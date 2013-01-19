#include "ClangHandler.h"

ClangHandler::ClangHandler() {
}

template <typename Out, typename In>
Out ClangHandler::getResource(In resourceId) {
  return reinterpret_cast<Out>(resourceId);
}

template <typename Out, typename In>
Out ClangHandler::saveResource(In pAddress) {
  return reinterpret_cast<Out>(pAddress);
}

std::string ClangHandler::convert(const CXString& src) {
  std::string result = clang_getCString(src);
  clang_disposeString(src);
  return result;
}

::clad::CXSourceLocation ClangHandler::convert(const CXSourceLocation& location) {
  ::clad::CXSourceLocation result;
  result.__set_int_data(location.int_data);
  result.__set_ptr_data(std::vector< ::clad::ResourceId>{
    saveResource(location.ptr_data[0]), saveResource(location.ptr_data[1])
  });
  return result;
}

CXSourceLocation ClangHandler::convert(const ::clad::CXSourceLocation& location) {
  CXSourceLocation result;

  result.int_data = location.int_data;
  result.ptr_data[0] = getResource(location.ptr_data[0]);
  result.ptr_data[1] = getResource(location.ptr_data[1]);

  return result;
}

::clad::CXSourceRange ClangHandler::convert(const CXSourceRange& range) {
  ::clad::CXSourceRange result;

  result.__set_begin_int_data(range.begin_int_data);
  result.__set_end_int_data(range.end_int_data);
  result.__set_ptr_data(std::vector< ::clad::ResourceId>{
    saveResource(range.ptr_data[0]), saveResource(range.ptr_data[1])
  });

  return result;
}

CXSourceRange ClangHandler::convert(const ::clad::CXSourceRange& range) {
  CXSourceRange result;

  result.begin_int_data = range.begin_int_data;
  result.end_int_data = range.end_int_data;
  result.ptr_data[0] = getResource(range.ptr_data[0]);
  result.ptr_data[1] = getResource(range.ptr_data[1]);

  return result;
}

/*
 * ==========================================================================
 * Index
 * ==========================================================================
 */
::clad::CXIndex ClangHandler::createIndex(const int32_t excludeDeclarationsFromPCH, const int32_t displayDiagnostics) {
  return saveResource(clang_createIndex(excludeDeclarationsFromPCH, displayDiagnostics));
}

void ClangHandler::disposeIndex(const ::clad::CXIndex index) {
  clang_disposeIndex(getResource(index));
}

void ClangHandler::CXIndex_setGlobalOptions(const ::clad::CXIndex index, const ::clad::CXGlobalOptFlags::type options) {
  clang_CXIndex_setGlobalOptions(getResource(index), options);
}

::clad::CXGlobalOptFlags::type ClangHandler::CXIndex_getGlobalOptions(const ::clad::CXIndex index) {
  return static_cast< ::clad::CXGlobalOptFlags::type>(
    clang_CXIndex_getGlobalOptions(getResource(index))
  );
}

/*
 * ==========================================================================
 * Translation Unit
 * ==========================================================================
 */
void ClangHandler::getTranslationUnitSpelling(std::string& _return, const ::clad::CXTranslationUnit unit) {
  _return = convert(clang_getTranslationUnitSpelling(getResource<CXTranslationUnit>(unit)));
}

::clad::CXTranslationUnit ClangHandler::createTranslationUnitFromSourceFile(const ::clad::CXIndex idx, const std::string& source_filename,
  const std::vector<std::string>& command_line_args, const std::vector< ::clad::CXUnsavedFile>& unsaved_files)
{
  return saveResource(
    clang_createTranslationUnitFromSourceFile(
      getResource(idx), source_filename.c_str(),
      command_line_args.size(), NULL /* TODO */,
      unsaved_files.size(),     NULL /* TODO */
    )
  );
}

::clad::CXTranslationUnit ClangHandler::createTranslationUnit(const ::clad::CXIndex idx, const std::string& ast_filename) {
  return saveResource(clang_createTranslationUnit(getResource(idx), ast_filename.c_str()));
}

::clad::u32 ClangHandler::defaultEditingTranslationUnitOptions() {
  return clang_defaultEditingTranslationUnitOptions();
}

::clad::CXTranslationUnit ClangHandler::parseTranslationUnit(const ::clad::CXIndex idx, const std::string& source_filename,
  const std::vector<std::string> & command_line_args, const std::vector< ::clad::CXUnsavedFile> & unsaved_files, const ::clad::u32 options)
{
  return saveResource(
    clang_parseTranslationUnit(
      getResource(idx), source_filename.c_str(),
      NULL /* TODO */, command_line_args.size(),
      NULL /* TODO */, unsaved_files.size(),
      options
    )
  );
}

::clad::u32 ClangHandler::defaultSaveOptions(const ::clad::CXTranslationUnit unit) {
  return clang_defaultSaveOptions(getResource<CXTranslationUnit>(unit));
}

::clad::CXSaveError::type ClangHandler::saveTranslationUnit(const ::clad::CXTranslationUnit unit, const std::string& filename, const ::clad::u32 options) {
  return static_cast< ::clad::CXSaveError::type>(
    clang_saveTranslationUnit(getResource<CXTranslationUnit>(unit), filename.c_str(), options)
  );
}

void ClangHandler::disposeTranslationUnit(const ::clad::CXTranslationUnit unit) {
  clang_disposeTranslationUnit(getResource<CXTranslationUnit>(unit));
}

::clad::u32 ClangHandler::defaultReparseOptions(const ::clad::CXTranslationUnit unit) {
  return clang_defaultReparseOptions(getResource<CXTranslationUnit>(unit));
}

int32_t ClangHandler::reparseTranslationUnit(const ::clad::CXTranslationUnit unit, const std::vector< ::clad::CXUnsavedFile> & unsaved_files, const ::clad::u32 options) {
  return clang_reparseTranslationUnit(
    getResource<CXTranslationUnit>(unit),
    unsaved_files.size(), NULL /* TODO */,
    options
  );
}

void ClangHandler::getTUResourceUsageName(std::string& _return, const ::clad::CXTUResourceUsageKind::type kind) {
   _return = clang_getTUResourceUsageName(static_cast<CXTUResourceUsageKind>(kind));
}

void ClangHandler::getCXTUResourceUsage(::clad::CXTUResourceUsage& _return, const ::clad::CXTranslationUnit unit) {
  CXTUResourceUsage resource_usage = clang_getCXTUResourceUsage(getResource<CXTranslationUnit>(unit));

  std::transform(
    resource_usage.entries, resource_usage.entries + resource_usage.numEntries, _return.entries.begin(),
    [](CXTUResourceUsageEntry& entry) {
      ::clad::CXTUResourceUsageEntry newEntry;
      newEntry.__set_amount(entry.amount);
      newEntry.__set_kind(static_cast< ::clad::CXTUResourceUsageKind::type>(entry.kind));
      return newEntry;
    }
  );

  clang_disposeCXTUResourceUsage(resource_usage);
}

void ClangHandler::disposeCXTUResourceUsage(const ::clad::CXTUResourceUsage& usage) {
  /* TODO: Not needed, remove from API together with CXTUResourceUsage::data member */
}

/*
 * ==========================================================================
 * Files
 * ==========================================================================
 */
void ClangHandler::getFileName(std::string& _return, const ::clad::CXFile file) {
  _return= convert(clang_getFileName(getResource<CXFile>(file)));
}

::clad::t64 ClangHandler::getFileTime(const ::clad::CXFile file) {
  return clang_getFileTime(getResource<CXFile>(file));
}

::clad::u32 ClangHandler::isFileMultipleIncludeGuarded(const ::clad::CXTranslationUnit unit, const ::clad::CXFile file) {
  return clang_isFileMultipleIncludeGuarded(getResource<CXTranslationUnit>(unit), getResource<CXFile>(file));
}

::clad::CXFile ClangHandler::getFile(const ::clad::CXTranslationUnit unit, const std::string& filename) {
  return saveResource(
    clang_getFile(getResource<CXTranslationUnit>(unit), filename.c_str())
  );
}

/*
 * ==========================================================================
 * Physical source locations
 * ==========================================================================
 */
void ClangHandler::getNullLocation(::clad::CXSourceLocation& _return) {
  _return = convert(clang_getNullLocation());
}

::clad::u32 ClangHandler::equalLocations(const ::clad::CXSourceLocation& loc1, const ::clad::CXSourceLocation& loc2) {
  return clang_equalLocations(convert(loc1), convert(loc2));
}

void ClangHandler::getLocation(::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu,
  const ::clad::CXFile file, const ::clad::u32 line, const ::clad::u32 column)
{
  /* TODO: make names of CXTranslationUnit parameters consistent */
  _return = convert(clang_getLocation(getResource<CXTranslationUnit>(tu), getResource(file), line, column));
}

void ClangHandler::getLocationForOffset(::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu,
  const ::clad::CXFile file, const ::clad::u32 offset)
{
   _return = convert(clang_getLocationForOffset(getResource<CXTranslationUnit>(tu), getResource(file), offset));
}

void ClangHandler::getNullRange(::clad::CXSourceRange& _return) {
  _return = convert(clang_getNullRange());
}

void ClangHandler::getRange(::clad::CXSourceRange& _return, const ::clad::CXSourceLocation& sourceBegin, const ::clad::CXSourceLocation& sourceEnd) {
  _return = convert(clang_getRange(convert(sourceBegin), convert(sourceEnd)));
}

::clad::u32 ClangHandler::equalRanges(const ::clad::CXSourceRange& range1, const ::clad::CXSourceRange& range2) {
  return clang_equalRanges(convert(range1), convert(range2));
}

int32_t ClangHandler::Range_isNull(const ::clad::CXSourceRange& range) {
  /* TODO: change name to lower case, most likely it's typo in the CLang API */
  return clang_Range_isNull(convert(range));
}

void ClangHandler::getExpansionLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
  CXFile file;
  unsigned int line, column, offset;

  clang_getExpansionLocation(convert(location), &file, &line, &column, &offset);

  _return.__set_file(saveResource(file));
  _return.__set_line(line);
  _return.__set_column(column);
  _return.__set_offset(offset);
}

void ClangHandler::getPresumedLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
  CXString filename;
  unsigned line, column;

  clang_getPresumedLocation(convert(location), &filename, &line, &column);

  _return.__set_filename(convert(filename));
  _return.__set_line(line);
  _return.__set_column(column);
}

void ClangHandler::getInstantiationLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
  CXFile file;
  unsigned int line, column, offset;

  clang_getInstantiationLocation(convert(location), &file, &line, &column, &offset);

  _return.__set_file(saveResource(file));
  _return.__set_line(line);
  _return.__set_column(column);
  _return.__set_offset(offset);
}

void ClangHandler::getSpellingLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
  CXFile file;
  unsigned int line, column, offset;

  clang_getSpellingLocation(convert(location), &file, &line, &column, &offset);

  _return.__set_file(saveResource(file));
  _return.__set_line(line);
  _return.__set_column(column);
  _return.__set_offset(offset);
}

void ClangHandler::getRangeStart(::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range) {
  _return = convert(clang_getRangeStart(convert(range)));
}

void ClangHandler::getRangeEnd(::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range) {
  _return = convert(clang_getRangeEnd(convert(range)));
}

/**
 * ==========================================================================
 *                         Diagnostic reporting
 * ==========================================================================
 */
::clad::u32 ClangHandler::getNumDiagnosticsInSet(const ::clad::CXDiagnosticSet diags) {
  return clang_getNumDiagnosticsInSet(getResource(diags));
}

::clad::CXDiagnostic ClangHandler::getDiagnosticInSet(const ::clad::CXDiagnosticSet diags, const ::clad::u32 index) {
  return saveResource(clang_getDiagnosticInSet(getResource(diags), index));
}

::clad::CXDiagnosticSet ClangHandler::loadDiagnostics(const std::string& filename) {
  enum CXLoadDiag_Error error;
  CXString errorString;

  CXDiagnosticSet diagnostic_set = clang_loadDiagnostics(filename.c_str(), &error, &errorString);

  if (error != CXLoadDiag_None) {
    ::clad::CXLoadDiagException ex;
    ex.__set_Error(static_cast< ::clad::CXLoadDiag_Error::type>(error));
    ex.__set_ErrorString(convert(errorString));
    throw ex;
  }

  return saveResource(diagnostic_set);
}

void ClangHandler::disposeDiagnosticSet(const ::clad::CXDiagnosticSet diagnosticSet) {
  clang_disposeDiagnostic(getResource(diagnosticSet));
}

::clad::CXDiagnosticSet ClangHandler::getChildDiagnostics(const ::clad::CXDiagnostic diagnostic) {
  return saveResource(clang_getChildDiagnostics(getResource(diagnostic)));
}

::clad::u32 ClangHandler::getNumDiagnostics(const ::clad::CXTranslationUnit unit) {
  return clang_getNumDiagnostics(getResource<CXTranslationUnit>(unit));
}

::clad::CXDiagnostic ClangHandler::getDiagnostic(const ::clad::CXTranslationUnit unit, const ::clad::u32 index) {
  return saveResource(clang_getDiagnostic(getResource<CXTranslationUnit>(unit), index));
}

::clad::CXDiagnosticSet ClangHandler::getDiagnosticSetFromTU(const ::clad::CXTranslationUnit unit) {
  return saveResource(clang_getDiagnosticSetFromTU(getResource<CXTranslationUnit>(unit)));
}

void ClangHandler::disposeDiagnostic(const ::clad::CXDiagnostic diagnostic) {
  clang_disposeDiagnostic(getResource(diagnostic));
}

void ClangHandler::formatDiagnostic(std::string& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 options) {
  _return = convert(clang_formatDiagnostic(getResource(diagnostic), options));
}

::clad::u32 ClangHandler::defaultDiagnosticDisplayOptions() {
  return clang_defaultDiagnosticDisplayOptions();
}

::clad::CXDiagnosticSeverity::type ClangHandler::getDiagnosticSeverity(const ::clad::CXDiagnostic diagnostic) {
  return static_cast< ::clad::CXDiagnosticSeverity::type>(clang_getDiagnosticSeverity(getResource(diagnostic)));
}

void ClangHandler::getDiagnosticLocation(::clad::CXSourceLocation& _return, const ::clad::CXDiagnostic diagnostic) {
  _return = convert(clang_getDiagnosticLocation(getResource(diagnostic)));
}

void ClangHandler::getDiagnosticSpelling(std::string& _return, const ::clad::CXDiagnostic diagnostic) {
  _return = convert(clang_getDiagnosticSpelling(getResource(diagnostic)));
}

void ClangHandler::getDiagnosticOption(::clad::CXDiagnosticOption& _return, const ::clad::CXDiagnostic diagnostic) {
  CXString enable, disable;
  enable = clang_getDiagnosticOption(getResource(diagnostic), &disable);

  _return.__set_Enable(convert(enable));
  _return.__set_Disable(convert(disable));
}

::clad::u32 ClangHandler::getDiagnosticCategory(const ::clad::CXDiagnostic diagnostic) {
  return clang_getDiagnosticCategory(getResource(diagnostic));
}

void ClangHandler::getDiagnosticCategoryName(std::string& _return, const ::clad::u32 category) {
  /* TODO: Remove this, clang_getDiagnosticCategoryName is deprecated */
}

void ClangHandler::getDiagnosticCategoryText(std::string& _return, const ::clad::CXDiagnostic diagnostic) {
  _return = convert(clang_getDiagnosticCategoryText(getResource(diagnostic)));
}

::clad::u32 ClangHandler::getDiagnosticNumRanges(const ::clad::CXDiagnostic diagnostic) {
  return clang_getDiagnosticNumRanges(getResource(diagnostic));
}

void ClangHandler::getDiagnosticRange(::clad::CXSourceRange& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 range) {
  _return = convert(clang_getDiagnosticRange(getResource(diagnostic), range));
}

::clad::u32 ClangHandler::getDiagnosticNumFixIts(const ::clad::CXDiagnostic diagnostic) {
  return clang_getDiagnosticNumFixIts(getResource(diagnostic));
}

void ClangHandler::getDiagnosticFixIt(::clad::CXDiagnosticFixIt& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 fix_it) {
  /* TODO: Fix parameters names cases inside thrift file */
  CXSourceRange replacement_range;
  CXString replacement_text = clang_getDiagnosticFixIt(getResource(diagnostic), fix_it, &replacement_range);
  _return.__set_ReplacementText(convert(replacement_text));
  _return.__set_ReplacementRange(convert(replacement_range));
}
