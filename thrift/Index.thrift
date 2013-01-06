namespace * clang.thrift

/**
 * \defgroup CINDEX libclang: C Interface to Clang
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

include "Types.thrift"

/**
 * \brief An "index" that consists of a set of translation units that would
 * typically be linked together into an executable or library.
 */
typedef Types.ResourceId CXIndex

/**
 * \brief Client data that will be passed through to various callbacks
 * and visitors.
 */
typedef Types.ResourceId CXClientData

/**
 * \brief Describes the availability of a particular entity, which indicates
 * whether the use of this entity will result in a warning or error due to
 * it being deprecated or unavailable.
 */
enum CXAvailabilityKind {
  /**
   * \brief The entity is available.
   */
  CXAvailability_Available,
  /**
   * \brief The entity is available, but has been deprecated (and its use is
   * not recommended).
   */
  CXAvailability_Deprecated,
  /**
   * \brief The entity is not available; any use of it will be an error.
   */
  CXAvailability_NotAvailable,
  /**
   * \brief The entity is available, but not accessible; any use of it will be
   * an error.
   */
  CXAvailability_NotAccessible
}

/**
 * \brief Describes a version number of the form major.minor.subminor.
 */
struct CXVersion {
  /**
   * \brief The major version number, e.g., the '10' in '10.7.3'. A negative
   * value indicates that there is no version number at all.
   */
  1: Types.int Major,
  /**
   * \brief The minor version number, e.g., the '7' in '10.7.3'. This value
   * will be negative if no minor version number was provided, e.g., for 
   * version '10'.
   */
  2: Types.int Minor,
  /**
   * \brief The subminor version number, e.g., the '3' in '10.7.3'. This value
   * will be negative if no minor or subminor version number was provided,
   * e.g., in version '10' or '10.7'.
   */
  3: Types.int Subminor
}

enum CXGlobalOptFlags {
  /**
   * \brief Used to indicate that no special CXIndex options are needed.
   */
  CXGlobalOpt_None = 0x0,

  /**
   * \brief Used to indicate that threads that libclang creates for indexing
   * purposes should use background priority.
   *
   * Affects #clang_indexSourceFile, #clang_indexTranslationUnit,
   * #clang_parseTranslationUnit, #clang_saveTranslationUnit.
   */
  CXGlobalOpt_ThreadBackgroundPriorityForIndexing = 0x1,

  /**
   * \brief Used to indicate that threads that libclang creates for editing
   * purposes should use background priority.
   *
   * Affects #clang_reparseTranslationUnit, #clang_codeCompleteAt,
   * #clang_annotateTokens
   */
  CXGlobalOpt_ThreadBackgroundPriorityForEditing = 0x2,

  /**
   * \brief Used to indicate that all threads that libclang creates should use
   * background priority.
   */
  CXGlobalOpt_ThreadBackgroundPriorityForAll = 0x3
}

service Index {
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
   *   Idx = clang_createIndex(1, 1);
   *
   *   // IndexTest.pch was produced with the following command:
   *   // "clang -x c IndexTest.h -emit-ast -o IndexTest.pch"
   *   TU = clang_createTranslationUnit(Idx, "IndexTest.pch");
   *
   *   // This will load all the symbols from 'IndexTest.pch'
   *   clang_visitChildren(clang_getTranslationUnitCursor(TU),
   *                       TranslationUnitVisitor, 0);
   *   clang_disposeTranslationUnit(TU);
   *
   *   // This will load all the symbols from 'IndexTest.c', excluding symbols
   *   // from 'IndexTest.pch'.
   *   char *args[] = { "-Xclang", "-include-pch=IndexTest.pch" };
   *   TU = clang_createTranslationUnitFromSourceFile(Idx, "IndexTest.c", 2, args,
   *                                                  0, 0);
   *   clang_visitChildren(clang_getTranslationUnitCursor(TU),
   *                       TranslationUnitVisitor, 0);
   *   clang_disposeTranslationUnit(TU);
   * \endcode
   *
   * This process of creating the 'pch', loading it separately, and using it (via
   * -include-pch) allows 'excludeDeclsFromPCH' to remove redundant callbacks
   * (which gives the indexer the same performance benefit as the compiler).
   */
  CXIndex clang_createIndex(1: Types.int excludeDeclarationsFromPCH, 
                            2: Types.int displayDiagnostics),

  /**
   * \brief Destroy the given index.
   *
   * The index must not be destroyed until all of the translation units created
   * within that index have been destroyed.
   */
  void clang_disposeIndex(1: CXIndex index),

  /**
   * \brief Sets general options associated with a CXIndex.
   *
   * For example:
   * \code
   * CXIndex idx = ...;
   * clang_CXIndex_setGlobalOptions(idx,
   *     clang_CXIndex_getGlobalOptions(idx) |
   *     CXGlobalOpt_ThreadBackgroundPriorityForIndexing);
   * \endcode
   *
   * \param options A bitmask of options, a bitwise OR of CXGlobalOpt_XXX flags.
   */
  void clang_CXIndex_setGlobalOptions(1: CXIndex index, 2: CXGlobalOptFlags options),

  /**
   * \brief Gets the general options associated with a CXIndex.
   *
   * \returns A bitmask of options, a bitwise OR of CXGlobalOpt_XXX flags that
   * are associated with the given CXIndex object.
   */
  CXGlobalOptFlags clang_CXIndex_getGlobalOptions(1: CXIndex index)
}
