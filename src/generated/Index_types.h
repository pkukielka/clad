/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Index_TYPES_H
#define Index_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"


namespace clad {

struct CXAvailabilityKind {
  enum type {
    CXAvailability_Available = 0,
    CXAvailability_Deprecated = 1,
    CXAvailability_NotAvailable = 2,
    CXAvailability_NotAccessible = 3
  };
};

extern const std::map<int, const char*> _CXAvailabilityKind_VALUES_TO_NAMES;

struct CXGlobalOptFlags {
  enum type {
    CXGlobalOpt_None = 0,
    CXGlobalOpt_ThreadBackgroundPriorityForIndexing = 1,
    CXGlobalOpt_ThreadBackgroundPriorityForEditing = 2,
    CXGlobalOpt_ThreadBackgroundPriorityForAll = 3
  };
};

extern const std::map<int, const char*> _CXGlobalOptFlags_VALUES_TO_NAMES;

typedef  ::clad::ResourceId CXIndex;

typedef  ::clad::ResourceId CXClientData;

typedef struct _CXVersion__isset {
  _CXVersion__isset() : Major(false), Minor(false), Subminor(false) {}
  bool Major;
  bool Minor;
  bool Subminor;
} _CXVersion__isset;

class CXVersion {
 public:

  static const char* ascii_fingerprint; // = "6435B39C87AB0E30F30BEDEFD7328C0D";
  static const uint8_t binary_fingerprint[16]; // = {0x64,0x35,0xB3,0x9C,0x87,0xAB,0x0E,0x30,0xF3,0x0B,0xED,0xEF,0xD7,0x32,0x8C,0x0D};

  CXVersion() : Major(0), Minor(0), Subminor(0) {
  }

  virtual ~CXVersion() throw() {}

  int32_t Major;
  int32_t Minor;
  int32_t Subminor;

  _CXVersion__isset __isset;

  void __set_Major(const int32_t val) {
    Major = val;
  }

  void __set_Minor(const int32_t val) {
    Minor = val;
  }

  void __set_Subminor(const int32_t val) {
    Subminor = val;
  }

  bool operator == (const CXVersion & rhs) const
  {
    if (!(Major == rhs.Major))
      return false;
    if (!(Minor == rhs.Minor))
      return false;
    if (!(Subminor == rhs.Subminor))
      return false;
    return true;
  }
  bool operator != (const CXVersion &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXVersion & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXVersion &a, CXVersion &b);

} // namespace

#endif
