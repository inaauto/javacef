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

#include "libcef_dll/cpptoc/menu_model_delegate_cpptoc.h"
#include "libcef_dll/ctocpp/menu_model_ctocpp.h"


// STATIC METHODS - Body may be edited by hand.

CefRefPtr<CefMenuModel> CefMenuModel::CreateMenuModel(
    CefRefPtr<CefMenuModelDelegate> delegate) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: delegate; type: refptr_diff
  DCHECK(delegate.get());
  if (!delegate.get())
    return NULL;

  // Execute
  cef_menu_model_t* _retval = cef_menu_model_create(
      CefMenuModelDelegateCppToC::Wrap(delegate));

  // Return type: refptr_same
  return CefMenuModelCToCpp::Wrap(_retval);
}


// VIRTUAL METHODS - Body may be edited by hand.

bool CefMenuModelCToCpp::Clear() {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, clear))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->clear(_struct);

  // Return type: bool
  return _retval?true:false;
}

int CefMenuModelCToCpp::GetCount() {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_count))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_count(_struct);

  // Return type: simple
  return _retval;
}

bool CefMenuModelCToCpp::AddSeparator() {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_separator))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->add_separator(_struct);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::AddItem(int command_id, const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_item))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->add_item(_struct,
      command_id,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::AddCheckItem(int command_id, const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_check_item))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->add_check_item(_struct,
      command_id,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::AddRadioItem(int command_id, const CefString& label,
    int group_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_radio_item))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->add_radio_item(_struct,
      command_id,
      label.GetStruct(),
      group_id);

  // Return type: bool
  return _retval?true:false;
}

CefRefPtr<CefMenuModel> CefMenuModelCToCpp::AddSubMenu(int command_id,
    const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, add_sub_menu))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return NULL;

  // Execute
  cef_menu_model_t* _retval = _struct->add_sub_menu(_struct,
      command_id,
      label.GetStruct());

  // Return type: refptr_same
  return CefMenuModelCToCpp::Wrap(_retval);
}

bool CefMenuModelCToCpp::InsertSeparatorAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, insert_separator_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->insert_separator_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::InsertItemAt(int index, int command_id,
    const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, insert_item_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->insert_item_at(_struct,
      index,
      command_id,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::InsertCheckItemAt(int index, int command_id,
    const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, insert_check_item_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->insert_check_item_at(_struct,
      index,
      command_id,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::InsertRadioItemAt(int index, int command_id,
    const CefString& label, int group_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, insert_radio_item_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->insert_radio_item_at(_struct,
      index,
      command_id,
      label.GetStruct(),
      group_id);

  // Return type: bool
  return _retval?true:false;
}

CefRefPtr<CefMenuModel> CefMenuModelCToCpp::InsertSubMenuAt(int index,
    int command_id, const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, insert_sub_menu_at))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return NULL;

  // Execute
  cef_menu_model_t* _retval = _struct->insert_sub_menu_at(_struct,
      index,
      command_id,
      label.GetStruct());

  // Return type: refptr_same
  return CefMenuModelCToCpp::Wrap(_retval);
}

bool CefMenuModelCToCpp::Remove(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, remove))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->remove(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::RemoveAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, remove_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->remove_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

int CefMenuModelCToCpp::GetIndexOf(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_index_of))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_index_of(_struct,
      command_id);

  // Return type: simple
  return _retval;
}

int CefMenuModelCToCpp::GetCommandIdAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_command_id_at))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_command_id_at(_struct,
      index);

  // Return type: simple
  return _retval;
}

bool CefMenuModelCToCpp::SetCommandIdAt(int index, int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_command_id_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_command_id_at(_struct,
      index,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

CefString CefMenuModelCToCpp::GetLabel(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_label))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_label(_struct,
      command_id);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefMenuModelCToCpp::GetLabelAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_label_at))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = _struct->get_label_at(_struct,
      index);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

bool CefMenuModelCToCpp::SetLabel(int command_id, const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_label))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->set_label(_struct,
      command_id,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetLabelAt(int index, const CefString& label) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_label_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: label; type: string_byref_const
  DCHECK(!label.empty());
  if (label.empty())
    return false;

  // Execute
  int _retval = _struct->set_label_at(_struct,
      index,
      label.GetStruct());

  // Return type: bool
  return _retval?true:false;
}

CefMenuModel::MenuItemType CefMenuModelCToCpp::GetType(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_type))
    return MENUITEMTYPE_NONE;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_menu_item_type_t _retval = _struct->get_type(_struct,
      command_id);

  // Return type: simple
  return _retval;
}

CefMenuModel::MenuItemType CefMenuModelCToCpp::GetTypeAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_type_at))
    return MENUITEMTYPE_NONE;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_menu_item_type_t _retval = _struct->get_type_at(_struct,
      index);

  // Return type: simple
  return _retval;
}

int CefMenuModelCToCpp::GetGroupId(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_group_id))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_group_id(_struct,
      command_id);

  // Return type: simple
  return _retval;
}

int CefMenuModelCToCpp::GetGroupIdAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_group_id_at))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->get_group_id_at(_struct,
      index);

  // Return type: simple
  return _retval;
}

bool CefMenuModelCToCpp::SetGroupId(int command_id, int group_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_group_id))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_group_id(_struct,
      command_id,
      group_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetGroupIdAt(int index, int group_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_group_id_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_group_id_at(_struct,
      index,
      group_id);

  // Return type: bool
  return _retval?true:false;
}

CefRefPtr<CefMenuModel> CefMenuModelCToCpp::GetSubMenu(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_sub_menu))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_menu_model_t* _retval = _struct->get_sub_menu(_struct,
      command_id);

  // Return type: refptr_same
  return CefMenuModelCToCpp::Wrap(_retval);
}

CefRefPtr<CefMenuModel> CefMenuModelCToCpp::GetSubMenuAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_sub_menu_at))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_menu_model_t* _retval = _struct->get_sub_menu_at(_struct,
      index);

  // Return type: refptr_same
  return CefMenuModelCToCpp::Wrap(_retval);
}

bool CefMenuModelCToCpp::IsVisible(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_visible))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_visible(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::IsVisibleAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_visible_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_visible_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetVisible(int command_id, bool visible) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_visible))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_visible(_struct,
      command_id,
      visible);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetVisibleAt(int index, bool visible) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_visible_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_visible_at(_struct,
      index,
      visible);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::IsEnabled(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_enabled))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_enabled(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::IsEnabledAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_enabled_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_enabled_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetEnabled(int command_id, bool enabled) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_enabled))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_enabled(_struct,
      command_id,
      enabled);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetEnabledAt(int index, bool enabled) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_enabled_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_enabled_at(_struct,
      index,
      enabled);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::IsChecked(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_checked))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_checked(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::IsCheckedAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, is_checked_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_checked_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetChecked(int command_id, bool checked) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_checked))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_checked(_struct,
      command_id,
      checked);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetCheckedAt(int index, bool checked) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_checked_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_checked_at(_struct,
      index,
      checked);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::HasAccelerator(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, has_accelerator))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->has_accelerator(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::HasAcceleratorAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, has_accelerator_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->has_accelerator_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetAccelerator(int command_id, int key_code,
    bool shift_pressed, bool ctrl_pressed, bool alt_pressed) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_accelerator))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_accelerator(_struct,
      command_id,
      key_code,
      shift_pressed,
      ctrl_pressed,
      alt_pressed);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::SetAcceleratorAt(int index, int key_code,
    bool shift_pressed, bool ctrl_pressed, bool alt_pressed) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_accelerator_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->set_accelerator_at(_struct,
      index,
      key_code,
      shift_pressed,
      ctrl_pressed,
      alt_pressed);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::RemoveAccelerator(int command_id) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, remove_accelerator))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->remove_accelerator(_struct,
      command_id);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::RemoveAcceleratorAt(int index) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, remove_accelerator_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->remove_accelerator_at(_struct,
      index);

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::GetAccelerator(int command_id, int& key_code,
    bool& shift_pressed, bool& ctrl_pressed, bool& alt_pressed) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_accelerator))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: shift_pressed; type: bool_byref
  int shift_pressedInt = shift_pressed;
  // Translate param: ctrl_pressed; type: bool_byref
  int ctrl_pressedInt = ctrl_pressed;
  // Translate param: alt_pressed; type: bool_byref
  int alt_pressedInt = alt_pressed;

  // Execute
  int _retval = _struct->get_accelerator(_struct,
      command_id,
      &key_code,
      &shift_pressedInt,
      &ctrl_pressedInt,
      &alt_pressedInt);

  // Restore param:shift_pressed; type: bool_byref
  shift_pressed = shift_pressedInt?true:false;
  // Restore param:ctrl_pressed; type: bool_byref
  ctrl_pressed = ctrl_pressedInt?true:false;
  // Restore param:alt_pressed; type: bool_byref
  alt_pressed = alt_pressedInt?true:false;

  // Return type: bool
  return _retval?true:false;
}

bool CefMenuModelCToCpp::GetAcceleratorAt(int index, int& key_code,
    bool& shift_pressed, bool& ctrl_pressed, bool& alt_pressed) {
  cef_menu_model_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_accelerator_at))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: shift_pressed; type: bool_byref
  int shift_pressedInt = shift_pressed;
  // Translate param: ctrl_pressed; type: bool_byref
  int ctrl_pressedInt = ctrl_pressed;
  // Translate param: alt_pressed; type: bool_byref
  int alt_pressedInt = alt_pressed;

  // Execute
  int _retval = _struct->get_accelerator_at(_struct,
      index,
      &key_code,
      &shift_pressedInt,
      &ctrl_pressedInt,
      &alt_pressedInt);

  // Restore param:shift_pressed; type: bool_byref
  shift_pressed = shift_pressedInt?true:false;
  // Restore param:ctrl_pressed; type: bool_byref
  ctrl_pressed = ctrl_pressedInt?true:false;
  // Restore param:alt_pressed; type: bool_byref
  alt_pressed = alt_pressedInt?true:false;

  // Return type: bool
  return _retval?true:false;
}


// CONSTRUCTOR - Do not edit by hand.

CefMenuModelCToCpp::CefMenuModelCToCpp() {
}

template<> cef_menu_model_t* CefCToCpp<CefMenuModelCToCpp, CefMenuModel,
    cef_menu_model_t>::UnwrapDerived(CefWrapperType type, CefMenuModel* c) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#if DCHECK_IS_ON()
template<> base::AtomicRefCount CefCToCpp<CefMenuModelCToCpp, CefMenuModel,
    cef_menu_model_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCToCpp<CefMenuModelCToCpp, CefMenuModel,
    cef_menu_model_t>::kWrapperType = WT_MENU_MODEL;
