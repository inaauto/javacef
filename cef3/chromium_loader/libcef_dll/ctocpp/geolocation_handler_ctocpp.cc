// Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/browser_cpptoc.h"
#include "libcef_dll/cpptoc/geolocation_callback_cpptoc.h"
#include "libcef_dll/ctocpp/geolocation_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

bool CefGeolocationHandlerCToCpp::OnRequestGeolocationPermission(
    CefRefPtr<CefBrowser> browser, const CefString& requesting_url,
    int request_id, CefRefPtr<CefGeolocationCallback> callback) {
  cef_geolocation_handler_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, on_request_geolocation_permission))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return false;
  // Verify param: requesting_url; type: string_byref_const
  DCHECK(!requesting_url.empty());
  if (requesting_url.empty())
    return false;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return false;

  // Execute
  int _retval = _struct->on_request_geolocation_permission(_struct,
      CefBrowserCppToC::Wrap(browser),
      requesting_url.GetStruct(),
      request_id,
      CefGeolocationCallbackCppToC::Wrap(callback));

  // Return type: bool
  return _retval?true:false;
}

void CefGeolocationHandlerCToCpp::OnCancelGeolocationPermission(
    CefRefPtr<CefBrowser> browser, const CefString& requesting_url,
    int request_id) {
  cef_geolocation_handler_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, on_cancel_geolocation_permission))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return;
  // Verify param: requesting_url; type: string_byref_const
  DCHECK(!requesting_url.empty());
  if (requesting_url.empty())
    return;

  // Execute
  _struct->on_cancel_geolocation_permission(_struct,
      CefBrowserCppToC::Wrap(browser),
      requesting_url.GetStruct(),
      request_id);
}


// CONSTRUCTOR - Do not edit by hand.

CefGeolocationHandlerCToCpp::CefGeolocationHandlerCToCpp() {
}

template<> cef_geolocation_handler_t* CefCToCpp<CefGeolocationHandlerCToCpp,
    CefGeolocationHandler, cef_geolocation_handler_t>::UnwrapDerived(
    CefWrapperType type, CefGeolocationHandler* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCToCpp<CefGeolocationHandlerCToCpp,
    CefGeolocationHandler, cef_geolocation_handler_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCToCpp<CefGeolocationHandlerCToCpp,
    CefGeolocationHandler, cef_geolocation_handler_t>::kWrapperType =
    WT_GEOLOCATION_HANDLER;
