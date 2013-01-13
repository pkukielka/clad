/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TranslationUnit_TYPES_H
#define TranslationUnit_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"
#include "Index_types.h"


namespace clad {

struct CXTranslationUnit_Flags {
  enum type {
    CXTranslationUnit_None = 0,
    CXTranslationUnit_DetailedPreprocessingRecord = 1,
    CXTranslationUnit_Incomplete = 2,
    CXTranslationUnit_PrecompiledPreamble = 4,
    CXTranslationUnit_CacheCompletionResults = 8,
    CXTranslationUnit_ForSerialization = 16,
    CXTranslationUnit_CXXChainedPCH = 32,
    CXTranslationUnit_SkipFunctionBodies = 64,
    CXTranslationUnit_IncludeBriefCommentsInCodeCompletion = 128
  };
};

extern const std::map<int, const char*> _CXTranslationUnit_Flags_VALUES_TO_NAMES;

struct CXSaveTranslationUnit_Flags {
  enum type {
    CXSaveTranslationUnit_None = 0
  };
};

extern const std::map<int, const char*> _CXSaveTranslationUnit_Flags_VALUES_TO_NAMES;

struct CXSaveError {
  enum type {
    CXSaveError_None = 0,
    CXSaveError_Unknown = 1,
    CXSaveError_TranslationErrors = 2,
    CXSaveError_InvalidTU = 3
  };
};

extern const std::map<int, const char*> _CXSaveError_VALUES_TO_NAMES;

struct CXReparse_Flags {
  enum type {
    CXReparse_None = 0
  };
};

extern const std::map<int, const char*> _CXReparse_Flags_VALUES_TO_NAMES;

struct CXTUResourceUsageKind {
  enum type {
    CXTUResourceUsage_AST = 1,
    CXTUResourceUsage_Identifiers = 2,
    CXTUResourceUsage_Selectors = 3,
    CXTUResourceUsage_GlobalCompletionResults = 4,
    CXTUResourceUsage_SourceManagerContentCache = 5,
    CXTUResourceUsage_AST_SideTables = 6,
    CXTUResourceUsage_SourceManager_Membuffer_Malloc = 7,
    CXTUResourceUsage_SourceManager_Membuffer_MMap = 8,
    CXTUResourceUsage_ExternalASTSource_Membuffer_Malloc = 9,
    CXTUResourceUsage_ExternalASTSource_Membuffer_MMap = 10,
    CXTUResourceUsage_Preprocessor = 11,
    CXTUResourceUsage_PreprocessingRecord = 12,
    CXTUResourceUsage_SourceManager_DataStructures = 13,
    CXTUResourceUsage_Preprocessor_HeaderSearch = 14,
    CXTUResourceUsage_MEMORY_IN_BYTES_BEGIN = 1,
    CXTUResourceUsage_MEMORY_IN_BYTES_END = 14,
    CXTUResourceUsage_First = 1,
    CXTUResourceUsage_Last = 14
  };
};

extern const std::map<int, const char*> _CXTUResourceUsageKind_VALUES_TO_NAMES;

typedef  ::clad::ResourceId CXTranslationUnit;

typedef struct _CXUnsavedFile__isset {
  _CXUnsavedFile__isset() : Filename(false), Contents(false), Length(false) {}
  bool Filename;
  bool Contents;
  bool Length;
} _CXUnsavedFile__isset;

class CXUnsavedFile {
 public:

  static const char* ascii_fingerprint; // = "343DA57F446177400B333DC49B037B0C";
  static const uint8_t binary_fingerprint[16]; // = {0x34,0x3D,0xA5,0x7F,0x44,0x61,0x77,0x40,0x0B,0x33,0x3D,0xC4,0x9B,0x03,0x7B,0x0C};

  CXUnsavedFile() : Filename(), Contents(), Length(0) {
  }

  virtual ~CXUnsavedFile() throw() {}

  std::string Filename;
  std::string Contents;
   ::clad::u32 Length;

  _CXUnsavedFile__isset __isset;

  void __set_Filename(const std::string& val) {
    Filename = val;
  }

  void __set_Contents(const std::string& val) {
    Contents = val;
  }

  void __set_Length(const  ::clad::u32 val) {
    Length = val;
  }

  bool operator == (const CXUnsavedFile & rhs) const
  {
    if (!(Filename == rhs.Filename))
      return false;
    if (!(Contents == rhs.Contents))
      return false;
    if (!(Length == rhs.Length))
      return false;
    return true;
  }
  bool operator != (const CXUnsavedFile &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXUnsavedFile & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXUnsavedFile &a, CXUnsavedFile &b);

typedef struct _CXTUResourceUsageEntry__isset {
  _CXTUResourceUsageEntry__isset() : kind(false), amount(false) {}
  bool kind;
  bool amount;
} _CXTUResourceUsageEntry__isset;

class CXTUResourceUsageEntry {
 public:

  static const char* ascii_fingerprint; // = "6E7DD25E88B43484CFC93FCB15DCA1AF";
  static const uint8_t binary_fingerprint[16]; // = {0x6E,0x7D,0xD2,0x5E,0x88,0xB4,0x34,0x84,0xCF,0xC9,0x3F,0xCB,0x15,0xDC,0xA1,0xAF};

  CXTUResourceUsageEntry() : kind((CXTUResourceUsageKind::type)0), amount(0) {
  }

  virtual ~CXTUResourceUsageEntry() throw() {}

  CXTUResourceUsageKind::type kind;
   ::clad::u64 amount;

  _CXTUResourceUsageEntry__isset __isset;

  void __set_kind(const CXTUResourceUsageKind::type val) {
    kind = val;
  }

  void __set_amount(const  ::clad::u64 val) {
    amount = val;
  }

  bool operator == (const CXTUResourceUsageEntry & rhs) const
  {
    if (!(kind == rhs.kind))
      return false;
    if (!(amount == rhs.amount))
      return false;
    return true;
  }
  bool operator != (const CXTUResourceUsageEntry &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXTUResourceUsageEntry & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXTUResourceUsageEntry &a, CXTUResourceUsageEntry &b);

typedef struct _CXTUResourceUsage__isset {
  _CXTUResourceUsage__isset() : data(false), entries(false) {}
  bool data;
  bool entries;
} _CXTUResourceUsage__isset;

class CXTUResourceUsage {
 public:

  static const char* ascii_fingerprint; // = "458A44B0FD0112BE746A8E4B68F24C77";
  static const uint8_t binary_fingerprint[16]; // = {0x45,0x8A,0x44,0xB0,0xFD,0x01,0x12,0xBE,0x74,0x6A,0x8E,0x4B,0x68,0xF2,0x4C,0x77};

  CXTUResourceUsage() : data(0) {
  }

  virtual ~CXTUResourceUsage() throw() {}

   ::clad::ResourceId data;
  std::vector<CXTUResourceUsageEntry>  entries;

  _CXTUResourceUsage__isset __isset;

  void __set_data(const  ::clad::ResourceId val) {
    data = val;
  }

  void __set_entries(const std::vector<CXTUResourceUsageEntry> & val) {
    entries = val;
  }

  bool operator == (const CXTUResourceUsage & rhs) const
  {
    if (!(data == rhs.data))
      return false;
    if (!(entries == rhs.entries))
      return false;
    return true;
  }
  bool operator != (const CXTUResourceUsage &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const CXTUResourceUsage & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(CXTUResourceUsage &a, CXTUResourceUsage &b);

} // namespace

#endif