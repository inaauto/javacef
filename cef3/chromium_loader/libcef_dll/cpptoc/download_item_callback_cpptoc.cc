// Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/download_item_callback_cpptoc.h"


namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK download_item_callback_cancel(
    struct _cef_download_item_callback_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefDownloadItemCallbackCppToC::Get(self)->Cancel();
}

void CEF_CALLBACK download_item_callback_pause(
    struct _cef_download_item_callback_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefDownloadItemCallbackCppToC::Get(self)->Pause();
}

void CEF_CALLBACK download_item_callback_resume(
    struct _cef_download_item_callback_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefDownloadItemCallbackCppToC::Get(self)->Resume();
}

}  // namespace


// CONSTRUCTOR - Do not edit by hand.

CefDownloadItemCallbackCppToC::CefDownloadItemCallbackCppToC() {
  GetStruct()->cancel = download_item_callback_cancel;
  GetStruct()->pause = download_item_callback_pause;
  GetStruct()->resume = download_item_callback_resume;
}

template<> CefRefPtr<CefDownloadItemCallback> CefCppToC<CefDownloadItemCallbackCppToC,
    CefDownloadItemCallback, cef_download_item_callback_t>::UnwrapDerived(
    CefWrapperType type, cef_download_item_callback_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template<> base::AtomicRefCount CefCppToC<CefDownloadItemCallbackCppToC,
    CefDownloadItemCallback, cef_download_item_callback_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCppToC<CefDownloadItemCallbackCppToC,
    CefDownloadItemCallback, cef_download_item_callback_t>::kWrapperType =
    WT_DOWNLOAD_ITEM_CALLBACK;
