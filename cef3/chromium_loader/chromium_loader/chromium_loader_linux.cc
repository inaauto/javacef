
#include "org_embedded_browser_Chromium.h"
#include "org_embedded_browser_DownloadWindow.h"
#include "jni_tools.h"

#include <stdlib.h>
#include <sstream>
#include <string>
#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_frame.h"
#include "tests/shared/browser/client_app_browser.h"
#include "tests/cefclient/browser/client_handler.h"
#include "tests/cefclient/browser/cookie_handler.h"
#include "tests/cefclient/browser/main_context_impl.h"
#include "chromium_loader/signal_restore_posix.h"
#include "browser_creator.h"

namespace {

char* szWorkingDir;  // The current working directory
bool message_loop = false;
client::MainContextImpl* context;

} // namespace


void GetBrowserWindowInfo(CefWindowInfo& info, CefWindowHandle handle) {
  // The size may be (0,0)

  GtkWidget* canvas = (GtkWidget*)handle;

  GtkAllocation* allocation = new GtkAllocation();
  gtk_widget_get_allocation(canvas, allocation);

  CefRect window_rect(0, 0, allocation->width, allocation->height);

  DLOG(INFO) << "Window info: width: " << allocation->width << "; height=" << allocation->height;

  delete allocation;

  // Initialize window info to the defaults for a child window
  info.SetAsChild(handle, window_rect);
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
  CefRefPtr<client::ClientApp> app(new client::ClientAppBrowser);

  // Retrieve the current working directory.
  szWorkingDir = getenv("JAVACEF_PATH");
  if (!szWorkingDir)
    szWorkingDir = (char*)calloc(1, sizeof(char));

  // Parse command line arguments. The passed in values are ignored on Windows.
  //AppInitCommandLine(argc, argv);
  CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
  command_line->InitFromArgv(argc, argv);

  // Create the main context object.
  context = new client::MainContextImpl(command_line, true);

  CefSettings settings;

  // Populate the settings based on command line arguments.
  //AppGetSettings(settings);

  // Populate the settings based on argument provided from Java
  populate_cef_settings(env, chromiumset, settings);

  settings.multi_threaded_message_loop = message_loop;
  settings.no_sandbox = true;
  //settings.single_process = true;

  BackupSignalHandlers();

  // Initialize CEF.
  context->Initialize(main_args, settings, app.get(), NULL);

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

  GtkWidget* canvas = (GtkWidget*)hwnd;
  GtkWidget* vbox = gtk_vbox_new(FALSE, 0);
  gtk_fixed_put(GTK_FIXED(canvas), vbox, 0, 0);

  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;

  CefRefPtr<client::ClientHandler> gh = NewBrowser((CefWindowHandle)vbox, wc);
  gh->id = 1;
  gh->vbox = vbox;

  env->ReleaseStringUTFChars(url, chr);

  // NOTE: This function (browser_init) should only be called ONCE in one process,
  // which means to call CefInitialize in the first broswer creation, and call 
  // CefShutdown in the exit of the process. Repeated calls to this function will 
  // NOT work, because the web page will not render. Most probably a bug in cef.
  set_jvm(env, jobj);
  send_handler(env, jobj, (jlong)(void*)gh);

  // Have to be here and use own jnienv to avoid errors.
  get_browser_settings(env, chromiumset, gh->csettings);

  //CefRunMessageLoop();
  //CefShutdown();

  DLOG(INFO) << "Exit init() method";
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1new
  (JNIEnv *env, jobject jobj, jlong hwnd, jint id, jstring url, jobject chromiumset)
{
  DLOG(INFO) << "Enter new() method";

  const char* chr = env->GetStringUTFChars(url, 0);
  CefString wc = chr;

  GtkWidget* canvas = (GtkWidget*)hwnd;
  GtkWidget* vbox = gtk_vbox_new(FALSE, 0);
  gtk_fixed_put(GTK_FIXED(canvas), vbox, 0, 0);

  CefRefPtr<client::ClientHandler> gh = NewBrowser((CefWindowHandle)vbox, wc);
  gh->id = id;
  gh->vbox = vbox;
  env->ReleaseStringUTFChars(url, chr);
  send_handler(env, jobj, (jlong)(void*)gh);
  get_browser_settings(env, chromiumset, gh->csettings);

  DLOG(INFO) << "Exit new() method";
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1message_1loop
  (JNIEnv *env, jobject jobj)
{
  CefDoMessageLoopWork();
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1close
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;

  if (g_handler_local.get() && g_handler_local->GetBrowser()) {
    g_handler_local->GetBrowser()->GetHost()->CloseBrowser(true);
    g_handler_local->id = -1;
  }
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1shutdown
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;

  if (g_handler_local.get() && g_handler_local->GetBrowser() &&
      g_handler_local->GetBrowser()->GetHost()->GetWindowHandle()) {
    //g_handler_local->GetBrowser()->GetHost()->ParentWindowWillClose();
    g_handler_local->GetBrowser()->GetHost()->CloseBrowser(true);
    g_handler_local->id = -1;
  }

  cleanup_jvm(env);
  context->Shutdown();
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
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;
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
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;
  GtkWidget* canvas = (GtkWidget*)hwnd;

  GtkAllocation* allocation = new GtkAllocation();
  gtk_widget_get_allocation(canvas, allocation);

  gtk_widget_show_all(GTK_WIDGET(canvas));
  gtk_widget_set_size_request(g_handler_local->vbox,
                              allocation->width,
                              allocation->height);

  DLOG(INFO) << "browser_resized() method: Window info: width: " << allocation->width << "; height=" << allocation->height;

  delete allocation;
}

JNIEXPORT void JNICALL Java_org_embedded_browser_Chromium_browser_1back
  (JNIEnv *env, jobject jobj, jlong gh)
{
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;
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
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;
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
  CefRefPtr<client::ClientHandler> g_handler_local = (client::ClientHandler*)gh;
  if (g_handler_local.get()) {
    CefRefPtr<CefBrowser> browser = g_handler_local->GetBrowser();
    if (browser.get()) {
      browser->Reload();
    }
  }
}

JNIEXPORT jlong JNICALL Java_org_embedded_browser_DownloadWindow_getReceivedN
  (JNIEnv *env, jobject jobj, jint dhint) // TODO: fix long
{
  return 0;
}

// Global functions

std::string AppGetWorkingDirectory() {
  return szWorkingDir;
}

void AppQuitMessageLoop() {
  // Do nothing.
}

