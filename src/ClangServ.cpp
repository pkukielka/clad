#include "generated/Clang.h"
#include <clang-c/Index.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class ClangHandler : virtual public ::clad::ClangIf {
 public:
  ClangHandler() {
  }

  ::clad::CXIndex createIndex(const int32_t excludeDeclarationsFromPCH, const int32_t displayDiagnostics) {
    return saveResource(clang_createIndex(excludeDeclarationsFromPCH, displayDiagnostics));
  }

  void disposeIndex(const ::clad::CXIndex index) {
    clang_disposeIndex(getResource(index));
  }

  void CXIndex_setGlobalOptions(const ::clad::CXIndex index, const ::clad::CXGlobalOptFlags::type options) {
    clang_CXIndex_setGlobalOptions(getResource(index), options);
  }

  ::clad::CXGlobalOptFlags::type CXIndex_getGlobalOptions(const ::clad::CXIndex index) {
    return static_cast<::clad::CXGlobalOptFlags::type>(
      clang_CXIndex_getGlobalOptions(getResource(index))
    );
  }

  void getTranslationUnitSpelling(std::string& _return, const ::clad::CXTranslationUnit unit) {
    _return = convert(clang_getTranslationUnitSpelling(getResource<CXTranslationUnit>(unit)));
  }

  ::clad::CXTranslationUnit createTranslationUnitFromSourceFile(const ::clad::CXIndex idx, const std::string& source_filename, 
    const std::vector<std::string>& command_line_args, const std::vector<::clad::CXUnsavedFile>& unsaved_files) 
  {
    return saveResource(
      clang_createTranslationUnitFromSourceFile(
        getResource(index), source_filename.c_str(), 
        command_line_args.size(), NULL /* TODO */, 
        unsaved_files.size(),     NULL /* TODO */
      )
    );
  }

  ::clad::CXTranslationUnit createTranslationUnit(const ::clad::CXIndex idx, const std::string& ast_filename) {
    return saveResource(clang_createTranslationUnit(getResource(idx), ast_filename.c_str()));
  }

  ::clad::u32 defaultEditingTranslationUnitOptions() {
    return clang_defaultEditingTranslationUnitOptions();
  }

  ::clad::CXTranslationUnit parseTranslationUnit(const ::clad::CXIndex idx, const std::string& source_filename, 
    const std::vector<std::string> & command_line_args, const std::vector<::clad::CXUnsavedFile> & unsaved_files, const ::clad::u32 options) 
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

  ::clad::u32 defaultSaveOptions(const ::clad::CXTranslationUnit unit) {
    return clang_defaultSaveOptions(getResource<CXTranslationUnit>(unit));
  }

  ::clad::CXSaveError::type saveTranslationUnit(const ::clad::CXTranslationUnit unit, const std::string& filename, const ::clad::u32 options) {
    return static_cast<::clad::CXSaveError::type>(
      clang_saveTranslationUnit(getResource<CXTranslationUnit>(unit), filename.c_str(), options)
    );
  }

  void disposeTranslationUnit(const ::clad::CXTranslationUnit unit) {
    clang_disposeTranslationUnit(getResource<CXTranslationUnit>(unit));
  }

  ::clad::u32 defaultReparseOptions(const ::clad::CXTranslationUnit unit) {
    return clang_defaultReparseOptions(getResource<CXTranslationUnit>(unit));
  }

  int32_t reparseTranslationUnit(const ::clad::CXTranslationUnit unit, const std::vector<::clad::CXUnsavedFile> & unsaved_files, const ::clad::u32 options) {
    return clang_reparseTranslationUnit(
      getResource<CXTranslationUnit>(unit), 
      unsaved_files.size(), NULL /* TODO */, 
      options
    );
  }

  void getTUResourceUsageName(std::string& _return, const ::clad::CXTUResourceUsageKind::type kind) {
     _return = clang_getTUResourceUsageName(static_cast<CXTUResourceUsageKind>(kind));
  }

  void getCXTUResourceUsage(::clad::CXTUResourceUsage& _return, const ::clad::CXTranslationUnit unit) {
    CXTUResourceUsage resource_usage = clang_getCXTUResourceUsage(getResource<CXTranslationUnit>(unit));

    std::transform(
      resource_usage.entries, resource_usage.entries + resource_usage.numEntries, _return.entries.begin(), 
      [](CXTUResourceUsageEntry& entry) {
        ::clad::CXTUResourceUsageEntry newEntry;
        newEntry.__set_amount(entry.amount);
        newEntry.__set_kind(static_cast<::clad::CXTUResourceUsageKind::type>(entry.kind));
        return newEntry;
      }
    );

    clang_disposeCXTUResourceUsage(resource_usage);
  }

  void disposeCXTUResourceUsage(const ::clad::CXTUResourceUsage& usage) {
    /* TODO: Not needed, remove from API together with CXTUResourceUsage::data member */
  }

  void getFileName(std::string& _return, const ::clad::CXFile file) {
    _return= convert(clang_getFileName(getResource<CXFile>(file)));
  }

  ::clad::t64 getFileTime(const ::clad::CXFile file) {
    return clang_getFileTime(getResource<CXFile>(file));
  }

  ::clad::u32 isFileMultipleIncludeGuarded(const ::clad::CXTranslationUnit unit, const ::clad::CXFile file) {
    return clang_isFileMultipleIncludeGuarded(getResource<CXTranslationUnit>(unit), getResource<CXFile>(file));
  }

  ::clad::CXFile getFile(const ::clad::CXTranslationUnit unit, const std::string& filename) {
    return saveResource(
      clang_getFile(getResource<CXTranslationUnit>(unit), filename.c_str())
    );
  }

  void getNullLocation(::clad::CXSourceLocation& _return) {
    _return = convert(clang_getNullLocation());
  }

  ::clad::u32 equalLocations(const ::clad::CXSourceLocation& loc1, const ::clad::CXSourceLocation& loc2) {
    return clang_equalLocations(convert(loc1), convert(loc2));
  }

  void getLocation(::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu, const ::clad::CXFile file, const ::clad::u32 line, const ::clad::u32 column) {
    /* TODO: make names of CXTranslationUnit parameters consistent*/
    _return = convert(clang_getLocation(getResource<CXTranslationUnit>(tu), getResource(file), line, column));
  }

  void getLocationForOffset(::clad::CXSourceLocation& _return, const ::clad::CXTranslationUnit tu, const ::clad::CXFile file, const ::clad::u32 offset) {
     _return = convert(clang_getLocationForOffset(getResource<CXTranslationUnit>(tu), getResource(file), offset));
  }

  void getNullRange(::clad::CXSourceRange& _return) {
  }

  void getRange(::clad::CXSourceRange& _return, const ::clad::CXSourceLocation& sourceBegin, const ::clad::CXSourceLocation& sourceEnd) {
    // Your implementation goes here
    printf("getRange\n");
  }

  ::clad::u32 equalRanges(const ::clad::CXSourceRange& range1, const ::clad::CXSourceRange& range2) {
    // Your implementation goes here
    printf("equalRanges\n");
  }

  int32_t Range_isNull(const ::clad::CXSourceRange& range) {
    // Your implementation goes here
    printf("Range_isNull\n");
  }

  void getExpansionLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
    // Your implementation goes here
    printf("getExpansionLocation\n");
  }

  void getPresumedLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
    // Your implementation goes here
    printf("getPresumedLocation\n");
  }

  void getInstantiationLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
    // Your implementation goes here
    printf("getInstantiationLocation\n");
  }

  void getSpellingLocation(::clad::CXSourcePosition& _return, const ::clad::CXSourceLocation& location) {
    // Your implementation goes here
    printf("getSpellingLocation\n");
  }

  void getRangeStart(::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range) {
    // Your implementation goes here
    printf("getRangeStart\n");
  }

  void getRangeEnd(::clad::CXSourceLocation& _return, const ::clad::CXSourceRange& range) {
    // Your implementation goes here
    printf("getRangeEnd\n");
  }

  ::clad::u32 getNumDiagnosticsInSet(const ::clad::CXDiagnosticSet diags) {
    // Your implementation goes here
    printf("getNumDiagnosticsInSet\n");
  }

  ::clad::CXDiagnostic getDiagnosticInSet(const ::clad::CXDiagnosticSet diags, const ::clad::u32 index) {
    // Your implementation goes here
    printf("getDiagnosticInSet\n");
  }

  ::clad::CXDiagnosticSet loadDiagnostics(const std::string& filename) {
    // Your implementation goes here
    printf("loadDiagnostics\n");
  }

  void disposeDiagnosticSet(const ::clad::CXDiagnosticSet diagnosticSet) {
    // Your implementation goes here
    printf("disposeDiagnosticSet\n");
  }

  ::clad::CXDiagnosticSet getChildDiagnostics(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getChildDiagnostics\n");
  }

  ::clad::u32 getNumDiagnostics(const ::clad::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("getNumDiagnostics\n");
  }

  ::clad::CXDiagnostic getDiagnostic(const ::clad::CXTranslationUnit unit, const ::clad::u32 index) {
    // Your implementation goes here
    printf("getDiagnostic\n");
  }

  ::clad::CXDiagnosticSet getDiagnosticSetFromTU(const ::clad::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("getDiagnosticSetFromTU\n");
  }

  void disposeDiagnostic(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("disposeDiagnostic\n");
  }

  void formatDiagnostic(std::string& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 options) {
    // Your implementation goes here
    printf("formatDiagnostic\n");
  }

  ::clad::u32 defaultDiagnosticDisplayOptions() {
    // Your implementation goes here
    printf("defaultDiagnosticDisplayOptions\n");
  }

  ::clad::CXDiagnosticSeverity::type getDiagnosticSeverity(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticSeverity\n");
  }

  void getDiagnosticLocation(::clad::CXSourceLocation& _return, const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticLocation\n");
  }

  void getDiagnosticSpelling(std::string& _return, const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticSpelling\n");
  }

  void getDiagnosticOption(::clad::CXDiagnosticOption& _return, const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticOption\n");
  }

  ::clad::u32 getDiagnosticCategory(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticCategory\n");
  }

  void getDiagnosticCategoryName(std::string& _return, const ::clad::u32 category) {
    // Your implementation goes here
    printf("getDiagnosticCategoryName\n");
  }

  void getDiagnosticCategoryText(std::string& _return, const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticCategoryText\n");
  }

  ::clad::u32 getDiagnosticNumRanges(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticNumRanges\n");
  }

  void getDiagnosticRange(::clad::CXSourceRange& _return, const ::clad::CXDiagnostic diagnostic, const ::clad::u32 range) {
    // Your implementation goes here
    printf("getDiagnosticRange\n");
  }

  ::clad::u32 getDiagnosticNumFixIts(const ::clad::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("getDiagnosticNumFixIts\n");
  }

  void getDiagnosticFixIt(::clad::CXDiagnosticFixIt& _return, const ::clad::CXDiagnostic Diagnostic, const ::clad::u32 FixIt) {
    // Your implementation goes here
    printf("getDiagnosticFixIt\n");
  }

private:
  template <typename Out = void*, typename In = ::clad::ResourceId>
  Out getResource(In resourceId) {
    return reinterpret_cast<Out>(resourceId);
  }

  template <typename Out = ::clad::ResourceId, typename In = void*>
  Out saveResource(In pAddress) {
    return reinterpret_cast<Out>(pAddress);
  }

  std::string convert(const CXString& src) {
    std::string result = clang_getCString(src);
    clang_disposeString(src);
    return result;
  }

  ::clad::CXSourceLocation convert(const CXSourceLocation& location) {
    ::clad::CXSourceLocation result;
    result.__set_int_data(location.int_data);
    result.__set_ptr_data(std::vector<::clad::ResourceId>{
      saveResource(location.ptr_data[0]), saveResource(location.ptr_data[1])
    });
    return result;
  }

  CXSourceLocation convert(const ::clad::CXSourceLocation& location) {
    CXSourceLocation result;
    result.int_data = location.int_data;
    result.ptr_data[0] = getResource(location.ptr_data[0]);
    result.ptr_data[1] = getResource(location.ptr_data[1]);
    return result;
  }
};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ClangHandler> handler(new ClangHandler());
  shared_ptr<TProcessor> processor(new ::clad::ClangProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
