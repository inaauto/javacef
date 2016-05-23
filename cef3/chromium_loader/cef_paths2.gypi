# Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

{
  'includes': [
    # Bring in the autogenerated source file lists.
    'cef_paths.gypi',
   ],
  'variables': {
    'includes_common': [
      'include/base/cef_atomic_ref_count.h',
      'include/base/cef_atomicops.h',
      'include/base/cef_basictypes.h',
      'include/base/cef_bind.h',
      'include/base/cef_bind_helpers.h',
      'include/base/cef_build.h',
      'include/base/cef_callback.h',
      'include/base/cef_callback_forward.h',
      'include/base/cef_callback_helpers.h',
      'include/base/cef_callback_list.h',
      'include/base/cef_cancelable_callback.h',
      'include/base/cef_lock.h',
      'include/base/cef_logging.h',
      'include/base/cef_macros.h',
      'include/base/cef_move.h',
      'include/base/cef_platform_thread.h',
      'include/base/cef_ref_counted.h',
      'include/base/cef_scoped_ptr.h',
      'include/base/cef_string16.h',
      'include/base/cef_template_util.h',
      'include/base/cef_thread_checker.h',
      'include/base/cef_thread_collision_warner.h',
      'include/base/cef_trace_event.h',
      'include/base/cef_tuple.h',
      'include/base/cef_weak_ptr.h',
      'include/base/internal/cef_bind_internal.h',
      'include/base/internal/cef_callback_internal.h',
      'include/base/internal/cef_lock_impl.h',
      'include/base/internal/cef_raw_scoped_refptr_mismatch_checker.h',
      'include/base/internal/cef_thread_checker_impl.h',
      'include/cef_base.h',
      'include/cef_pack_resources.h',
      'include/cef_pack_strings.h',
      'include/cef_runnable.h',
      'include/cef_version.h',
      'include/internal/cef_export.h',
      'include/internal/cef_logging_internal.h',
      'include/internal/cef_ptr.h',
      'include/internal/cef_string.h',
      'include/internal/cef_string_list.h',
      'include/internal/cef_string_map.h',
      'include/internal/cef_string_multimap.h',
      'include/internal/cef_string_types.h',
      'include/internal/cef_string_wrappers.h',
      'include/internal/cef_thread_internal.h',
      'include/internal/cef_time.h',
      'include/internal/cef_trace_event_internal.h',
      'include/internal/cef_types.h',
      'include/internal/cef_types_wrappers.h',
      '<@(autogen_cpp_includes)',
    ],
    'includes_capi': [
      'include/capi/cef_base_capi.h',
      '<@(autogen_capi_includes)',
    ],
    'includes_wrapper': [
      'include/wrapper/cef_byte_read_handler.h',
      'include/wrapper/cef_closure_task.h',
      'include/wrapper/cef_helpers.h',
      'include/wrapper/cef_message_router.h',
      'include/wrapper/cef_resource_manager.h',
      'include/wrapper/cef_stream_resource_handler.h',
      'include/wrapper/cef_xml_object.h',
      'include/wrapper/cef_zip_archive.h',
    ],
    'includes_win': [
      'include/base/internal/cef_atomicops_x86_msvc.h',
      'include/base/internal/cef_bind_internal_win.h',
      'include/cef_sandbox_win.h',
      'include/internal/cef_types_win.h',
      'include/internal/cef_win.h',
    ],
    'includes_mac': [
      'include/base/internal/cef_atomicops_atomicword_compat.h',
      'include/base/internal/cef_atomicops_mac.h',
      'include/cef_application_mac.h',
      'include/internal/cef_mac.h',
      'include/internal/cef_types_mac.h',
    ],
    'includes_linux': [
      'include/base/internal/cef_atomicops_atomicword_compat.h',
      'include/base/internal/cef_atomicops_x86_gcc.h',
      'include/internal/cef_linux.h',
      'include/internal/cef_types_linux.h',
    ],
    'libcef_sources_common': [
      'libcef_dll/cpptoc/cpptoc.h',
      'libcef_dll/ctocpp/base_ctocpp.cc',
      'libcef_dll/ctocpp/base_ctocpp.h',
      'libcef_dll/ctocpp/ctocpp.h',
      'libcef_dll/libcef_dll.cc',
      'libcef_dll/libcef_dll2.cc',
      'libcef_dll/resource.h',
      'libcef_dll/transfer_util.cc',
      'libcef_dll/transfer_util.h',
      'libcef_dll/wrapper_types.h',
      '<@(autogen_library_side)',
    ],
    'libcef_dll_wrapper_sources_common': [
      'libcef_dll/base/cef_atomicops_x86_gcc.cc',
      'libcef_dll/base/cef_bind_helpers.cc',
      'libcef_dll/base/cef_callback_helpers.cc',
      'libcef_dll/base/cef_callback_internal.cc',
      'libcef_dll/base/cef_lock.cc',
      'libcef_dll/base/cef_lock_impl.cc',
      'libcef_dll/base/cef_logging.cc',
      'libcef_dll/base/cef_ref_counted.cc',
      'libcef_dll/base/cef_string16.cc',
      'libcef_dll/base/cef_thread_checker_impl.cc',
      'libcef_dll/base/cef_thread_collision_warner.cc',
      'libcef_dll/base/cef_weak_ptr.cc',
      'libcef_dll/cpptoc/base_cpptoc.cc',
      'libcef_dll/cpptoc/base_cpptoc.h',
      'libcef_dll/cpptoc/cpptoc.h',
      'libcef_dll/ctocpp/ctocpp.h',
      'libcef_dll/transfer_util.cc',
      'libcef_dll/transfer_util.h',
      'libcef_dll/wrapper_types.h',
      'libcef_dll/wrapper/cef_browser_info_map.h',
      'libcef_dll/wrapper/cef_byte_read_handler.cc',
      'libcef_dll/wrapper/cef_closure_task.cc',
      'libcef_dll/wrapper/cef_message_router.cc',
      'libcef_dll/wrapper/cef_resource_manager.cc',
      'libcef_dll/wrapper/cef_stream_resource_handler.cc',
      'libcef_dll/wrapper/cef_xml_object.cc',
      'libcef_dll/wrapper/cef_zip_archive.cc',
      'libcef_dll/wrapper/libcef_dll_wrapper.cc',
      'libcef_dll/wrapper/libcef_dll_wrapper2.cc',
      '<@(autogen_client_side)',
    ],
    'cefclient_sources_browser': [
      'cefclient/browser/binding_test.cc',
      'cefclient/browser/binding_test.h',
      'cefclient/browser/browser_window.cc',
      'cefclient/browser/browser_window.h',
      'cefclient/browser/bytes_write_handler.cc',
      'cefclient/browser/bytes_write_handler.h',
      'cefclient/browser/client_app_browser.cc',
      'cefclient/browser/client_app_browser.h',
      'cefclient/browser/client_app_delegates_browser.cc',
      'cefclient/browser/client_handler.cc',
      'cefclient/browser/client_handler.h',
      'cefclient/browser/client_handler_osr.cc',
      'cefclient/browser/client_handler_osr.h',
      'cefclient/browser/client_handler_std.cc',
      'cefclient/browser/client_handler_std.h',
      'cefclient/browser/client_types.h',
      'cefclient/browser/cookie_handler.cc',
      'cefclient/browser/cookie_handler.h',
      'cefclient/browser/dialog_test.cc',
      'cefclient/browser/dialog_test.h',
      'cefclient/browser/geometry_util.cc',
      'cefclient/browser/geometry_util.h',
      'cefclient/browser/main_context.cc',
      'cefclient/browser/main_context.h',
      'cefclient/browser/main_context_impl.cc',
      'cefclient/browser/main_context_impl.h',
      'cefclient/browser/main_message_loop.h',
      'cefclient/browser/main_message_loop.cc',
      'cefclient/browser/main_message_loop_std.h',
      'cefclient/browser/main_message_loop_std.cc',
      'cefclient/browser/osr_dragdrop_events.h',
      'cefclient/browser/osr_renderer.h',
      'cefclient/browser/osr_renderer.cc',
      'cefclient/browser/preferences_test.cc',
      'cefclient/browser/preferences_test.h',
      'cefclient/browser/resource.h',
      'cefclient/browser/resource_util.h',
      'cefclient/browser/response_filter_test.cc',
      'cefclient/browser/response_filter_test.h',
      'cefclient/browser/root_window.cc',
      'cefclient/browser/root_window.h',
      'cefclient/browser/root_window_manager.cc',
      'cefclient/browser/root_window_manager.h',
      'cefclient/browser/scheme_test.cc',
      'cefclient/browser/scheme_test.h',
      'cefclient/browser/temp_window.h',
      'cefclient/browser/test_runner.cc',
      'cefclient/browser/test_runner.h',
      'cefclient/browser/urlrequest_test.cc',
      'cefclient/browser/urlrequest_test.h',
      'cefclient/browser/window_test.cc',
      'cefclient/browser/window_test.h',
    ],
    'cefclient_sources_common': [
      'cefclient/common/client_app.cc',
      'cefclient/common/client_app.h',
      'cefclient/common/client_app_delegates_common.cc',
      'cefclient/common/client_app_other.cc',
      'cefclient/common/client_app_other.h',
      'cefclient/common/client_switches.cc',
      'cefclient/common/client_switches.h',
      'cefclient/common/scheme_test_common.cc',
      'cefclient/common/scheme_test_common.h',
    ],
    'cefclient_sources_renderer': [
      'cefclient/renderer/client_app_delegates_renderer.cc',
      'cefclient/renderer/client_app_renderer.cc',
      'cefclient/renderer/client_app_renderer.h',
      'cefclient/renderer/client_renderer.cc',
      'cefclient/renderer/client_renderer.h',
      'cefclient/renderer/performance_test.cc',
      'cefclient/renderer/performance_test.h',
      'cefclient/renderer/performance_test_setup.h',
      'cefclient/renderer/performance_test_tests.cc',
    ],
    'cefclient_sources_resources': [
      'cefclient/resources/binding.html',
      'cefclient/resources/dialogs.html',
      'cefclient/resources/localstorage.html',
      'cefclient/resources/logo.png',
      'cefclient/resources/osr_test.html',
      'cefclient/resources/other_tests.html',
      'cefclient/resources/pdf.html',
      'cefclient/resources/pdf.pdf',
      'cefclient/resources/performance.html',
      'cefclient/resources/performance2.html',
      'cefclient/resources/preferences.html',
      'cefclient/resources/response_filter.html',
      'cefclient/resources/transparency.html',
      'cefclient/resources/urlrequest.html',
      'cefclient/resources/window.html',
      'cefclient/resources/xmlhttprequest.html',
    ],
    'cefclient_sources_win': [
      'cefclient/browser/browser_window_osr_win.cc',
      'cefclient/browser/browser_window_osr_win.h',
      'cefclient/browser/browser_window_std_win.cc',
      'cefclient/browser/browser_window_std_win.h',
      'cefclient/browser/main_context_impl_win.cc',
      'cefclient/browser/main_message_loop_multithreaded_win.cc',
      'cefclient/browser/main_message_loop_multithreaded_win.h',
      'cefclient/browser/osr_dragdrop_win.cc',
      'cefclient/browser/osr_dragdrop_win.h',
      'cefclient/browser/osr_window_win.cc',
      'cefclient/browser/osr_window_win.h',
      'cefclient/browser/resource_util_win.cc',
      'cefclient/browser/root_window_win.cc',
      'cefclient/browser/root_window_win.h',
      'cefclient/browser/temp_window_win.cc',
      'cefclient/browser/temp_window_win.h',
      'cefclient/browser/util_win.cc',
      'cefclient/browser/util_win.h',
      'cefclient/browser/window_test_win.cc',
      'cefclient/cefclient_win.cc',
      'cefclient/resources/win/cefclient.exe.manifest',
      'cefclient/resources/win/cefclient.ico',
      'cefclient/resources/win/cefclient.rc',
      'cefclient/resources/win/small.ico',
      '<@(cefclient_sources_browser)',
      '<@(cefclient_sources_common)',
      '<@(cefclient_sources_renderer)',
      '<@(cefclient_sources_resources)',
    ],
    'cefclient_sources_mac': [
      'cefclient/browser/browser_window_osr_mac.h',
      'cefclient/browser/browser_window_osr_mac.mm',
      'cefclient/browser/browser_window_std_mac.h',
      'cefclient/browser/browser_window_std_mac.mm',
      'cefclient/browser/main_context_impl_posix.cc',
      'cefclient/browser/resource_util_mac.mm',
      'cefclient/browser/resource_util_posix.cc',
      'cefclient/browser/root_window_mac.h',
      'cefclient/browser/root_window_mac.mm',
      'cefclient/browser/temp_window_mac.h',
      'cefclient/browser/temp_window_mac.mm',
      'cefclient/browser/window_test_mac.mm',
      'cefclient/cefclient_mac.mm',
      '<@(cefclient_sources_browser)',
      '<@(cefclient_sources_common)',
   ],
    'cefclient_sources_mac_helper': [
      'cefclient/process_helper_mac.cc',
      '<@(cefclient_sources_common)',
      '<@(cefclient_sources_renderer)',
    ],
    'cefclient_bundle_resources_mac': [
      'cefclient/resources/mac/cefclient.icns',
      'cefclient/resources/mac/English.lproj/InfoPlist.strings',
      'cefclient/resources/mac/English.lproj/MainMenu.xib',
      'cefclient/resources/mac/Info.plist',
      '<@(cefclient_sources_resources)',
    ],
    'cefclient_sources_linux': [
      'cefclient/browser/browser_window_osr_gtk.cc',
      'cefclient/browser/browser_window_osr_gtk.h',
      'cefclient/browser/browser_window_std_gtk.cc',
      'cefclient/browser/browser_window_std_gtk.h',
      'cefclient/browser/dialog_handler_gtk.cc',
      'cefclient/browser/dialog_handler_gtk.h',
      'cefclient/browser/main_context_impl_posix.cc',
      'cefclient/browser/print_handler_gtk.cc',
      'cefclient/browser/print_handler_gtk.h',
      'cefclient/browser/resource_util_linux.cc',
      'cefclient/browser/resource_util_posix.cc',
      'cefclient/browser/root_window_gtk.cc',
      'cefclient/browser/root_window_gtk.h',
      'cefclient/browser/temp_window_x11.cc',
      'cefclient/browser/temp_window_x11.h',
      'cefclient/browser/window_test_gtk.cc',
      'cefclient/cefclient_gtk.cc',
      '<@(cefclient_sources_browser)',
      '<@(cefclient_sources_common)',
      '<@(cefclient_sources_renderer)',
    ],
    'cefclient_bundle_resources_linux': [
      '<@(cefclient_sources_resources)',
    ],
    'cefsimple_sources_common': [
      'cefsimple/simple_app.cc',
      'cefsimple/simple_app.h',
      'cefsimple/simple_handler.cc',
      'cefsimple/simple_handler.h',
    ],
    'cefsimple_sources_win': [
      'cefsimple/cefsimple.exe.manifest',
      'cefsimple/cefsimple.rc',
      'cefsimple/cefsimple_win.cc',
      'cefsimple/simple_handler_win.cc',
      'cefsimple/resource.h',
      'cefsimple/res/cefsimple.ico',
      'cefsimple/res/small.ico',
    ],
    'cefsimple_sources_mac': [
      'cefsimple/cefsimple_mac.mm',
      'cefsimple/simple_handler_mac.mm',
    ],
    'cefsimple_sources_mac_helper': [
      'cefsimple/process_helper_mac.cc',
    ],
    'cefsimple_bundle_resources_mac': [
      'cefsimple/mac/cefsimple.icns',
      'cefsimple/mac/English.lproj/InfoPlist.strings',
      'cefsimple/mac/English.lproj/MainMenu.xib',
      'cefsimple/mac/Info.plist',
    ],
    'cefsimple_sources_linux': [
      'cefsimple/cefsimple_linux.cc',
      'cefsimple/simple_handler_linux.cc',
    ],
    'chromium_loader_sources_common': [
      'chromium_loader/browser_creator.cc',
      'chromium_loader/browser_creator.h',
      'chromium_loader/chromium_settings.h',
      'chromium_loader/jni_tools.cc',
      'chromium_loader/jni_tools.h',
    ],
    'chromium_loader_sources_win': [
      'chromium_loader/chromium_loader_win.cc',
      'chromium_loader/chromium_loader_win.rc',
      'chromium_loader/resource.h',
      'chromium_loader/targetver.h',
    ],
    'chromium_loader_sources_mac': [
      'chromium_loader/chromium_loader_mac.mm',
      'chromium_loader/signal_restore_posix.cc',
      'chromium_loader/signal_restore_posix.h',
    ],
    'chromium_loader_sources_linux': [
      'chromium_loader/chromium_loader_linux.cc',
      'chromium_loader/signal_restore_posix.cc',
      'chromium_loader/signal_restore_posix.h',
    ],
  },
}
