namespace * clad

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
  1: i32 Major,
  /**
   * \brief The minor version number, e.g., the '7' in '10.7.3'. This value
   * will be negative if no minor version number was provided, e.g., for 
   * version '10'.
   */
  2: i32 Minor,
  /**
   * \brief The subminor version number, e.g., the '3' in '10.7.3'. This value
   * will be negative if no minor or subminor version number was provided,
   * e.g., in version '10' or '10.7'.
   */
  3: i32 Subminor
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

