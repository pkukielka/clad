namespace * clang.thrift

/**
 * Physical source locations
 *
 * Clang represents physical source locations in its abstract syntax tree in
 * great detail, with file, line, and column information for the majority of
 * the tokens parsed in the source code. These data types and functions are
 * used to represent source location information, either for a particular
 * point in the program or for a range of points in the program, and extract
 * specific location information from those data types.
 */

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

service Location {
  /**
   * \brief Retrieve a NULL (invalid) source location.
   */
  CXSourceLocation clang_getNullLocation(),

  /**
   * \brief Determine whether two source locations, which must refer into
   * the same translation unit, refer to exactly the same point in the source
   * code.
   *
   * \returns non-zero if the source locations refer to the same location, zero
   * if they refer to different locations.
   */
  Types.u32 clang_equalLocations(1: CXSourceLocation loc1, 2: CXSourceLocation loc2),

  /**
   * \brief Retrieves the source location associated with a given file/line/column
   * in a particular translation unit.
   */
  CXSourceLocation clang_getLocation(1: TranslationUnit.CXTranslationUnit tu, 2: File.CXFile file,
                                     3: Types.u32 line,
                                     4: Types.u32 column),
  /**
   * \brief Retrieves the source location associated with a given character offset
   * in a particular translation unit.
   */
  CXSourceLocation clang_getLocationForOffset(1: TranslationUnit.CXTranslationUnit tu, 
                                              2: File.CXFile file,
                                              3: Types.u32 offset),

  /**
   * \brief Retrieve a NULL (invalid) source range.
   */
  CXSourceRange clang_getNullRange(),

  /**
   * \brief Retrieve a source range given the beginning and ending source
   * locations.
   */
  CXSourceRange clang_getRange(1: CXSourceLocation sourceBegin, 
                               2: CXSourceLocation sourceEnd),

  /**
   * \brief Determine whether two ranges are equivalent.
   *
   * \returns non-zero if the ranges are the same, zero if they differ.
   */
  Types.u32 clang_equalRanges(1: CXSourceRange range1, 2: CXSourceRange range2),

  /**
   * \brief Returns non-zero if \p range is null.
   */
  Types.int clang_Range_isNull(1: CXSourceRange range),

  /**
   * \brief Retrieve the file, line, column, and offset represented by
   * the given source location.
   *
   * If the location refers into a macro expansion, retrieves the
   * location of the macro expansion.
   */
  CXSourcePosition clang_getExpansionLocation(1: CXSourceLocation location),

  /**
   * \brief Retrieve the file, line, column, and offset represented by
   * the given source location, as specified in a # line directive.
   *
   * Example: given the following source code in a file somefile.c
   *
   * \code
   * #123 "dummy.c" 1
   *
   * static int func(void)
   * {
   *     return 0;
   * }
   * \endcode
   *
   * the location information returned by this function would be
   *
   * File: dummy.c Line: 124 Column: 12
   *
   * whereas clang_getExpansionLocation would have returned
   *
   * File: somefile.c Line: 3 Column: 12
   *
   * \param location the location within a source file that will be decomposed
   * into its parts.
   */
  CXSourcePosition clang_getPresumedLocation(1: CXSourceLocation location),

  /**
   * \brief Legacy API to retrieve the file, line, column, and offset represented
   * by the given source location.
   *
   * This interface has been replaced by the newer interface
   * #clang_getExpansionLocation(). See that interface's documentation for
   * details.
   */
  CXSourcePosition clang_getInstantiationLocation(1: CXSourceLocation location),

  /**
   * \brief Retrieve the file, line, column, and offset represented by
   * the given source location.
   *
   * If the location refers into a macro instantiation, return where the
   * location was originally spelled in the source file.
   */
  CXSourcePosition clang_getSpellingLocation(1: CXSourceLocation location),

  /**
   * \brief Retrieve a source location representing the first character within a
   * source range.
   */
  CXSourceLocation clang_getRangeStart(1: CXSourceRange range),

  /**
   * \brief Retrieve a source location representing the last character within a
   * source range.
   */
  CXSourceLocation clang_getRangeEnd(1: CXSourceRange range)
}