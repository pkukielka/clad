namespace * clad

include "Types.thrift"
include "Index.thrift"
include "TranslationUnit.thrift"
include "File.thrift"
include "Location.thrift"
include "Diagnostic.thrift"

service Clang {

  /**
   * ==================================================================================================================
   *                                     libclang: C Interface to Clang
   * ==================================================================================================================
   *
   * The C Interface to Clang provides a relatively small API that exposes
   * facilities for parsing source code into an abstract syntax tree (AST),
   * loading already-parsed ASTs, traversing the AST, associating
   * physical source locations with elements within the AST, and other
   * facilities that support Clang-based development tools.
   *
   * This C interface to Clang will never provide all of the information
   * representation stored in Clang's C++ AST, nor should it: the intent is to
   * maintain an API that is relatively stable from one release to the next,
   * providing only the basic functionality needed to support development tools.
   *
   * To avoid namespace pollution, data types are prefixed with "CX" and
   * functions are prefixed with "clang_".
   */


  /**
   * \brief Provides a shared context for creating translation units.
   *
   * It provides two options:
   *
   * - excludeDeclarationsFromPCH: When non-zero, allows enumeration of "local"
   * declarations (when loading any new translation units). A "local" declaration
   * is one that belongs in the translation unit itself and not in a precompiled
   * header that was used by the translation unit. If zero, all declarations
   * will be enumerated.
   *
   * Here is an example:
   *
   * \code
   *   // excludeDeclsFromPCH = 1, displayDiagnostics=1
   *   Idx = createIndex(1, 1);
   *
   *   // IndexTest.pch was produced with the following command:
   *   // "clang -x c IndexTest.h -emit-ast -o IndexTest.pch"
   *   TU = createTranslationUnit(Idx, "IndexTest.pch");
   *
   *   // This will load all the symbols from 'IndexTest.pch'
   *   visitChildren(clang_getTranslationUnitCursor(TU),
   *                       TranslationUnitVisitor, 0);
   *   disposeTranslationUnit(TU);
   *
   *   // This will load all the symbols from 'IndexTest.c', excluding symbols
   *   // from 'IndexTest.pch'.
   *   char *args[] = { "-Xclang", "-include-pch=IndexTest.pch" };
   *   TU = createTranslationUnitFromSourceFile(Idx, "IndexTest.c", 2, args,
   *                                                  0, 0);
   *   visitChildren(clang_getTranslationUnitCursor(TU),
   *                       TranslationUnitVisitor, 0);
   *   disposeTranslationUnit(TU);
   * \endcode
   *
   * This process of creating the 'pch', loading it separately, and using it (via
   * -include-pch) allows 'excludeDeclsFromPCH' to remove redundant callbacks
   * (which gives the indexer the same performance benefit as the compiler).
   */
  Index.CXIndex createIndex(
                        1: i32 excludeDeclarationsFromPCH,
                        2: i32 displayDiagnostics),

  /**
   * \brief Destroy the given index.
   *
   * The index must not be destroyed until all of the translation units created
   * within that index have been destroyed.
   */
  void disposeIndex(1: Index.CXIndex index),

  /**
   * \brief Sets general options associated with a CXIndex.
   *
   * For example:
   * \code
   * CXIndex idx = ...;
   * CXIndex_setGlobalOptions(idx,
   *     CXIndex_getGlobalOptions(idx) |
   *     CXGlobalOpt_ThreadBackgroundPriorityForIndexing);
   * \endcode
   *
   * \param options A bitmask of options, a bitwise OR of CXGlobalOpt_XXX flags.
   */
  void CXIndex_setGlobalOptions(
                        1: Index.CXIndex index,
                        2: Index.CXGlobalOptFlags options),

  /**
   * \brief Gets the general options associated with a CXIndex.
   *
   * \returns A bitmask of options, a bitwise OR of CXGlobalOpt_XXX flags that
   * are associated with the given CXIndex object.
   */
  Index.CXGlobalOptFlags CXIndex_getGlobalOptions(1: Index.CXIndex index),

  /**
   * ==================================================================================================================
   *                                      Translation unit manipulation
   * ==================================================================================================================
   *
   * The routines in this group provide the ability to create and destroy
   * translation units from files, either by parsing the contents of the files or
   * by reading in a serialized representation of a translation unit.
   */

  /**
   * \brief Get the original translation unit source file name.
   */
  string getTranslationUnitSpelling(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Return the CXTranslationUnit for a given source file and the provided
   * command line arguments one would pass to the compiler.
   *
   * Note: The 'source_filename' argument is optional.  If the caller provides a
   * NULL pointer, the name of the source file is expected to reside in the
   * specified command line arguments.
   *
   * Note: When encountered in 'clang_command_line_args', the following options
   * are ignored:
   *
   *   '-c'
   *   '-emit-ast'
   *   '-fsyntax-only'
   *   '-o \<output file>'  (both '-o' and '\<output file>' are ignored)
   *
   * \param idx The index object with which the translation unit will be
   * associated.
   *
   * \param source_filename The name of the source file to load, or empty if the
   * source file is included in \p command_line_args.
   *
   * \param command_line_args The command-line arguments that would be
   * passed to the \c clang executable if it were being invoked out-of-process.
   * These command-line options will be parsed and will affect how the translation
   * unit is parsed. Note that the following options are ignored: '-c',
   * '-emit-ast', '-fsyntax-only' (which is the default), and '-o \<output file>'.
   *
   * \param unsaved_files the files that have not yet been saved to disk
   * but may be required for code completion, including the contents of
   * those files.  The contents and name of these files (as specified by
   * CXUnsavedFile) are copied when necessary, so the client only needs to
   * guarantee their validity until the call to this function returns.
   */
  TranslationUnit.CXTranslationUnit createTranslationUnitFromSourceFile(
                        1: Index.CXIndex idx,
                        2: string source_filename,
                        3: list<string> command_line_args,
                        4: list<TranslationUnit.CXUnsavedFile> unsaved_files),

  /**
   * \brief Create a translation unit from an AST file (-emit-ast).
   */
  TranslationUnit.CXTranslationUnit createTranslationUnit(
                        1: Index.CXIndex idx,
                        2: string ast_filename),

  /**
   * \brief Returns the set of flags that is suitable for parsing a translation
   * unit that is being edited.
   *
   * The set of flags returned provide options for \c parseTranslationUnit()
   * to indicate that the translation unit is likely to be reparsed many times,
   * either explicitly (via \c reparseTranslationUnit()) or implicitly
   * (e.g., by code completion (\c codeCompletionAt())). The returned flag
   * set contains an unspecified set of optimizations (e.g., the precompiled
   * preamble) geared toward improving the performance of these routines. The
   * set of optimizations enabled may change from one version to the next.
   */
  Types.u32 defaultEditingTranslationUnitOptions(),

  /**
   * \brief Parse the given source file and the translation unit corresponding
   * to that file.
   *
   * This routine is the main entry point for the Clang C API, providing the
   * ability to parse a source file into a translation unit that can then be
   * queried by other functions in the API. This routine accepts a set of
   * command-line arguments so that the compilation can be configured in the same
   * way that the compiler is configured on the command line.
   *
   * \param idx The index object with which the translation unit will be
   * associated.
   *
   * \param source_filename The name of the source file to load, or NULL if the
   * source file is included in \p command_line_args.
   *
   * \param command_line_args The command-line arguments that would be
   * passed to the \c clang executable if it were being invoked out-of-process.
   * These command-line options will be parsed and will affect how the translation
   * unit is parsed. Note that the following options are ignored: '-c',
   * '-emit-ast', '-fsyntax-only' (which is the default), and '-o \<output file>'.
   *
   * \param unsaved_files the files that have not yet been saved to disk
   * but may be required for parsing, including the contents of
   * those files.  The contents and name of these files (as specified by
   * CXUnsavedFile) are copied when necessary, so the client only needs to
   * guarantee their validity until the call to this function returns.
   *
   * \param options A bitmask of options that affects how the translation unit
   * is managed but not its compilation. This should be a bitwise OR of the
   * CXTranslationUnit_XXX flags.
   *
   * \returns A new translation unit describing the parsed code and containing
   * any diagnostics produced by the compiler. If there is a failure from which
   * the compiler cannot recover, returns NULL.
   */
  TranslationUnit.CXTranslationUnit parseTranslationUnit(
                        1: Index.CXIndex idx,
                        2: string source_filename,
                        3: list<string> command_line_args,
                        4: list<TranslationUnit.CXUnsavedFile> unsaved_files,
                        5: Types.u32 options),

  /**
   * \brief Returns the set of flags that is suitable for saving a translation
   * unit.
   *
   * The set of flags returned provide options for
   * \c saveTranslationUnit() by default. The returned flag
   * set contains an unspecified set of options that save translation units with
   * the most commonly-requested data.
   */
  Types.u32 defaultSaveOptions(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Saves a translation unit into a serialized representation of
   * that translation unit on disk.
   *
   * Any translation unit that was parsed without error can be saved
   * into a file. The translation unit can then be deserialized into a
   * new \c CXTranslationUnit with \c createTranslationUnit() or,
   * if it is an incomplete translation unit that corresponds to a
   * header, used as a precompiled header when parsing other translation
   * units.
   *
   * \param unit The translation unit to save.
   *
   * \param filename The file to which the translation unit will be saved.
   *
   * \param options A bitmask of options that affects how the translation unit
   * is saved. This should be a bitwise OR of the
   * CXSaveTranslationUnit_XXX flags.
   *
   * \returns A value that will match one of the enumerators of the CXSaveError
   * enumeration. Zero (CXSaveError_None) indicates that the translation unit was
   * saved successfully, while a non-zero value indicates that a problem occurred.
   */
  TranslationUnit.CXSaveError saveTranslationUnit(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: string filename,
                        3: Types.u32 options),
  /**
   * \brief Destroy the specified CXTranslationUnit object.
   */
  void disposeTranslationUnit(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Returns the set of flags that is suitable for reparsing a translation
   * unit.
   *
   * The set of flags returned provide options for
   * \c reparseTranslationUnit() by default. The returned flag
   * set contains an unspecified set of optimizations geared toward common uses
   * of reparsing. The set of optimizations enabled may change from one version
   * to the next.
   */
  Types.u32 defaultReparseOptions(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Reparse the source files that produced this translation unit.
   *
   * This routine can be used to re-parse the source files that originally
   * created the given translation unit, for example because those source files
   * have changed (either on disk or as passed via \p unsaved_files). The
   * source code will be reparsed with the same command-line options as it
   * was originally parsed.
   *
   * Reparsing a translation unit invalidates all cursors and source locations
   * that refer into that translation unit. This makes reparsing a translation
   * unit semantically equivalent to destroying the translation unit and then
   * creating a new translation unit with the same command-line arguments.
   * However, it may be more efficient to reparse a translation
   * unit using this routine.
   *
   * \param unit The translation unit whose contents will be re-parsed. The
   * translation unit must originally have been built with
   * \c createTranslationUnitFromSourceFile().
   *
   * \param unsaved_files The files that have not yet been saved to disk
   * but may be required for parsing, including the contents of
   * those files.  The contents and name of these files (as specified by
   * CXUnsavedFile) are copied when necessary, so the client only needs to
   * guarantee their validity until the call to this function returns.
   *
   * \param options A bitset of options composed of the flags in CXReparse_Flags.
   * The function \c defaultReparseOptions() produces a default set of
   * options recommended for most uses, based on the translation unit.
   *
   * \returns 0 if the sources could be reparsed. A non-zero value will be
   * returned if reparsing was impossible, such that the translation unit is
   * invalid. In such cases, the only valid call for \p TU is
   * \c disposeTranslationUnit(TU).
   */
  i32 reparseTranslationUnit(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: list<TranslationUnit.CXUnsavedFile> unsaved_files,
                        3: Types.u32 options),

  /**
    * \brief Returns the human-readable string that represents the name
    *  of the memory category.
    */
  string getTUResourceUsageName(
                        1: TranslationUnit.CXTUResourceUsageKind kind),

  /**
    * \brief Return the memory usage of a translation unit.  This object
    *  should be released with disposeCXTUResourceUsage().
    */
  TranslationUnit.CXTUResourceUsage getCXTUResourceUsage(
                        1: TranslationUnit.CXTranslationUnit unit),

  /**
   * ==================================================================================================================
   *                                         File manipulation routines
   * ==================================================================================================================
   */

  /**
   * \brief Retrieve the complete file and path name of the given file.
   */
  string getFileName(1: File.CXFile file),

  /**
   * \brief Retrieve the last modification time of the given file.
   */
  Types.t64 getFileTime(1: File.CXFile file),

  /**
   * \brief Determine whether the given header is guarded against
   * multiple inclusions, either with the conventional
   * \#ifndef/\#define/\#endif macro guards or with \#pragma once.
   */
  Types.u32 isFileMultipleIncludeGuarded(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: File.CXFile file),

  /**
   * \brief Retrieve a file handle within the given translation unit.
   *
   * \param tu the translation unit
   *
   * \param file_name the name of the file.
   *
   * \returns the file handle for the named file in the translation unit \p tu,
   * or a NULL file handle if the file was not a part of this translation unit.
   */
  File.CXFile getFile(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: string filename),

  /**
   * ==================================================================================================================
   *                                          Physical source locations
   * ==================================================================================================================
   *
   * Clang represents physical source locations in its abstract syntax tree in
   * great detail, with file, line, and column information for the majority of
   * the tokens parsed in the source code. These data types and functions are
   * used to represent source location information, either for a particular
   * point in the program or for a range of points in the program, and extract
   * specific location information from those data types.
   */

  /**
   * \brief Retrieve a NULL (invalid) source location.
   */
  Location.CXSourceLocation getNullLocation(),

  /**
   * \brief Determine whether two source locations, which must refer into
   * the same translation unit, refer to exactly the same point in the source
   * code.
   *
   * \returns non-zero if the source locations refer to the same location, zero
   * if they refer to different locations.
   */
  Types.u32 equalLocations(
                        1: Location.CXSourceLocation loc1,
                        2: Location.CXSourceLocation loc2),

  /**
   * \brief Retrieves the source location associated with a given file/line/column
   * in a particular translation unit.
   */
  Location.CXSourceLocation getLocation(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: File.CXFile file,
                        3: Types.u32 line,
                        4: Types.u32 column),
  /**
   * \brief Retrieves the source location associated with a given character offset
   * in a particular translation unit.
   */
  Location.CXSourceLocation getLocationForOffset(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: File.CXFile file,
                        3: Types.u32 offset),

  /**
   * \brief Retrieve a NULL (invalid) source range.
   */
  Location.CXSourceRange getNullRange(),

  /**
   * \brief Retrieve a source range given the beginning and ending source
   * locations.
   */
  Location.CXSourceRange getRange(
                        1: Location.CXSourceLocation sourceBegin,
                        2: Location.CXSourceLocation sourceEnd),

  /**
   * \brief Determine whether two ranges are equivalent.
   *
   * \returns non-zero if the ranges are the same, zero if they differ.
   */
  Types.u32 equalRanges(
                        1: Location.CXSourceRange range1,
                        2: Location.CXSourceRange range2),

  /**
   * \brief Returns non-zero if \p range is null.
   */
  i32 isRangeNull(1: Location.CXSourceRange range),

  /**
   * \brief Retrieve the file, line, column, and offset represented by
   * the given source location.
   *
   * If the location refers into a macro expansion, retrieves the
   * location of the macro expansion.
   */
  Location.CXSourcePosition getExpansionLocation(
                        1: Location.CXSourceLocation location),

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
   * whereas getExpansionLocation would have returned
   *
   * File: somefile.c Line: 3 Column: 12
   *
   * \param location the location within a source file that will be decomposed
   * into its parts.
   */
  Location.CXSourcePosition getPresumedLocation(
                        1: Location.CXSourceLocation location),

  /**
   * \brief Legacy API to retrieve the file, line, column, and offset represented
   * by the given source location.
   *
   * This interface has been replaced by the newer interface
   * #clang_getExpansionLocation(). See that interface's documentation for
   * details.
   */
  Location.CXSourcePosition getInstantiationLocation(
                        1: Location.CXSourceLocation location),

  /**
   * \brief Retrieve the file, line, column, and offset represented by
   * the given source location.
   *
   * If the location refers into a macro instantiation, return where the
   * location was originally spelled in the source file.
   */
  Location.CXSourcePosition getSpellingLocation(
                        1: Location.CXSourceLocation location),

  /**
   * \brief Retrieve a source location representing the first character within a
   * source range.
   */
  Location.CXSourceLocation getRangeStart(
                        1: Location.CXSourceRange range),

  /**
   * \brief Retrieve a source location representing the last character within a
   * source range.
   */
  Location.CXSourceLocation getRangeEnd(
                        1: Location.CXSourceRange range),

  /**
   * ==================================================================================================================
   *                                          Diagnostic reporting
   * ==================================================================================================================
   */

  /**
   * \brief Determine the number of diagnostics in a CXDiagnosticSet.
   */
  Types.u32 getNumDiagnosticsInSet(1: Diagnostic.CXDiagnosticSet diags),

  /**
   * \brief Retrieve a diagnostic associated with the given CXDiagnosticSet.
   *
   * \param diags the CXDiagnosticSet to query.
   * \param dndex the zero-based diagnostic number to retrieve.
   *
   * \returns the requested diagnostic. This diagnostic must be freed
   * via a call to \c disposeDiagnostic().
   */
  Diagnostic.CXDiagnostic getDiagnosticInSet(
                        1: Diagnostic.CXDiagnosticSet diags,
                        2: Types.u32 index),

  /**
   * \brief Deserialize a set of diagnostics from a Clang diagnostics bitcode
   * file.
   *
   * \param file The name of the file to deserialize.
   *
   * \returns A loaded CXDiagnosticSet if successful, and NULL otherwise.  These
   * diagnostics should be released using disposeDiagnosticSet().
   */
  Diagnostic.CXDiagnosticSet loadDiagnostics(1: string filename)
                        throws (1: Diagnostic.CXLoadDiagException e),

  /**
   * \brief Release a CXDiagnosticSet and all of its contained diagnostics.
   */
  void disposeDiagnosticSet(1: Diagnostic.CXDiagnosticSet diagnosticSet),

  /**
   * \brief Retrieve the child diagnostics of a CXDiagnostic.
   *
   * This CXDiagnosticSet does not need to be released by
   * diposeDiagnosticSet.
   */
  Diagnostic.CXDiagnosticSet getChildDiagnostics(
                        1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Determine the number of diagnostics produced for the given
   * translation unit.
   */
  Types.u32 getNumDiagnostics(1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Retrieve a diagnostic associated with the given translation unit.
   *
   * \param Unit the translation unit to query.
   * \param Index the zero-based diagnostic number to retrieve.
   *
   * \returns the requested diagnostic. This diagnostic must be freed
   * via a call to \c disposeDiagnostic().
   */
  Diagnostic.CXDiagnostic getDiagnostic(
                        1: TranslationUnit.CXTranslationUnit unit,
                        2: Types.u32 index),

  /**
   * \brief Retrieve the complete set of diagnostics associated with a
   *        translation unit.
   *
   * \param Unit the translation unit to query.
   */
  Diagnostic.CXDiagnosticSet getDiagnosticSetFromTU(
                        1: TranslationUnit.CXTranslationUnit unit),

  /**
   * \brief Destroy a diagnostic.
   */
  void disposeDiagnostic(1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Format the given diagnostic in a manner that is suitable for display.
   *
   * This routine will format the given diagnostic to a string, rendering
   * the diagnostic according to the various options given. The
   * \c defaultDiagnosticDisplayOptions() function returns the set of
   * options that most closely mimics the behavior of the clang compiler.
   *
   * \param diagnostic The diagnostic to print.
   *
   * \param options A set of options that control the diagnostic display,
   * created by combining \c CXDiagnosticDisplayOptions values.
   *
   * \returns A new string containing for formatted diagnostic.
   */
  string formatDiagnostic(
                        1: Diagnostic.CXDiagnostic diagnostic,
                        2: Types.u32 options),

  /**
   * \brief Retrieve the set of display options most similar to the
   * default behavior of the clang compiler.
   *
   * \returns A set of display options suitable for use with \c
   * displayDiagnostic().
   */
  Types.u32 defaultDiagnosticDisplayOptions(),

  /**
   * \brief Determine the severity of the given diagnostic.
   */
  Diagnostic.CXDiagnosticSeverity getDiagnosticSeverity(
                        1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the source location of the given diagnostic.
   *
   * This location is where Clang would print the caret ('^') when
   * displaying the diagnostic on the command line.
   */
  Location.CXSourceLocation getDiagnosticLocation(
                        1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the text of the given diagnostic.
   */
  string getDiagnosticSpelling(
                        1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the name of the command-line option that enabled this
   * diagnostic as well as command-line option used to enable this
   * warning, such as "-Wconversion" or "-pedantic"
   *
   * \param diagnostic The diagnostic to be queried.
   *
   * \returns CXDiagnosticOption structure containing diagnostics options
   */
  Diagnostic.CXDiagnosticOption getDiagnosticOption(
                        1: Diagnostic.CXDiagnostic diagnostic),

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
  Types.u32 getDiagnosticCategory(
                        1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Retrieve the diagnostic category text for a given diagnostic.
   *
   * \returns The text of the given diagnostic category.
   */
  string getDiagnosticCategoryText(1: Diagnostic.CXDiagnostic diagnostic),

  /**
   * \brief Determine the number of source ranges associated with the given
   * diagnostic.
   */
  Types.u32 getDiagnosticNumRanges(1: Diagnostic.CXDiagnostic diagnostic),

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
   Location.CXSourceRange getDiagnosticRange(
                        1: Diagnostic.CXDiagnostic diagnostic,
                        2: Types.u32 range),

  /**
   * \brief Determine the number of fix-it hints associated with the
   * given diagnostic.
   */
  Types.u32 getDiagnosticNumFixIts(
                        1: Diagnostic.CXDiagnostic diagnostic),

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
  Diagnostic.CXDiagnosticFixIt getDiagnosticFixIt(
                        1: Diagnostic.CXDiagnostic siagnostic,
                        2: Types.u32 fix_it)
}