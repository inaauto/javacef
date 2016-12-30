// Copyright (c) 2012 javacef Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "targetver.h"
#include "org_embedded_browser_Chromium.h"
#include "org_embedded_browser_DownloadWindow.h"
#include "jni_tools.h"

#include <windows.h>
#include <commdlg.h>
#include <shellapi.h>
#include <direct.h>
#include <sstream>
#include <string>
#include "include/base/cef_scoped_ptr.h"
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "include/cef_runnable.h"
#include "cefclient/browser/client_app_browser.h"
#include "cefclient/browser/main_context_impl.h"
#include "cefclient/browser/client_handler.h"
#include "cefclient/browser/cookie_handler.h"
#include "cefclient/common/client_switches.h"
#include "browser_creator.h"

#include "cefclient/browser/main_message_loop.h"
#include "cefclient/browser/main_message_loop_std.h"

using ClientHandler = client::ClientHandler;

client::MainMessageLoop *message_loop;

HWND mainBrowserHandle = NULL;

void GetBrowserWindowInfo(CefWindowInfo& info, CefWindowHandle handle) {
  // The size may be (0,0)

  RECT rect;
  GetClientRect(handle, &rect);

  // Initialize window info to the defaults for a child window
  info.SetAsChild(handle, rect);
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1init
  (JNIEnv *env, jobject jobj, jlong hwnd, jstring url, jobject chromiumset)
{
  CefMainArgs main_args(GetModuleHandle(NULL));
  CefRefPtr<client::ClientApp> app(new client::ClientAppBrowser);

  // Parse command line arguments. The passed in values are ignored on Windows.
  //AppInitCommandLine(0, NULL);
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  //command_line->InitFromString(::GetCommandLineW());

  // Create the main context object.
  scoped_ptr<client::MainContextImpl> context(new client::MainContextImpl(command_line, false));

  CefSettings settings;

  // Populate the settings based on command line arguments.
  //AppGetSettings(settings);

  // Populate the settings based on argument provided from Java
  populate_cef_settings(env, chromiumset, settings);

  // if set to true, the process crashes in SWT
  settings.multi_threaded_message_loop = false;

  // Initialize CEF.
  //CefInitialize(main_args, settings, app.get(), NULL);
  context->Initialize(main_args, settings, app.get(), NULL);

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

  HWND hMain;
  hMain = (HWND)((void*)hwnd);

  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;

  CefRefPtr<ClientHandler> gh = NewBrowser(hMain, wc);
  gh->id = 1;

  env->ReleaseStringUTFChars(url, chr);

  // NOTE: This function (browser_init) should only be called ONCE in one process,
  // which means to call CefInitialize in the first browser creation, and call 
  // CefShutdown in the exit of the process. Repeated calls to this function will 
  // NOT work, because the web page will not render. Most probably a bug in cef.
  set_jvm(env, jobj);
  send_handler(env, jobj, (jlong)(void*)gh);

  // Have to be here and use own jnienv to avoid errors.
  get_browser_settings(env, chromiumset, gh->csettings);

  if (gh->csettings.run_modal_message_loop_in_init) {
    // Run the CEF message loop. This function will block until the application
    // recieves a WM_QUIT message.
    message_loop = new client::MainMessageLoopStd;
    message_loop->Run();
    //CefRunMessageLoop();
    cleanup_jvm(env);
    //CefShutdown();
    context->Shutdown();
  }

  DLOG(INFO) << "Exit init method!";
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1new
  (JNIEnv *env, jobject jobj, jlong hwnd, jint id, jstring url, jobject chromiumset)
{
  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;
  CefRefPtr<ClientHandler> gh = NewBrowser((HWND)((void*)hwnd), wc);
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
  }
  //_asm mov g_handler_local, 0;
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1shutdown
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<ClientHandler> g_handler_local = (ClientHandler*)gh;

  if (g_handler_local.get() && g_handler_local->GetBrowser() &&
      g_handler_local->GetBrowser()->GetHost()->GetWindowHandle()) {
    //g_handler_local->GetBrowser()->GetHost()->ParentWindowWillClose();
    //g_handler_local->GetBrowser()->GetHost()->CloseBrowser(true);
    mainBrowserHandle = g_handler_local->GetBrowser()->GetHost()->GetWindowHandle();

    // Exit main message loop
    g_handler_local->Quit();
  }
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1clean_1cookies
  (JNIEnv *env, jobject jobj)
{
  CefRefPtr<CefCookieManager> cookieManager = CefCookieManager::GetGlobalManager(NULL);
  CefRefPtr<CefCookieVisitor> cookieHandler = new CookieHandler(true);
  cookieManager->VisitAllCookies(cookieHandler);
  // Doesn't work:
  //CefString empty("");
  //cookieManager->DeleteCookies(empty, empty);
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
  HWND hMain = (HWND)hwnd;

  if (g_handler_local.get() && g_handler_local->GetBrowser() &&
      g_handler_local->GetBrowser()->GetHost()->GetWindowHandle()) {
    // Resize the browser window and address bar to match the new frame window size
    RECT rect;
    GetClientRect(hMain, &rect);

    HDWP hdwp = BeginDeferWindowPos(1);
    hdwp = DeferWindowPos(hdwp, g_handler_local->GetBrowser()->GetHost()->GetWindowHandle(), NULL,
      rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
      SWP_NOZORDER);
    EndDeferWindowPos(hdwp);

    PostMessage(g_handler_local->GetBrowser()->GetHost()->GetWindowHandle(), WM_SETFOCUS, 0, NULL);
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

// Global functions

void AppQuitMessageLoop() {
  /*
    CefQuitMessageLoop();
  */
  if (mainBrowserHandle)
    PostMessage(mainBrowserHandle, WM_QUIT, 0, 0);
}
