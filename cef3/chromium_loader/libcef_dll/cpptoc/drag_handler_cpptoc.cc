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

#include "libcef_dll/cpptoc/drag_handler_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/drag_data_ctocpp.h"


namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK drag_handler_on_drag_enter(struct _cef_drag_handler_t* self,
    cef_browser_t* browser, cef_drag_data_t* dragData,
    cef_drag_operations_mask_t mask) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return 0;
  // Verify param: dragData; type: refptr_diff
  DCHECK(dragData);
  if (!dragData)
    return 0;

  // Execute
  bool _retval = CefDragHandlerCppToC::Get(self)->OnDragEnter(
      CefBrowserCToCpp::Wrap(browser),
      CefDragDataCToCpp::Wrap(dragData),
      mask);

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK drag_handler_on_draggable_regions_changed(
    struct _cef_drag_handler_t* self, cef_browser_t* browser,
    size_t regionsCount, cef_draggable_region_t const* regions) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: regions; type: simple_vec_byref_const
  DCHECK(regionsCount == 0 || regions);
  if (regionsCount > 0 && !regions)
    return;

  // Translate param: regions; type: simple_vec_byref_const
  std::vector<CefDraggableRegion > regionsList;
  if (regionsCount > 0) {
    for (size_t i = 0; i < regionsCount; ++i) {
      CefDraggableRegion regionsVal = regions[i];
      regionsList.push_back(regionsVal);
    }
  }

  // Execute
  CefDragHandlerCppToC::Get(self)->OnDraggableRegionsChanged(
      CefBrowserCToCpp::Wrap(browser),
      regionsList);
}

}  // namespace


// CONSTRUCTOR - Do not edit by hand.

CefDragHandlerCppToC::CefDragHandlerCppToC() {
  GetStruct()->on_drag_enter = drag_handler_on_drag_enter;
  GetStruct()->on_draggable_regions_changed =
      drag_handler_on_draggable_regions_changed;
}

template<> CefRefPtr<CefDragHandler> CefCppToC<CefDragHandlerCppToC,
    CefDragHandler, cef_drag_handler_t>::UnwrapDerived(CefWrapperType type,
    cef_drag_handler_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template<> base::AtomicRefCount CefCppToC<CefDragHandlerCppToC, CefDragHandler,
    cef_drag_handler_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCppToC<CefDragHandlerCppToC, CefDragHandler,
    cef_drag_handler_t>::kWrapperType = WT_DRAG_HANDLER;
