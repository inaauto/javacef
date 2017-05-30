// Copyright (c) 2012 javacef Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#import <Cocoa/Cocoa.h>
#import <objc/runtime.h>
#include "org_embedded_browser_Chromium.h"
#include "org_embedded_browser_DownloadWindow.h"
#include "jni_tools.h"

#include <iostream>
#include <sstream>
#include <string>
#include "include/cef_app.h"
#include "include/cef_application_mac.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
//#include "include/cef_runnable.h"
#include "tests/shared/browser/client_app_browser.h"
#include "tests/cefclient/browser/client_handler.h"
#include "tests/cefclient/browser/cookie_handler.h"
#include "tests/cefclient/browser/main_context_impl.h"
#include "tests/shared/browser/main_message_loop_external_pump.h"
#include "tests/shared/browser/main_message_loop_std.h"
#include "tests/shared/common/client_switches.h"
#include "chromium_loader/browser_creator.h"
#include "chromium_loader/signal_restore_posix.h"

using ClientHandler = client::ClientHandler;

namespace {

bool use_message_loop = false;
bool handling_send_event = false;
client::MainContextImpl* context;
std::string resources_dir_path;

} // namespace

// Send event handling is copied from javachromiumembedded util_mac.mm.
// Java provides an NSApplicationAWT implementation that we can't access or
// override directly. Therefore add the necessary CrAppControlProtocol
// functionality to NSApplication using categories and swizzling.
@interface NSApplication (JavaCefApplication)

- (BOOL)isHandlingSendEvent;
- (void)setHandlingSendEvent:(BOOL)handlingSendEvent;
- (void)_swizzled_sendEvent:(NSEvent*)event;

@end

@implementation NSApplication (JavaCefApplication)

// This selector is called very early during the application initialization.
+ (void)load {
  // Swap NSApplication::sendEvent with _swizzled_sendEvent.
  Method original = class_getInstanceMethod(self, @selector(sendEvent));
  Method swizzled =
  class_getInstanceMethod(self, @selector(_swizzled_sendEvent));
  method_exchangeImplementations(original, swizzled);
}

- (BOOL)isHandlingSendEvent {
  return handling_send_event;
}

- (void)setHandlingSendEvent:(BOOL)handlingSendEvent {
  handling_send_event = handlingSendEvent;
}

- (void)_swizzled_sendEvent:(NSEvent*)event {
  CefScopedSendingEvent sendingEventScoper;
  // Calls NSApplication::sendEvent due to the swizzling.
  [self _swizzled_sendEvent:event];
}

@end

@interface NSBundle (JavaCefBundle)

- (NSString *)_swizzled_pathForResource:(NSString *)name
                                 ofType:(NSString *)extension;

- (NSString *)_swizzled_pathForResource:(NSString *)name
                                 ofType:(NSString *)extension
                            inDirectory:(NSString *)subpath
                        forLocalization:(NSString *)localizationName;

@end

@implementation NSBundle (JavaCefBundle)

+ (void)load {
  // Swap NSApplication::pathForResource with _swizzled_pathForResource.
  Method original = class_getInstanceMethod(self, @selector(pathForResource:ofType:));
  Method swizzled = class_getInstanceMethod(self, @selector(_swizzled_pathForResource:ofType:));
  method_exchangeImplementations(original, swizzled);

  original = class_getInstanceMethod(self, @selector(pathForResource:ofType:inDirectory:forLocalization:));
  swizzled = class_getInstanceMethod(self, @selector(_swizzled_pathForResource:ofType:inDirectory:forLocalization:));
  method_exchangeImplementations(original, swizzled);
}

- (NSString *)_swizzled_pathForResource:(NSString *)name
                                 ofType:(NSString *)extension {
  // Try to use the original resolver.
  NSString* original = [self _swizzled_pathForResource:name ofType:extension];
  if (original)
    return original;

  // Load resources from resources_dir_path.
  std::string ext = ".";
  ext = extension ? ext + [extension UTF8String] : "";

  const std::string resources_dir = (const std::string)resources_dir_path;
  std::string path = resources_dir + "/" + [name UTF8String] + ext;
  return [NSString stringWithUTF8String:path.c_str()];
}

- (NSString *)_swizzled_pathForResource:(NSString *)name
                                 ofType:(NSString *)extension
                            inDirectory:(NSString *)subpath
                        forLocalization:(NSString *)localizationName {
  std::string ext = ".";
  ext = extension ? ext + [extension UTF8String] : "";

  const std::string resources_dir = (const std::string)resources_dir_path;
  std::string path = resources_dir + "/" + [localizationName UTF8String] + ".lproj/" + [name UTF8String] + ext;
  return [NSString stringWithUTF8String:path.c_str()];
}

@end

void GetBrowserWindowInfo(CefWindowInfo& info, CefWindowHandle handle) {
  // The size may be (0,0)
  NSSize size = handle.frame.size;

  // Initialize window info to the defaults for a child window
  info.SetAsChild(handle, 0, 0, size.width, size.height);
}

// The linker has -fvisibility=hidden by default, so we need to explictly
// export the jni functions.
#undef JNIEXPORT
#define JNIEXPORT __attribute ((visibility("default")))

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1init
  (JNIEnv *env, jobject jobj, jlong hwnd, jstring url, jobject chromiumset)
{
  DLOG(INFO) << "Enter init() method";

  // Make a simple argument.
  const int argc = 3;
  char** argv = (char**)malloc(argc * sizeof(*argv));
  argv[0] = strdup("java");
  argv[1] = strdup("--no-sandbox");
  argv[2] = strdup("--wait-for-debugger-children");

  CefMainArgs main_args(argc, argv);

  CefRefPtr<CefApp> app(new client::ClientAppBrowser);

  // Parse command-line arguments.
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromArgv(argc, argv);

  // Create the main context object.
  context = new client::MainContextImpl(command_line, true);
  //scoped_ptr<MainContextImpl> context(new MainContextImpl(command_line, true));

  CefSettings settings;

  // Populate the settings based on argument provided from Java
  populate_cef_settings(env, chromiumset, settings);

  settings.multi_threaded_message_loop = use_message_loop;
  settings.no_sandbox = true;
  //settings.single_process = true;

  // Create the main message loop object.
  scoped_ptr<client::MainMessageLoop> message_loop;
  if (settings.external_message_pump)
    message_loop = client::MainMessageLoopExternalPump::Create();
  else
    message_loop.reset(new client::MainMessageLoopStd);

  BackupSignalHandlers();

  // Initialize CEF.
  if (!context->Initialize(main_args, settings, app, NULL)) {
    fprintf(stderr, "Failed to initialize CEF.\n");
    return;
  }

  RestoreSignalHandlers();

  // log all init settings
  DLOG(INFO) << "settings.no_sandbox = " << settings.no_sandbox;
  DLOG(INFO) << "settings.multi_threaded_message_loop = " << settings.multi_threaded_message_loop;
  DLOG(INFO) << "settings.persist_session_cookies = " << settings.persist_session_cookies;
  DLOG(INFO) << "settings.persist_user_preferences = " << settings.persist_user_preferences;
  DLOG(INFO) << "settings.ignore_certificate_errors = " << settings.ignore_certificate_errors;
  DLOG(INFO) << "settings.log_severity = " << settings.log_severity;
  DLOG(INFO) << "settings.remote_debugging_port = " << settings.remote_debugging_port;
  DLOG(INFO) << "settings.uncaught_exception_stack_size = " << settings.uncaught_exception_stack_size;
  DLOG(INFO) << "settings.browser_subprocess_path = " << (std::string)CefString(&settings.browser_subprocess_path);
  DLOG(INFO) << "settings.resources_dir_path = " << (std::string)CefString(&settings.resources_dir_path);
  DLOG(INFO) << "settings.locales_dir_path = " << (std::string)CefString(&settings.locales_dir_path);
  DLOG(INFO) << "settings.cache_path = " << (std::string)CefString(&settings.cache_path);
  DLOG(INFO) << "settings.user_data_path = " << (std::string)CefString(&settings.user_data_path);
  DLOG(INFO) << "settings.locale = " << (std::string)CefString(&settings.locale);
  DLOG(INFO) << "settings.accept_language_list = " << (std::string)CefString(&settings.accept_language_list);
  DLOG(INFO) << "settings.log_file = " << (std::string)CefString(&settings.log_file);

  resources_dir_path = (std::string)CefString(&settings.resources_dir_path);

  NSView* view = (NSView*)hwnd;
  NSThread* thread = [NSThread currentThread];
  if ([thread isMainThread])
    printf("[javacef] main thread\n");

  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;

  CefRefPtr<ClientHandler> gh = NewBrowser(view, wc);
  gh->id = 1;

  env->ReleaseStringUTFChars(url, chr);

  // NOTE: This function (browser_init) should only be called ONCE in one process,
  // which means to call CefInitialize in the first broswer creation, and call 
  // CefShutdown in the exit of the process. Repeated calls to this function will 
  // NOT work, because the web page will not render. Most probably a bug in cef.
  set_jvm(env, jobj);
  send_handler(env, jobj, (jlong)(void*)gh);

  // Have to be here and use own jnienv to avoid errors.
  get_browser_settings(env, chromiumset, gh->csettings);
/*
  if (!use_message_loop) {
    CefRunMessageLoop();
    CefShutdown();
  }
*/
  DLOG(INFO) << "Exit init() method";
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1new
  (JNIEnv *env, jobject jobj, jlong hwnd, jint id, jstring url, jobject chromiumset)
{
  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;
  CefRefPtr<ClientHandler> gh = NewBrowser((CefWindowHandle)hwnd, wc);
  gh->id = id;
  env->ReleaseStringUTFChars(url, chr);
  send_handler(env, jobj, (jlong)(void*)gh);
  get_browser_settings(env, chromiumset, gh->csettings);
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1message_1loop
  (JNIEnv *env, jobject jobj)
{
  CefDoMessageLoopWork();
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1close
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  /*CefRefPtr<ClientHandler> g_handler_local;
  _asm {
    push eax
    mov eax, gh
    mov g_handler_local, eax
    pop eax
  }*/

  if (g_handler_local.get() && g_handler_local->GetBrowser()) {
    g_handler_local->GetBrowser()->GetHost()->CloseBrowser(true);
    g_handler_local->id = -1;
  }
  //_asm mov g_handler_local, 0;
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1shutdown
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;

  if (g_handler_local.get() && g_handler_local->GetBrowser() &&
      g_handler_local->GetBrowser()->GetHost()->GetWindowHandle()) {
    g_handler_local->GetBrowser()->GetHost()->CloseBrowser(true);
    g_handler_local->id = -1;
  }
  cleanup_jvm(env);
  context->Shutdown();

  //if (message_loop) {
  //  delete message_loop;
  //  message_loop = NULL;
  //}
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1clean_1cookies
  (JNIEnv *env, jobject jobj)
{
  CefRefPtr<CefCookieManager> cookieManager = CefCookieManager::GetGlobalManager(NULL);
  CefRefPtr<CefCookieVisitor> cookieHandler = new CookieHandler(true);
  cookieManager->VisitAllCookies(cookieHandler);
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1setUrl
  (JNIEnv *env, jobject jobj, jlong gh, jstring url)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  const char* chr = env->GetStringUTFChars(url, 0);
  CefString urlString = chr;

  if (g_handler_local.get()) {
    CefRefPtr<CefBrowser> browser = g_handler_local->GetBrowser();
    if (browser.get() && browser->GetMainFrame())
      browser->GetMainFrame()->LoadURL(urlString);
  }
  env->ReleaseStringUTFChars(url, chr);
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1resized
  (JNIEnv *env, jobject jobj, jlong gh, jlong hwnd)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  NSView* view = (CefWindowHandle)hwnd;

  if (g_handler_local.get() && g_handler_local->GetBrowser() &&
      g_handler_local->GetBrowser()->GetHost()->GetWindowHandle()) {
    NSArray* subviews = [view subviews];
    if ([subviews count] > 0) {
      NSView* browser_view = [subviews objectAtIndex:0];
      NSRect bound = [view bounds];
      //NSSize size = bound.size;
      //printf("subviews %lu w %f h %f\n", [subviews count], size.width, size.height);
      [browser_view setFrame:bound];
    }
  }
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1back
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  if (g_handler_local.get()) {
    CefRefPtr<CefBrowser> browser = g_handler_local->GetBrowser();
    if (browser.get() && browser->CanGoBack()) {
      browser->GoBack();
    }
  }
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1forward
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  if (g_handler_local.get()) {
    CefRefPtr<CefBrowser> browser = g_handler_local->GetBrowser();
    if (browser.get() && browser->CanGoForward()) {
      browser->GoForward();
    }
  }
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1reload
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;
  if (g_handler_local.get()) {
    CefRefPtr<CefBrowser> browser = g_handler_local->GetBrowser();
    if (browser.get()) {
      browser->Reload();
    }
  }
}

JNIEXPORT jlong JNICALL Java_org_embedded_browser_DownloadWindow_getReceivedN
  (JNIEnv *env, jobject jobj, jint dhint)
{
  /*CefRefPtr<CefDownloadHandlerW> d_handler;
  _asm {
  push eax
  mov eax, dhint
  mov d_handler, eax
  pop eax
  }
  int64 rs = -10;
  if (d_handler.get())
    rs = d_handler->received_size;
  _asm {
    mov d_handler, 0
  }
  return rs;*/
  return 0;
}
