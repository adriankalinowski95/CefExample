// Copyright (c) 2023 The Chromium Embedded Framework Authors. All rights
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
// $hash=e1ea194c8ef69a57ee4bee0b1729798128eb8754$
//

#include "libcef_dll/ctocpp/preference_manager_ctocpp.h"
#include "libcef_dll/ctocpp/dictionary_value_ctocpp.h"
#include "libcef_dll/ctocpp/request_context_ctocpp.h"
#include "libcef_dll/ctocpp/value_ctocpp.h"

// STATIC METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
CefRefPtr<CefPreferenceManager>
CefPreferenceManager::GetGlobalPreferenceManager() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_preference_manager_t* _retval = cef_preference_manager_get_global();

  // Return type: refptr_same
  return CefPreferenceManagerCToCpp::Wrap(_retval);
}

// VIRTUAL METHODS - Body may be edited by hand.

NO_SANITIZE("cfi-icall")
bool CefPreferenceManagerCToCpp::HasPreference(const CefString& name) {
  cef_preference_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, has_preference)) {
    return false;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(!name.empty());
  if (name.empty()) {
    return false;
  }

  // Execute
  int _retval = _struct->has_preference(_struct, name.GetStruct());

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
CefRefPtr<CefValue> CefPreferenceManagerCToCpp::GetPreference(
    const CefString& name) {
  cef_preference_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_preference)) {
    return nullptr;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(!name.empty());
  if (name.empty()) {
    return nullptr;
  }

  // Execute
  cef_value_t* _retval = _struct->get_preference(_struct, name.GetStruct());

  // Return type: refptr_same
  return CefValueCToCpp::Wrap(_retval);
}

NO_SANITIZE("cfi-icall")
CefRefPtr<CefDictionaryValue> CefPreferenceManagerCToCpp::GetAllPreferences(
    bool include_defaults) {
  cef_preference_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, get_all_preferences)) {
    return nullptr;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_dictionary_value_t* _retval =
      _struct->get_all_preferences(_struct, include_defaults);

  // Return type: refptr_same
  return CefDictionaryValueCToCpp::Wrap(_retval);
}

NO_SANITIZE("cfi-icall")
bool CefPreferenceManagerCToCpp::CanSetPreference(const CefString& name) {
  cef_preference_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, can_set_preference)) {
    return false;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(!name.empty());
  if (name.empty()) {
    return false;
  }

  // Execute
  int _retval = _struct->can_set_preference(_struct, name.GetStruct());

  // Return type: bool
  return _retval ? true : false;
}

NO_SANITIZE("cfi-icall")
bool CefPreferenceManagerCToCpp::SetPreference(const CefString& name,
                                               CefRefPtr<CefValue> value,
                                               CefString& error) {
  cef_preference_manager_t* _struct = GetStruct();
  if (CEF_MEMBER_MISSING(_struct, set_preference)) {
    return false;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(!name.empty());
  if (name.empty()) {
    return false;
  }
  // Unverified params: value

  // Execute
  int _retval = _struct->set_preference(_struct, name.GetStruct(),
                                        CefValueCToCpp::Unwrap(value),
                                        error.GetWritableStruct());

  // Return type: bool
  return _retval ? true : false;
}

// CONSTRUCTOR - Do not edit by hand.

CefPreferenceManagerCToCpp::CefPreferenceManagerCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

CefPreferenceManagerCToCpp::~CefPreferenceManagerCToCpp() {}

template <>
cef_preference_manager_t* CefCToCppRefCounted<
    CefPreferenceManagerCToCpp,
    CefPreferenceManager,
    cef_preference_manager_t>::UnwrapDerived(CefWrapperType type,
                                             CefPreferenceManager* c) {
  if (type == WT_REQUEST_CONTEXT) {
    return reinterpret_cast<cef_preference_manager_t*>(
        CefRequestContextCToCpp::Unwrap(
            reinterpret_cast<CefRequestContext*>(c)));
  }
  NOTREACHED() << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType CefCToCppRefCounted<CefPreferenceManagerCToCpp,
                                   CefPreferenceManager,
                                   cef_preference_manager_t>::kWrapperType =
    WT_PREFERENCE_MANAGER;
