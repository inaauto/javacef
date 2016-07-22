// Copyright (c) 2012 javacef Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "jni_tools.h"
#include "chromium_settings.h"

#if defined(OS_LINUX)
#include <stdlib.h>
#endif

JavaVM* jvm;
JNIEnv* envs;
jobject jobjs;
jclass  jchromium;

class AutoJvmAttach {
 public:
  AutoJvmAttach() : env_(NULL), detach_(false) {
    if (jvm->GetEnv((void**)&env_, JNI_VERSION_1_6) == JNI_EDETACHED) {
      if (jvm->AttachCurrentThread((void**)&env_, NULL) == JNI_OK)
        detach_ = true;
      else
        printf("Can not get jni env\n");
    }
  }

  ~AutoJvmAttach() {
    if (detach_)
      jvm->DetachCurrentThread();
  }

  JNIEnv* get() {
    return env_;
  }

  JNIEnv* operator->() {
    return env_;
  }

 private:
  JNIEnv* env_;
  bool detach_;
};

void set_jvm(JNIEnv* env, jobject jobj)
{
  jint rs = env->GetJavaVM(&jvm);
  if (rs != JNI_OK) {
    printf("Can not get jvm\n");
    exit(1);
  }
  jchromium = (jclass)env->NewGlobalRef(env->FindClass("org/embedded/browser/Chromium"));
  envs = env;
  jobjs = jobj;
}

void cleanup_jvm(JNIEnv* env) {
  env->DeleteGlobalRef(jchromium);
}

jstring string_to_jstring(JNIEnv* env, const char* pat)
{
  jclass strClass = env->FindClass("Ljava/lang/String;");
  jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
  jbyteArray bytes = env->NewByteArray((jsize)strlen(pat));
  env->SetByteArrayRegion(bytes, 0, (jsize)strlen(pat), (jbyte*)pat);
  jstring encoding = env->NewStringUTF("utf-8");
  return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}

std::string jstring_to_stdstring(JNIEnv* env, jstring java_string)
{
  std::string return_val;

  const char* nativeString = env->GetStringUTFChars(java_string, 0);
  if (nativeString != NULL)
    return_val = std::string(nativeString);

  // release java string
  env->ReleaseStringUTFChars(java_string, nativeString);

  return return_val;
}

void send_handler(JNIEnv* env, jobject jobj, jlong gh)
{
  jclass cls = env->FindClass("org/embedded/browser/Chromium");
  jmethodID mid = env->GetMethodID(cls, "loadfinish", "(J)V");
  env->CallObjectMethod(jobj, mid, gh);
}

void set_title(const char* title, int id)
{
  AutoJvmAttach jenv;
  jmethodID mid = jenv->GetStaticMethodID(jchromium, "title_change", "(Ljava/lang/String;I)V");
  jenv->CallStaticObjectMethod(jchromium, mid, string_to_jstring(jenv.get(), title), id);
}

jobject get_download_window(const char* fn, long long size, const char* mime)
{
  jclass cls = envs->FindClass("org/embedded/browser/DownloadWindow");
  jmethodID mid = envs->GetMethodID(cls, "<init>", "(Ljava/lang/String;JLjava/lang/String;)V");
  return envs->NewObject(cls, mid, string_to_jstring(envs, fn), size, string_to_jstring(envs, mime));
}

std::string get_download_path_init(jobject dw)
{
  jclass cls = envs->FindClass("org/embedded/browser/DownloadWindow");
  jmethodID mid = envs->GetMethodID(cls, "getPathAndInit", "()Ljava/lang/String;");
  jstring jpath = (jstring)envs->CallObjectMethod(dw, mid);
  const char* chr = envs->GetStringUTFChars(jpath, 0);
  std::string path(chr);
  envs->ReleaseStringUTFChars(jpath, chr);
  return path;
}

void send_download_handler(jobject dw, int dh)
{
  jclass cls = envs->FindClass("org/embedded/browser/DownloadWindow");
  jmethodID mid = envs->GetMethodID(cls, "set_dhptr", "(I)V");
  envs->CallObjectMethod(dw, mid, dh);
}

void send_download_status(jobject dw, int ds)
{
  jclass cls = envs->FindClass("org/embedded/browser/DownloadWindow");
  jmethodID msid = envs->GetMethodID(cls, "set_status", "(I)V");
  envs->CallObjectMethod(dw, msid, ds);
}

void new_tab(int id, std::string url)
{
  jclass cls = envs->FindClass("org/embedded/browser/Chromium");
  jmethodID mid = envs->GetMethodID(cls, "new_window", "(ILjava/lang/String;)V");//(I)Lorg/embedded/browser/Chromium;
  envs->CallObjectMethod(jobjs, mid, id, string_to_jstring(envs, url.c_str()));
  //jfieldID fidc = envs->GetFieldID(cls, "chptr", "I");
  //envs->SetIntField(bobj, fidc, gh);
  //jfieldID fidh = envs->GetFieldID(cls, "hwnd", "I");
  //hwnd = envs->GetIntField(bobj, fidh);
  //return bobj;get_chromium
}

void close_tab(int id)
{
  jclass cls = envs->FindClass("org/embedded/browser/Chromium");
  jmethodID mid = envs->GetMethodID(cls, "close_window", "(I)V");
  envs->CallObjectMethod(jobjs, mid, id);
}

void send_load(int id, bool loading)
{
  AutoJvmAttach jenv;
  jmethodID mid = jenv->GetStaticMethodID(jchromium, "load_change", "(IZ)V");
  jenv->CallStaticObjectMethod(jchromium, mid, id, loading);
}

void send_navstate(int id, bool canGoBack, bool canGoForward)
{
  AutoJvmAttach jenv;
  jmethodID mid = jenv->GetStaticMethodID(jchromium, "navstate_change", "(IZZ)V");
  jenv->CallStaticObjectMethod(jchromium, mid, id, canGoBack, canGoForward);
}

void get_browser_settings(JNIEnv* env, jobject jcset, ChromiumSettings& cset)
{
  jclass cls = env->FindClass("org/embedded/browser/ChromeSettings");

  jfieldID allow_right_button = env->GetFieldID(cls, "allow_right_button", "Z");
  cset.allow_right_button = (bool)env->GetBooleanField(jcset, allow_right_button);

  jfieldID run_modal_message_loop_in_init = env->GetFieldID(cls, "separateMessageLoop", "Z");
  cset.run_modal_message_loop_in_init = (bool)env->GetBooleanField(jcset, run_modal_message_loop_in_init);

  jfieldID keyid = env->GetFieldID(cls, "keys", "[Ljava/lang/String;");
  jobjectArray keys = (jobjectArray)env->GetObjectField(jcset, keyid);
  jint klen = env->GetArrayLength(keys);
  jfieldID valueid = env->GetFieldID(cls, "values", "[Ljava/lang/String;");
  jobjectArray values = (jobjectArray)env->GetObjectField(jcset, valueid);
  //jint vlen = env->GetArrayLength(values);
  for (int i = 0; i < klen; i++)
  {
    jstring kstr = (jstring)env->GetObjectArrayElement(keys, (jsize)i);
    jstring vstr = (jstring)env->GetObjectArrayElement(values, (jsize)i);
    const char* kchr = env->GetStringUTFChars(kstr, 0);
    const char* vchr = env->GetStringUTFChars(vstr, 0);
    cset.cookies[std::string(kchr)] = std::string(vchr);
    env->ReleaseStringUTFChars(kstr, kchr);
    env->ReleaseStringUTFChars(vstr, vchr);
  }
}

bool get_setting_boolean(JNIEnv* env, jclass cls, jobject jcset, const char* field_name)
{
  if (env == NULL || cls == NULL || jcset == NULL || field_name == NULL)
    return FALSE;

  jfieldID fieldId = env->GetFieldID(cls, field_name, "Z");
  if (fieldId == NULL)
    return FALSE;

  return (bool)env->GetBooleanField(jcset, fieldId);
}

int get_setting_int(JNIEnv* env, jclass cls, jobject jcset, const char* field_name)
{
  if (env == NULL || cls == NULL || jcset == NULL || field_name == NULL)
    return NULL;

  jfieldID fieldId = env->GetFieldID(cls, field_name, "I");
  if (fieldId == NULL)
    return FALSE;

  return (int)env->GetIntField(jcset, fieldId);
}

jstring get_setting_jstring(JNIEnv* env, jclass cls, jobject jcset, const char* field_name)
{
  if (env == NULL || cls == NULL || jcset == NULL || field_name == NULL)
    return NULL;

  jfieldID fieldId = env->GetFieldID(cls, field_name, "Ljava/lang/String;");
  if (fieldId == NULL)
    return NULL;

  return (jstring)env->GetObjectField(jcset, fieldId);
}

void populate_cef_settings(JNIEnv* env, jobject jcset, CefSettings& cef_settings)
{
  jclass cls = env->FindClass("org/embedded/browser/ChromeSettings");
  jstring java_string;

  // get all boolean settings
  
  cef_settings.multi_threaded_message_loop = get_setting_boolean(env, cls, jcset, "multiThreadedMessageLoop");
  cef_settings.no_sandbox = get_setting_boolean(env, cls, jcset, "noSandbox");
  cef_settings.persist_session_cookies = get_setting_boolean(env, cls, jcset, "persistSessionCookies");
  cef_settings.persist_user_preferences = get_setting_boolean(env, cls, jcset, "persistUserPreferences");
  cef_settings.ignore_certificate_errors = get_setting_boolean(env, cls, jcset, "ignoreCertificateErrors");

  // get all integer settings
  cef_settings.log_severity = static_cast<cef_log_severity_t>(get_setting_int(env, cls, jcset, "logSeverityAsInt"));
  cef_settings.remote_debugging_port = get_setting_int(env, cls, jcset, "remoteDebuggingPort");
  cef_settings.uncaught_exception_stack_size = get_setting_int(env, cls, jcset, "uncaughtExceptionStackSize");

  // get all string settings
  java_string = get_setting_jstring(env, cls, jcset, "browserSubprocessPath");
  if (java_string != NULL) {
    CefString(&cef_settings.browser_subprocess_path) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "resourcesDirPath");
  if (java_string != NULL) {
    CefString(&cef_settings.resources_dir_path) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "localesDirPath");
  if (java_string != NULL) {
    CefString(&cef_settings.locales_dir_path) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "cachePath");
  if (java_string != NULL) {
    CefString(&cef_settings.cache_path) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "userDataPath");
  if (java_string != NULL) {
    CefString(&cef_settings.user_data_path) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "locale");
  if (java_string != NULL) {
    CefString(&cef_settings.locale) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "acceptLanguageList");
  if (java_string != NULL) {
    CefString(&cef_settings.accept_language_list) = jstring_to_stdstring(env, java_string);
  }
  java_string = get_setting_jstring(env, cls, jcset, "logFile");
  if (java_string != NULL) {
    CefString(&cef_settings.log_file) = jstring_to_stdstring(env, java_string);
  }
}
