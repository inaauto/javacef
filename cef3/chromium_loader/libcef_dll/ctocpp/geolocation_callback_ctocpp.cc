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

#include "libcef_dll/ctocpp/geolocation_callback_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

void CefGeolocationCallbackCToCpp::Continue(bool allow) {
  cef_geolocation_callback_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, cont))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->cont(_struct,
      allow);
}


// CONSTRUCTOR - Do not edit by hand.

CefGeolocationCallbackCToCpp::CefGeolocationCallbackCToCpp() {
}

template<> cef_geolocation_callback_t* CefCToCpp<CefGeolocationCallbackCToCpp,
    CefGeolocationCallback, cef_geolocation_callback_t>::UnwrapDerived(
    CefWrapperType type, CefGeolocationCallback* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template<> base::AtomicRefCount CefCToCpp<CefGeolocationCallbackCToCpp,
    CefGeolocationCallback, cef_geolocation_callback_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCToCpp<CefGeolocationCallbackCToCpp,
    CefGeolocationCallback, cef_geolocation_callback_t>::kWrapperType =
    WT_GEOLOCATION_CALLBACK;
