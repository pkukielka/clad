/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Diagnostic_TYPES_H
#define Diagnostic_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"
#include "Location_types.h"
#include "TranslationUnit_types.h"


namespace clad {

struct CXDiagnosticSeverity {
  enum type {
    CXDiagnostic_Ignored = 0,
    CXDiagnostic_Note = 1,
    CXDiagnostic_Warning = 2,
    CXDiagnostic_Error = 3,
    CXDiagnostic_Fatal = 4
  };
};

extern const std::map<int, const char*> _CXDiagnosticSeverity_VALUES_TO_NAMES;

struct CXLoadDiag_Error {
  enum type {
    CXLoadDiag_None = 0,
    CXLoadDiag_Unknown = 1,
    CXLoadDiag_CannotLoad = 2,
    CXLoadDiag_InvalidFile = 3
  };
};

extern const std::map<int, const char*> _CXLoadDiag_Error_VALUES_TO_NAMES;

struct CXDiagnosticDisplayOptions {
  enum type {
    CXDiagnostic_DisplaySourceLocation = 1,
    CXDiagnostic_DisplayColumn = 2,
    CXDiagnostic_DisplaySourceRanges = 4,
    CXDiagnostic_DisplayOption = 8,
    CXDiagnostic_DisplayCategoryId = 16,
    CXDiagnostic_DisplayCategoryName = 32
  };
};

extern const std::map<int, const char*> _CXDiagnosticDisplayOptions_VALUES_TO_NAMES;

typedef  ::clad::ResourceId CXDiagnostic;

typedef  ::clad::ResourceId CXDiagnosticSet;

typedef struct _CXLoadDiagException__isset {
  _CXLoadDiagException__isset() : Error(false), ErrorString(false) {}
  bool Error;
  bool ErrorString;
} _CXLoadDiagException__isset;

class CXLoadDiagException : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "19B5240589E680301A7E32DF3971EFBE";
  static const uint8_t binary_fingerprint[16]; // = {0x19,0xB5,0x24,0x05,0x89,0xE6,0x80,0x30,0x1A,0x7E,0x32,0xDF,0x39,0x71,0xEF,0xBE};

  CXLoadDiagException() : Error((CXLoadDiag_Error::type)0), ErrorString() {
  }

  virtual ~CXLoadDiagException() throw() {}

  CXLoadDiag_Error::type Error;
  std::string ErrorString;

  _CXLoadDiagException__isset __isset;

  void __set_Error(const CXLoadDiag_Error::type val) {
    Error = val;
  }

  void __set_ErrorString(const std::string& val) {
    ErrorString = val;
  }

  bool operator == (const CXLoadDiagException & rhs) const
  {
    if (!(Error == rhs.Error))
      return false;
    if (!(ErrorString == rhs.ErrorString))
      return false;
    return true;
  }
  bool operator != (const CXLoadDiagException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXLoadDiagException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXLoadDiagException &a, CXLoadDiagException &b);

typedef struct _CXDiagnosticOption__isset {
  _CXDiagnosticOption__isset() : Enable(false), Disable(false) {}
  bool Enable;
  bool Disable;
} _CXDiagnosticOption__isset;

class CXDiagnosticOption {
 public:

  static const char* ascii_fingerprint; // = "07A9615F837F7D0A952B595DD3020972";
  static const uint8_t binary_fingerprint[16]; // = {0x07,0xA9,0x61,0x5F,0x83,0x7F,0x7D,0x0A,0x95,0x2B,0x59,0x5D,0xD3,0x02,0x09,0x72};

  CXDiagnosticOption() : Enable(), Disable() {
  }

  virtual ~CXDiagnosticOption() throw() {}

  std::string Enable;
  std::string Disable;

  _CXDiagnosticOption__isset __isset;

  void __set_Enable(const std::string& val) {
    Enable = val;
  }

  void __set_Disable(const std::string& val) {
    Disable = val;
  }

  bool operator == (const CXDiagnosticOption & rhs) const
  {
    if (!(Enable == rhs.Enable))
      return false;
    if (!(Disable == rhs.Disable))
      return false;
    return true;
  }
  bool operator != (const CXDiagnosticOption &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXDiagnosticOption & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXDiagnosticOption &a, CXDiagnosticOption &b);

typedef struct _CXDiagnosticFixIt__isset {
  _CXDiagnosticFixIt__isset() : ReplacementRange(false), ReplacementText(false) {}
  bool ReplacementRange;
  bool ReplacementText;
} _CXDiagnosticFixIt__isset;

class CXDiagnosticFixIt {
 public:

  static const char* ascii_fingerprint; // = "B6D5433EE95BE4D21B2A5CD1011EAD8E";
  static const uint8_t binary_fingerprint[16]; // = {0xB6,0xD5,0x43,0x3E,0xE9,0x5B,0xE4,0xD2,0x1B,0x2A,0x5C,0xD1,0x01,0x1E,0xAD,0x8E};

  CXDiagnosticFixIt() : ReplacementText() {
  }

  virtual ~CXDiagnosticFixIt() throw() {}

   ::clad::CXSourceRange ReplacementRange;
  std::string ReplacementText;

  _CXDiagnosticFixIt__isset __isset;

  void __set_ReplacementRange(const  ::clad::CXSourceRange& val) {
    ReplacementRange = val;
  }

  void __set_ReplacementText(const std::string& val) {
    ReplacementText = val;
  }

  bool operator == (const CXDiagnosticFixIt & rhs) const
  {
    if (!(ReplacementRange == rhs.ReplacementRange))
      return false;
    if (!(ReplacementText == rhs.ReplacementText))
      return false;
    return true;
  }
  bool operator != (const CXDiagnosticFixIt &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXDiagnosticFixIt & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXDiagnosticFixIt &a, CXDiagnosticFixIt &b);

} // namespace

#endif