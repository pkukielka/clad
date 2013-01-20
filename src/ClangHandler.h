#ifndef CLAD_SRC_CLANG_HANDLER
#define CLAD_SRC_CLANG_HANDLER

#include <clang-c/Index.h>
#include "generated/Clang.h"

class ClangHandler : virtual public ::clad::ClangIf {
public:
  ClangHandler();

  /*
   * ==========================================================================
   * Index
   * ==========================================================================
   */
  ::clad::CXIndex                 createIndex                         (const int32_t excludeDeclarationsFromPCH, const int32_t displayDiagnostics);
  void                            disposeIndex                        (const ::clad::CXIndex index);
  void                            CXIndex_setGlobalOptions            (const ::clad::CXIndex index, const ::clad::CXGlobalOptFlags::type options);
  ::clad::CXGlobalOptFlags::type  CXIndex_getGlobalOptions            (const ::clad::CXIndex index);

  /*
   * ==========================================================================
   * Translation Unit
   * ==========================================================================
   */
  void                            getTranslationUnitSpelling          (std::string& _return, const ::clad::CXTranslationUnit unit);
  ::clad::CXTranslationUnit       createTranslationUnitFromSourceFile (const ::clad::CXIndex idx, const std::string& source_filename,
                                                                       const std::vector<std::string>& command_line_args,
                                                                       const std::vector< ::clad::CXUnsavedFile>& unsaved_files);
  ::clad::CXTranslationUnit       createTranslationUnit               (const ::clad::CXIndex idx, const std::string& ast_filename);
  ::clad::u32                     defaultEditingTranslationUnitOptions();
  ::clad::CXTranslationUnit       parseTranslationUnit                (const ::clad::CXIndex idx, const std::string& source_filename,
                                                                       const std::vector<std::string>& command_line_args,
                                                                       const std::vector< ::clad::CXUnsavedFile>& unsaved_files, const ::clad::u32 options);
  ::clad::u32                     defaultSaveOptions                  (const ::clad::CXTranslationUnit unit);
  ::clad::CXSaveError::type       saveTranslationUnit                 (const ::clad::CXTranslationUnit unit, const std::string& filename,
                                                                       const ::clad::u32 options);
  void                            disposeTranslationUnit              (const ::clad::CXTranslationUnit unit);
  ::clad::u32                     defaultReparseOptions               (const ::clad::CXTranslationUnit unit);
  int32_t                         reparseTranslationUnit              (const ::clad::CXTranslationUnit unit,
                                                                       const std::vector< ::clad::CXUnsavedFile>& unsaved_files, const ::clad::u32 options);
  void                            getTUResourceUsageName              (std::string& _return, const ::clad::CXTUResourceUsageKind::type kind);
  void                            getCXTUResourceUsage                (::clad::CXTUResourceUsage& _return, const ::clad::CXTranslationUnit unit);
  void                            disposeCXTUResourceUsage            (const ::clad::CXTUResourceUsage& usage);

  /*
   * ==========================================================================
   * Files
   * ==========================================================================
   */
  void                            getFileName                         (std::string& _return, const ::clad::CXFile file);
  ::clad::t64                     getFileTime                         (const ::clad::CXFile file);
  ::clad::u32                     isFileMultipleIncludeGuarded        (const ::clad::CXTranslationUnit unit, const ::clad::CXFile file);
  ::clad::CXFile                  getFile                             (const ::clad::CXTranslationUnit unit, const std::string& filename);

  /*
   * ==========================================================================
   * Physical source locations
   * ==========================================================================
   */
  void                            getNullLocation                     (::clad::CXSourceLocation& _return);
  ::clad::u32                     equalLocations                      (const ::clad::CXSourceLocation& loc1, const ::clad::CXSourceLocation& loc2);
  void                            getLocation                         (::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu,
                                                                       const ::clad::CXFile file, const ::clad::u32 line, const ::clad::u32 column);
  void                            getLocationForOffset                (::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu,
                                                                       const ::clad::CXFile file, const ::clad::u32 offset);
  void                            getNullRange                        (::clad::CXSourceRange& _return);
  void                            getRange                            (::clad::CXSourceRange& _return, const ::clad::CXSourceLocation& sourceBegin,
                                                                       const ::clad::CXSourceLocation& sourceEnd);
  ::clad::u32                     equalRanges                         (const ::clad::CXSourceRange& range1, const ::clad::CXSourceRange& range2);
  int32_t                         isRangeNull                         (const ::clad::CXSourceRange& range);
  void                            getExpansionLocation                (::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location);
  void                            getPresumedLocation                 (::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location);
  void                            getInstantiationLocation            (::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location);
  void                            getSpellingLocation                 (::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location);
  void                            getRangeStart                       (::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range);
  void                            getRangeEnd                         (::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range);

  /**
   * ==========================================================================
   *                         Diagnostic reporting
   * ==========================================================================
   */
  ::clad::u32                     getNumDiagnosticsInSet              (const ::clad::CXDiagnosticSet diags);
  ::clad::CXDiagnostic            getDiagnosticInSet                  (const ::clad::CXDiagnosticSet diags, const ::clad::u32 index);
  ::clad::CXDiagnosticSet         loadDiagnostics                     (const std::string& filename);
  void                            disposeDiagnosticSet                (const ::clad::CXDiagnosticSet diagnosticSet);
  ::clad::CXDiagnosticSet         getChildDiagnostics                 (const ::clad::CXDiagnostic diagnostic);
  ::clad::u32                     getNumDiagnostics                   (const ::clad::CXTranslationUnit unit);
  ::clad::CXDiagnostic            getDiagnostic                       (const ::clad::CXTranslationUnit unit, const ::clad::u32 index);
  ::clad::CXDiagnosticSet         getDiagnosticSetFromTU              (const ::clad::CXTranslationUnit unit);
  void                            disposeDiagnostic                   (const ::clad::CXDiagnostic diagnostic);
  void                            formatDiagnostic                    (std::string& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 options);
  ::clad::u32                     defaultDiagnosticDisplayOptions     ();
  ::clad::CXDiagnosticSeverity::type getDiagnosticSeverity            (const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticLocation               (::clad::CXSourceLocation& _return, const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticSpelling               (std::string& _return, const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticOption                 (::clad::CXDiagnosticOption& _return, const ::clad::CXDiagnostic diagnostic);
  ::clad::u32                     getDiagnosticCategory               (const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticCategoryName           (std::string& _return, const ::clad::u32 category);
  void                            getDiagnosticCategoryText           (std::string& _return, const ::clad::CXDiagnostic diagnostic);
  ::clad::u32                     getDiagnosticNumRanges              (const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticRange                  (::clad::CXSourceRange& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 range);
  ::clad::u32                     getDiagnosticNumFixIts              (const ::clad::CXDiagnostic diagnostic);
  void                            getDiagnosticFixIt                  (::clad::CXDiagnosticFixIt& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 fix_it);

private:
  template <typename Out = void*, typename In = ::clad::ResourceId>
  Out                             getResource               (In resourceId);

  template <typename Out = ::clad::ResourceId, typename In = void*>
  Out                             saveResource              (In pAddress);

  std::string                     convert                     (const CXString& src);
  ::clad::CXSourceLocation        convert                     (const CXSourceLocation& location);
  CXSourceLocation                convert                     (const ::clad::CXSourceLocation& location);
  ::clad::CXSourceRange           convert                     (const CXSourceRange& range);
  CXSourceRange                   convert                     (const ::clad::CXSourceRange& range);
};

#endif // CLAD_SRC_CLANG_HANDLER
