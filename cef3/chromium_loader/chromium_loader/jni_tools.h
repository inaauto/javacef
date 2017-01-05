// Copyright (c) 2012 javacef Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef JNI_TOOLS_H
#define JNI_TOOLS_H
#pragma once

#include <jni.h>
#include <string>

#include "include/internal/cef_types_wrappers.h"

std::string jstring_to_stdstring(JNIEnv* env, jstring java_string);
jstring string_to_jstring(JNIEnv* env, const char* pat);

void set_jvm(JNIEnv* env, jobject jobj);
void cleanup_jvm(JNIEnv* env);
void send_handler(JNIEnv* env, jobject jobj, jlong);
void set_title(const char*, int);
jobject get_download_window(const char* fn, long long size, const char* mime);
std::string get_download_path_init(jobject dw);
void send_download_handler(jobject dw, int dh);
void send_download_status(jobject dw, int ds);
//jobject get_chromium(int id, int gh, int& hwnd);
void new_tab(int id, std::string url);
void close_tab(int id);
void send_load(int id, bool loading);
void send_navstate(int id, bool canGoBack, bool canGoForward);

struct ChromiumSettings;
void get_browser_settings(JNIEnv* env, jobject jcset, ChromiumSettings& cset);
void populate_cef_settings(JNIEnv* env, jobject jcset, CefSettings& cset);

#endif // JNI_TOOLS_H
