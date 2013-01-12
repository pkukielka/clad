/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Location_TYPES_H
#define Location_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"
#include "File_types.h"
#include "TranslationUnit_types.h"


namespace clang { namespace thrift {

typedef struct _CXSourceLocation__isset {
  _CXSourceLocation__isset() : ptr_data(false), int_data(false) {}
  bool ptr_data;
  bool int_data;
} _CXSourceLocation__isset;

class CXSourceLocation {
 public:

  static const char* ascii_fingerprint; // = "CCD847ED8F9380F935E4ECB1C10F3559";
  static const uint8_t binary_fingerprint[16]; // = {0xCC,0xD8,0x47,0xED,0x8F,0x93,0x80,0xF9,0x35,0xE4,0xEC,0xB1,0xC1,0x0F,0x35,0x59};

  CXSourceLocation() : int_data(0) {
  }

  virtual ~CXSourceLocation() throw() {}

  std::vector< ::clang::thrift::ResourceId>  ptr_data;
   ::clang::thrift::u32 int_data;

  _CXSourceLocation__isset __isset;

  void __set_ptr_data(const std::vector< ::clang::thrift::ResourceId> & val) {
    ptr_data = val;
  }

  void __set_int_data(const  ::clang::thrift::u32 val) {
    int_data = val;
  }

  bool operator == (const CXSourceLocation & rhs) const
  {
    if (!(ptr_data == rhs.ptr_data))
      return false;
    if (!(int_data == rhs.int_data))
      return false;
    return true;
  }
  bool operator != (const CXSourceLocation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXSourceLocation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXSourceLocation &a, CXSourceLocation &b);

typedef struct _CXSourceRange__isset {
  _CXSourceRange__isset() : ptr_data(false), begin_int_data(false), end_int_data(false) {}
  bool ptr_data;
  bool begin_int_data;
  bool end_int_data;
} _CXSourceRange__isset;

class CXSourceRange {
 public:

  static const char* ascii_fingerprint; // = "8C9B1A52DF178D7BCD3BAAF3162A3D80";
  static const uint8_t binary_fingerprint[16]; // = {0x8C,0x9B,0x1A,0x52,0xDF,0x17,0x8D,0x7B,0xCD,0x3B,0xAA,0xF3,0x16,0x2A,0x3D,0x80};

  CXSourceRange() : begin_int_data(0), end_int_data(0) {
  }

  virtual ~CXSourceRange() throw() {}

  std::vector< ::clang::thrift::ResourceId>  ptr_data;
   ::clang::thrift::u32 begin_int_data;
   ::clang::thrift::u32 end_int_data;

  _CXSourceRange__isset __isset;

  void __set_ptr_data(const std::vector< ::clang::thrift::ResourceId> & val) {
    ptr_data = val;
  }

  void __set_begin_int_data(const  ::clang::thrift::u32 val) {
    begin_int_data = val;
  }

  void __set_end_int_data(const  ::clang::thrift::u32 val) {
    end_int_data = val;
  }

  bool operator == (const CXSourceRange & rhs) const
  {
    if (!(ptr_data == rhs.ptr_data))
      return false;
    if (!(begin_int_data == rhs.begin_int_data))
      return false;
    if (!(end_int_data == rhs.end_int_data))
      return false;
    return true;
  }
  bool operator != (const CXSourceRange &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXSourceRange & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXSourceRange &a, CXSourceRange &b);

typedef struct _CXSourcePosition__isset {
  _CXSourcePosition__isset() : file(false), filename(false), line(false), column(false), offset(false) {}
  bool file;
  bool filename;
  bool line;
  bool column;
  bool offset;
} _CXSourcePosition__isset;

class CXSourcePosition {
 public:

  static const char* ascii_fingerprint; // = "3490AC639D1D7CD0933B17E89E84AD32";
  static const uint8_t binary_fingerprint[16]; // = {0x34,0x90,0xAC,0x63,0x9D,0x1D,0x7C,0xD0,0x93,0x3B,0x17,0xE8,0x9E,0x84,0xAD,0x32};

  CXSourcePosition() : file(0), filename(), line(0), column(0), offset(0) {
  }

  virtual ~CXSourcePosition() throw() {}

   ::clang::thrift::CXFile file;
  std::string filename;
   ::clang::thrift::u32 line;
   ::clang::thrift::u32 column;
   ::clang::thrift::u32 offset;

  _CXSourcePosition__isset __isset;

  void __set_file(const  ::clang::thrift::CXFile val) {
    file = val;
  }

  void __set_filename(const std::string& val) {
    filename = val;
  }

  void __set_line(const  ::clang::thrift::u32 val) {
    line = val;
  }

  void __set_column(const  ::clang::thrift::u32 val) {
    column = val;
  }

  void __set_offset(const  ::clang::thrift::u32 val) {
    offset = val;
  }

  bool operator == (const CXSourcePosition & rhs) const
  {
    if (!(file == rhs.file))
      return false;
    if (!(filename == rhs.filename))
      return false;
    if (!(line == rhs.line))
      return false;
    if (!(column == rhs.column))
      return false;
    if (!(offset == rhs.offset))
      return false;
    return true;
  }
  bool operator != (const CXSourcePosition &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXSourcePosition & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXSourcePosition &a, CXSourcePosition &b);

}} // namespace

#endif
