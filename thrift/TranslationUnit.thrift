namespace * clang.thrift

/**
 * Translation unit manipulation
 *
 * The routines in this group provide the ability to create and destroy
 * translation units from files, either by parsing the contents of the files or
 * by reading in a serialized representation of a translation unit.
 */

include "Types.thrift"
include "Index.thrift"

/**
 * \brief A single translation unit, which resides in an index.
 */
typedef Types.ResourceId CXTranslationUnit

 /**
 * \brief Provides the contents of a file that has not yet been saved to disk.
 *
 * Each CXUnsavedFile instance provides the name of a file on the
 * system along with the current contents of that file that have not
 * yet been saved to disk.
 */
struct CXUnsavedFile {
  /**
   * \brief The file whose contents have not yet been saved.
   *
   * This file must already exist in the file system.
   */
  1: string Filename,

  /**
   * \brief A buffer containing the unsaved contents of this file.
   */
  2: string Contents,

  /**
   * \brief The length of the unsaved contents of this buffer.
   */
  3: Types.u32 Length
}


/**
 * \brief Flags that control the creation of translation units.
 *
 * The enumerators in this enumeration type are meant to be bitwise
 * ORed together to specify which options should be used when
 * constructing the translation unit.
 */
enum CXTranslationUnit_Flags {
  /**
   * \brief Used to indicate that no special translation-unit options are
   * needed.
   */
  CXTranslationUnit_None = 0x0,

  /**
   * \brief Used to indicate that the parser should construct a "detailed"
   * preprocessing record, including all macro definitions and instantiations.
   *
   * Constructing a detailed preprocessing record requires more memory
   * and time to parse, since the information contained in the record
   * is usually not retained. However, it can be useful for
   * applications that require more detailed information about the
   * behavior of the preprocessor.
   */
  CXTranslationUnit_DetailedPreprocessingRecord = 0x01,

  /**
   * \brief Used to indicate that the translation unit is incomplete.
   *
   * When a translation unit is considered "incomplete", semantic
   * analysis that is typically performed at the end of the
   * translation unit will be suppressed. For example, this suppresses
   * the completion of tentative declarations in C and of
   * instantiation of implicitly-instantiation function templates in
   * C++. This option is typically used when parsing a header with the
   * intent of producing a precompiled header.
   */
  CXTranslationUnit_Incomplete = 0x02,
  
  /**
   * \brief Used to indicate that the translation unit should be built with an 
   * implicit precompiled header for the preamble.
   *
   * An implicit precompiled header is used as an optimization when a
   * particular translation unit is likely to be reparsed many times
   * when the sources aren't changing that often. In this case, an
   * implicit precompiled header will be built containing all of the
   * initial includes at the top of the main file (what we refer to as
   * the "preamble" of the file). In subsequent parses, if the
   * preamble or the files in it have not changed, \c
   * clang_reparseTranslationUnit() will re-use the implicit
   * precompiled header to improve parsing performance.
   */
  CXTranslationUnit_PrecompiledPreamble = 0x04,
  
  /**
   * \brief Used to indicate that the translation unit should cache some
   * code-completion results with each reparse of the source file.
   *
   * Caching of code-completion results is a performance optimization that
   * introduces some overhead to reparsing but improves the performance of
   * code-completion operations.
   */
  CXTranslationUnit_CacheCompletionResults = 0x08,

  /**
   * \brief Used to indicate that the translation unit will be serialized with
   * \c clang_saveTranslationUnit.
   *
   * This option is typically used when parsing a header with the intent of
   * producing a precompiled header.
   */
  CXTranslationUnit_ForSerialization = 0x10,

  /**
   * \brief DEPRECATED: Enabled chained precompiled preambles in C++.
   *
   * Note: this is a *temporary* option that is available only while
   * we are testing C++ precompiled preamble support. It is deprecated.
   */
  CXTranslationUnit_CXXChainedPCH = 0x20,

  /**
   * \brief Used to indicate that function/method bodies should be skipped while
   * parsing.
   *
   * This option can be used to search for declarations/definitions while
   * ignoring the usages.
   */
  CXTranslationUnit_SkipFunctionBodies = 0x40,

  /**
   * \brief Used to indicate that brief documentation comments should be
   * included into the set of code completions returned from this translation
   * unit.
   */
  CXTranslationUnit_IncludeBriefCommentsInCodeCompletion = 0x80
}

/**
 * \brief Flags that control how translation units are saved.
 *
 * The enumerators in this enumeration type are meant to be bitwise
 * ORed together to specify which options should be used when
 * saving the translation unit.
 */
enum CXSaveTranslationUnit_Flags {
  /**
   * \brief Used to indicate that no special saving options are needed.
   */
  CXSaveTranslationUnit_None = 0x0
}


/**
 * \brief Describes the kind of error that occurred (if any) in a call to
 * \c clang_saveTranslationUnit().
 */
enum CXSaveError {
  /**
   * \brief Indicates that no error occurred while saving a translation unit.
   */
  CXSaveError_None = 0,
  
  /**
   * \brief Indicates that an unknown error occurred while attempting to save
   * the file.
   *
   * This error typically indicates that file I/O failed when attempting to 
   * write the file.
   */
  CXSaveError_Unknown = 1,
  
  /**
   * \brief Indicates that errors during translation prevented this attempt
   * to save the translation unit.
   * 
   * Errors that prevent the translation unit from being saved can be
   * extracted using \c clang_getNumDiagnostics() and \c clang_getDiagnostic().
   */
  CXSaveError_TranslationErrors = 2,
  
  /**
   * \brief Indicates that the translation unit to be saved was somehow
   * invalid (e.g., NULL).
   */
  CXSaveError_InvalidTU = 3
}

/**
 * \brief Flags that control the reparsing of translation units.
 *
 * The enumerators in this enumeration type are meant to be bitwise
 * ORed together to specify which options should be used when
 * reparsing the translation unit.
 */
enum CXReparse_Flags {
  /**
   * \brief Used to indicate that no special reparsing options are needed.
   */
  CXReparse_None = 0x0
}

/**
  * \brief Categorizes how memory is being used by a translation unit.
  */
enum CXTUResourceUsageKind {
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
  CXTUResourceUsage_MEMORY_IN_BYTES_BEGIN = 1,  // = CXTUResourceUsage_AST
  CXTUResourceUsage_MEMORY_IN_BYTES_END = 14,   // = CXTUResourceUsage_Preprocessor_HeaderSearch
  CXTUResourceUsage_First = 1,                  // = CXTUResourceUsage_AST
  CXTUResourceUsage_Last = 14                   // = CXTUResourceUsage_Preprocessor_HeaderSearch
}

struct CXTUResourceUsageEntry {
  /* \brief The memory usage category. */
  1: CXTUResourceUsageKind kind,
  /* \brief Amount of resources used. 
      The units will depend on the resource kind. */
  2: Types.u64 amount
}

/**
  * \brief The memory usage of a CXTranslationUnit, broken into categories.
  */
struct CXTUResourceUsage {
  /* \brief Private data member, used for queries. */
  1: Types.ResourceId data,

  /* \brief An array of key-value pairs, representing the breakdown of memory
            usage. */
  2: list<CXTUResourceUsageEntry> entries
}

service TranslationUnit {
  /**
   * \brief Get the original translation unit source file name.
   */
  string clang_getTranslationUnitSpelling(1: CXTranslationUnit unit),

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
   * source file is included in \p clang_command_line_args.
   *
   * \param clang_command_line_args The command-line arguments that would be
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
  CXTranslationUnit clang_createTranslationUnitFromSourceFile(
                                           1: Index.CXIndex idx,
                                           2: string source_filename,
                                           3: list<string> clang_command_line_args,
                                           4: list<CXUnsavedFile> unsaved_files),

  /**
   * \brief Create a translation unit from an AST file (-emit-ast).
   */
  CXTranslationUnit clang_createTranslationUnit(1: Index.CXIndex idx,
                                                2: string ast_filename),

  /**
   * \brief Returns the set of flags that is suitable for parsing a translation
   * unit that is being edited.
   *
   * The set of flags returned provide options for \c clang_parseTranslationUnit()
   * to indicate that the translation unit is likely to be reparsed many times,
   * either explicitly (via \c clang_reparseTranslationUnit()) or implicitly
   * (e.g., by code completion (\c clang_codeCompletionAt())). The returned flag
   * set contains an unspecified set of optimizations (e.g., the precompiled 
   * preamble) geared toward improving the performance of these routines. The
   * set of optimizations enabled may change from one version to the next.
   */
  Types.u32 clang_defaultEditingTranslationUnitOptions(),
    
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
  CXTranslationUnit clang_parseTranslationUnit(1: Index.CXIndex idx,
                                               2: string source_filename,
                                               3: list<string> command_line_args,
                                               4: list<CXUnsavedFile> unsaved_files,
                                               5: Types.u32 options),

  /**
   * \brief Returns the set of flags that is suitable for saving a translation
   * unit.
   *
   * The set of flags returned provide options for
   * \c clang_saveTranslationUnit() by default. The returned flag
   * set contains an unspecified set of options that save translation units with
   * the most commonly-requested data.
   */
  Types.u32 clang_defaultSaveOptions(1: CXTranslationUnit unit),

  /**
   * \brief Saves a translation unit into a serialized representation of
   * that translation unit on disk.
   *
   * Any translation unit that was parsed without error can be saved
   * into a file. The translation unit can then be deserialized into a
   * new \c CXTranslationUnit with \c clang_createTranslationUnit() or,
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
  CXSaveError clang_saveTranslationUnit(1: CXTranslationUnit unit,
                                       2: string filename,
                                       3: Types.u32 options),
  /**
   * \brief Destroy the specified CXTranslationUnit object.
   */
  void clang_disposeTranslationUnit(1: CXTranslationUnit unit),
   
  /**
   * \brief Returns the set of flags that is suitable for reparsing a translation
   * unit.
   *
   * The set of flags returned provide options for
   * \c clang_reparseTranslationUnit() by default. The returned flag
   * set contains an unspecified set of optimizations geared toward common uses
   * of reparsing. The set of optimizations enabled may change from one version 
   * to the next.
   */
  Types.u32 clang_defaultReparseOptions(1: CXTranslationUnit unit),

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
   * \c clang_createTranslationUnitFromSourceFile().
   *
   * \param unsaved_files The files that have not yet been saved to disk
   * but may be required for parsing, including the contents of
   * those files.  The contents and name of these files (as specified by
   * CXUnsavedFile) are copied when necessary, so the client only needs to
   * guarantee their validity until the call to this function returns.
   * 
   * \param options A bitset of options composed of the flags in CXReparse_Flags.
   * The function \c clang_defaultReparseOptions() produces a default set of
   * options recommended for most uses, based on the translation unit.
   *
   * \returns 0 if the sources could be reparsed. A non-zero value will be
   * returned if reparsing was impossible, such that the translation unit is
   * invalid. In such cases, the only valid call for \p TU is 
   * \c clang_disposeTranslationUnit(TU).
   */
  Types.int clang_reparseTranslationUnit(1: CXTranslationUnit unit,
                                         2: list<CXUnsavedFile> unsaved_files,
                                         3: Types.u32 options),

  /**
    * \brief Returns the human-readable string that represents the name 
    *  of the memory category.
    */
  string clang_getTUResourceUsageName(1: CXTUResourceUsageKind kind),

  /**
    * \brief Return the memory usage of a translation unit.  This object
    *  should be released with clang_disposeCXTUResourceUsage().
    */
  CXTUResourceUsage clang_getCXTUResourceUsage(1: CXTranslationUnit unit),

  void clang_disposeCXTUResourceUsage(1: CXTUResourceUsage usage),
}