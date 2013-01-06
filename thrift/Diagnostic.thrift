namespace * clang.thrift

/**
 * Diagnostic reporting
 */

include "Types.thrift"
include "Location.thrift"
include "TranslationUnit.thrift"

/**
 * \brief Describes the severity of a particular diagnostic.
 */
enum CXDiagnosticSeverity {
  /**
   * \brief A diagnostic that has been suppressed, e.g., by a command-line
   * option.
   */
  CXDiagnostic_Ignored = 0,

  /**
   * \brief This diagnostic is a note that should be attached to the
   * previous (non-note) diagnostic.
   */
  CXDiagnostic_Note    = 1,

  /**
   * \brief This diagnostic indicates suspicious code that may not be
   * wrong.
   */
  CXDiagnostic_Warning = 2,

  /**
   * \brief This diagnostic indicates that the code is ill-formed.
   */
  CXDiagnostic_Error   = 3,

  /**
   * \brief This diagnostic indicates that the code is ill-formed such
   * that future parser recovery is unlikely to produce useful
   * results.
   */
  CXDiagnostic_Fatal   = 4
}

/**
 * \brief A single diagnostic, containing the diagnostic's severity,
 * location, text, source ranges, and fix-it hints.
 */
typedef Types.ResourceId CXDiagnostic

/**
 * \brief A group of CXDiagnostics.
 */
typedef Types.ResourceId CXDiagnosticSet

/**
 * \brief Describes the kind of error that occurred (if any) in a call to
 * \c clang_loadDiagnostics.
 */
enum CXLoadDiag_Error {
  /**
   * \brief Indicates that no error occurred.
   */
  CXLoadDiag_None = 0,
  
  /**
   * \brief Indicates that an unknown error occurred while attempting to
   * deserialize diagnostics.
   */
  CXLoadDiag_Unknown = 1,
  
  /**
   * \brief Indicates that the file containing the serialized diagnostics
   * could not be opened.
   */
  CXLoadDiag_CannotLoad = 2,
  
  /**
   * \brief Indicates that the serialized diagnostics file is invalid or
   * corrupt.
   */
  CXLoadDiag_InvalidFile = 3
}

exception CXLoadDiagException {
  1: CXLoadDiag_Error Error,
  2: string ErrorString
}

/**
 * \brief Options to control the display of diagnostics.
 *
 * The values in this enum are meant to be combined to customize the
 * behavior of \c clang_displayDiagnostic().
 */
enum CXDiagnosticDisplayOptions {
  /**
   * \brief Display the source-location information where the
   * diagnostic was located.
   *
   * When set, diagnostics will be prefixed by the file, line, and
   * (optionally) column to which the diagnostic refers. For example,
   *
   * \code
   * test.c:28: warning: extra tokens at end of #endif directive
   * \endcode
   *
   * This option corresponds to the clang flag \c -fshow-source-location.
   */
  CXDiagnostic_DisplaySourceLocation = 0x01,

  /**
   * \brief If displaying the source-location information of the
   * diagnostic, also include the column number.
   *
   * This option corresponds to the clang flag \c -fshow-column.
   */
  CXDiagnostic_DisplayColumn = 0x02,

  /**
   * \brief If displaying the source-location information of the
   * diagnostic, also include information about source ranges in a
   * machine-parsable format.
   *
   * This option corresponds to the clang flag
   * \c -fdiagnostics-print-source-range-info.
   */
  CXDiagnostic_DisplaySourceRanges = 0x04,
  
  /**
   * \brief Display the option name associated with this diagnostic, if any.
   *
   * The option name displayed (e.g., -Wconversion) will be placed in brackets
   * after the diagnostic text. This option corresponds to the clang flag
   * \c -fdiagnostics-show-option.
   */
  CXDiagnostic_DisplayOption = 0x08,
  
  /**
   * \brief Display the category number associated with this diagnostic, if any.
   *
   * The category number is displayed within brackets after the diagnostic text.
   * This option corresponds to the clang flag 
   * \c -fdiagnostics-show-category=id.
   */
  CXDiagnostic_DisplayCategoryId = 0x10,

  /**
   * \brief Display the category name associated with this diagnostic, if any.
   *
   * The category name is displayed within brackets after the diagnostic text.
   * This option corresponds to the clang flag 
   * \c -fdiagnostics-show-category=name.
   */
  CXDiagnostic_DisplayCategoryName = 0x20
}

struct CXDiagnosticOption {
  /** 
  /* A string that contains the command-line option used to enable this
   * warning, such as "-Wconversion" or "-pedantic". 
   */
  1: string Enable,

  /**
  /* option that disables this diagnostic (if any).
  */
  2: string Disable
}

struct CXDiagnosticFixIt {
  /**
   * \brief The source range whose contents will be replaced with the 
   * replacement string.
   *
   * Note that source ranges are half-open ranges [a, b), so the source code 
   * should be replaced from a and up to (but not including) b.
   */
  1: Location.CXSourceRange ReplacementRange,

  /**
   * \brief A string containing text that should replace the source code 
   * indicated by the \c ReplacementRange.
   */
  2: string ReplacementText
}

service Diagnostic {
  /**
   * \brief Determine the number of diagnostics in a CXDiagnosticSet.
   */
  Types.uint clang_getNumDiagnosticsInSet(1: CXDiagnosticSet diags),

  /**
   * \brief Retrieve a diagnostic associated with the given CXDiagnosticSet.
   *
   * \param diags the CXDiagnosticSet to query.
   * \param dndex the zero-based diagnostic number to retrieve.
   *
   * \returns the requested diagnostic. This diagnostic must be freed
   * via a call to \c clang_disposeDiagnostic().
   */
  CXDiagnostic clang_getDiagnosticInSet(1: CXDiagnosticSet diags,
                                        2: Types.uint index),

  /**
   * \brief Deserialize a set of diagnostics from a Clang diagnostics bitcode
   * file.
   *
   * \param file The name of the file to deserialize.
   *
   * \returns A loaded CXDiagnosticSet if successful, and NULL otherwise.  These
   * diagnostics should be released using clang_disposeDiagnosticSet().
   */
  CXDiagnosticSet clang_loadDiagnostics(1: string filename) 
      throws (1: CXLoadDiagException e),

  /**
   * \brief Release a CXDiagnosticSet and all of its contained diagnostics.
   */
  void clang_disposeDiagnosticSet(1: CXDiagnosticSet diagnosticSet),

  /**
   * \brief Retrieve the child diagnostics of a CXDiagnostic. 
   *
   * This CXDiagnosticSet does not need to be released by
   * clang_diposeDiagnosticSet.
   */
  CXDiagnosticSet clang_getChildDiagnostics(1: CXDiagnostic diagnostic),

  /**
   * \brief Determine the number of diagnostics produced for the given
   * translation unit.
   */
  Types.uint clang_getNumDiagnostics(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Retrieve a diagnostic associated with the given translation unit.
   *
   * \param Unit the translation unit to query.
   * \param Index the zero-based diagnostic number to retrieve.
   *
   * \returns the requested diagnostic. This diagnostic must be freed
   * via a call to \c clang_disposeDiagnostic().
   */
  CXDiagnostic clang_getDiagnostic(1: TranslationUnit.CXTranslationUnit unit,
                                   2: Types.uint index),

  /**
   * \brief Retrieve the complete set of diagnostics associated with a
   *        translation unit.
   *
   * \param Unit the translation unit to query.
   */
  CXDiagnosticSet clang_getDiagnosticSetFromTU(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Destroy a diagnostic.
   */
  void clang_disposeDiagnostic(1: CXDiagnostic diagnostic),

  /**
   * \brief Format the given diagnostic in a manner that is suitable for display.
   *
   * This routine will format the given diagnostic to a string, rendering
   * the diagnostic according to the various options given. The
   * \c clang_defaultDiagnosticDisplayOptions() function returns the set of
   * options that most closely mimics the behavior of the clang compiler.
   *
   * \param diagnostic The diagnostic to print.
   *
   * \param options A set of options that control the diagnostic display,
   * created by combining \c CXDiagnosticDisplayOptions values.
   *
   * \returns A new string containing for formatted diagnostic.
   */
  string clang_formatDiagnostic(1: CXDiagnostic diagnostic,
                                  2: Types.uint options),

  /**
   * \brief Retrieve the set of display options most similar to the
   * default behavior of the clang compiler.
   *
   * \returns A set of display options suitable for use with \c
   * clang_displayDiagnostic().
   */
  Types.uint clang_defaultDiagnosticDisplayOptions(),

  /**
   * \brief Determine the severity of the given diagnostic.
   */
  CXDiagnosticSeverity clang_getDiagnosticSeverity(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the source location of the given diagnostic.
   *
   * This location is where Clang would print the caret ('^') when
   * displaying the diagnostic on the command line.
   */
  Location.CXSourceLocation clang_getDiagnosticLocation(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the text of the given diagnostic.
   */
  string clang_getDiagnosticSpelling(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the name of the command-line option that enabled this
   * diagnostic as well as command-line option used to enable this
   * warning, such as "-Wconversion" or "-pedantic"
   *
   * \param diagnostic The diagnostic to be queried.
   *
   * \returns CXDiagnosticOption structure containing diagnostics options
   */
  CXDiagnosticOption clang_getDiagnosticOption(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the category number for this diagnostic.
   *
   * Diagnostics can be categorized into groups along with other, related
   * diagnostics (e.g., diagnostics under the same warning flag). This routine 
   * retrieves the category number for the given diagnostic.
   *
   * \returns The number of the category that contains this diagnostic, or zero
   * if this diagnostic is uncategorized.
   */
  Types.uint clang_getDiagnosticCategory(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the name of a particular diagnostic category.  This
   *  is now deprecated.  Use clang_getDiagnosticCategoryText()
   *  instead.
   *
   * \param category A diagnostic category number, as returned by 
   * \c clang_getDiagnosticCategory().
   *
   * \returns The name of the given diagnostic category.
   */
  string clang_getDiagnosticCategoryName(1: Types.uint category),

  /**
   * \brief Retrieve the diagnostic category text for a given diagnostic.
   *
   * \returns The text of the given diagnostic category.
   */
  string clang_getDiagnosticCategoryText(1: CXDiagnostic diagnostic),
    
  /**
   * \brief Determine the number of source ranges associated with the given
   * diagnostic.
   */
  Types.uint clang_getDiagnosticNumRanges(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve a source range associated with the diagnostic.
   *
   * A diagnostic's source ranges highlight important elements in the source
   * code. On the command line, Clang displays source ranges by
   * underlining them with '~' characters.
   *
   * \param diagnostic the diagnostic whose range is being extracted.
   *
   * \param range the zero-based index specifying which range to
   *
   * \returns the requested source range.
   */
   Location.CXSourceRange clang_getDiagnosticRange(1: CXDiagnostic diagnostic,
                                         2: Types.uint range),

  /**
   * \brief Determine the number of fix-it hints associated with the
   * given diagnostic.
   */
  Types.uint clang_getDiagnosticNumFixIts(1: CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the replacement information for a given fix-it.
   *
   * Fix-its are described in terms of a source range whose contents
   * should be replaced by a string. This approach generalizes over
   * three kinds of operations: removal of source code (the range covers
   * the code to be removed and the replacement string is empty),
   * replacement of source code (the range covers the code to be
   * replaced and the replacement string provides the new code), and
   * insertion (both the start and end of the range point at the
   * insertion location, and the replacement string provides the text to
   * insert).
   *
   * \param diagnostic The diagnostic whose fix-its are being queried.
   *
   * \param FixIt The zero-based index of the fix-it.
   *
   * \returns Structure containing replacement range and text
   */
  CXDiagnosticFixIt clang_getDiagnosticFixIt(1: CXDiagnostic Diagnostic,
                                             2: Types.uint FixIt)
}
