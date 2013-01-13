namespace * clad

include "Types.thrift"
include "File.thrift"
include "TranslationUnit.thrift"

/**
 * \brief Identifies a specific source location within a translation
 * unit.
 *
 * Use clang_getExpansionLocation() or clang_getSpellingLocation()
 * to map a source location to a particular file, line, and column.
 */
struct CXSourceLocation {
  1: list<Types.ResourceId> ptr_data,
  2: Types.u32 int_data
}

/**
 * \brief Identifies a half-open character range in the source code.
 *
 * Use clang_getRangeStart() and clang_getRangeEnd() to retrieve the
 * starting and end locations from a source range, respectively.
 */
struct CXSourceRange {
  1: list<Types.ResourceId> ptr_data,
  2: Types.u32 begin_int_data,
  3: Types.u32 end_int_data
}

struct CXSourcePosition {
  1: File.CXFile file,
  2: string filename,
  3: Types.u32 line,
  4: Types.u32 column,
  5: Types.u32 offset
}
