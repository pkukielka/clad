#include "generated/Clang.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::clang::thrift;

class ClangHandler : virtual public ClangIf {
 public:
  ClangHandler() {
    // Your initialization goes here
  }

   ::clang::thrift::CXIndex clang_createIndex(const int32_t excludeDeclarationsFromPCH, const int32_t displayDiagnostics) {
    // Your implementation goes here
    printf("clang_createIndex\n");
  }

  void clang_disposeIndex(const  ::clang::thrift::CXIndex index) {
    // Your implementation goes here
    printf("clang_disposeIndex\n");
  }

  void clang_CXIndex_setGlobalOptions(const  ::clang::thrift::CXIndex index, const  ::clang::thrift::CXGlobalOptFlags::type options) {
    // Your implementation goes here
    printf("clang_CXIndex_setGlobalOptions\n");
  }

   ::clang::thrift::CXGlobalOptFlags::type clang_CXIndex_getGlobalOptions(const  ::clang::thrift::CXIndex index) {
    // Your implementation goes here
    printf("clang_CXIndex_getGlobalOptions\n");
  }

  void clang_getTranslationUnitSpelling(std::string& _return, const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_getTranslationUnitSpelling\n");
  }

   ::clang::thrift::CXTranslationUnit clang_createTranslationUnitFromSourceFile(const  ::clang::thrift::CXIndex idx, const std::string& source_filename, const std::vector<std::string> & clang_command_line_args, const std::vector< ::clang::thrift::CXUnsavedFile> & unsaved_files) {
    // Your implementation goes here
    printf("clang_createTranslationUnitFromSourceFile\n");
  }

   ::clang::thrift::CXTranslationUnit clang_createTranslationUnit(const  ::clang::thrift::CXIndex idx, const std::string& ast_filename) {
    // Your implementation goes here
    printf("clang_createTranslationUnit\n");
  }

   ::clang::thrift::u32 clang_defaultEditingTranslationUnitOptions() {
    // Your implementation goes here
    printf("clang_defaultEditingTranslationUnitOptions\n");
  }

   ::clang::thrift::CXTranslationUnit clang_parseTranslationUnit(const  ::clang::thrift::CXIndex idx, const std::string& source_filename, const std::vector<std::string> & command_line_args, const std::vector< ::clang::thrift::CXUnsavedFile> & unsaved_files, const  ::clang::thrift::u32 options) {
    // Your implementation goes here
    printf("clang_parseTranslationUnit\n");
  }

   ::clang::thrift::u32 clang_defaultSaveOptions(const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_defaultSaveOptions\n");
  }

   ::clang::thrift::CXSaveError::type clang_saveTranslationUnit(const  ::clang::thrift::CXTranslationUnit unit, const std::string& filename, const  ::clang::thrift::u32 options) {
    // Your implementation goes here
    printf("clang_saveTranslationUnit\n");
  }

  void clang_disposeTranslationUnit(const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_disposeTranslationUnit\n");
  }

   ::clang::thrift::u32 clang_defaultReparseOptions(const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_defaultReparseOptions\n");
  }

  int32_t clang_reparseTranslationUnit(const  ::clang::thrift::CXTranslationUnit unit, const std::vector< ::clang::thrift::CXUnsavedFile> & unsaved_files, const  ::clang::thrift::u32 options) {
    // Your implementation goes here
    printf("clang_reparseTranslationUnit\n");
  }

  void clang_getTUResourceUsageName(std::string& _return, const  ::clang::thrift::CXTUResourceUsageKind::type kind) {
    // Your implementation goes here
    printf("clang_getTUResourceUsageName\n");
  }

  void clang_getCXTUResourceUsage( ::clang::thrift::CXTUResourceUsage& _return, const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_getCXTUResourceUsage\n");
  }

  void clang_disposeCXTUResourceUsage(const  ::clang::thrift::CXTUResourceUsage& usage) {
    // Your implementation goes here
    printf("clang_disposeCXTUResourceUsage\n");
  }

  void clang_getFileName(std::string& _return, const  ::clang::thrift::CXFile file) {
    // Your implementation goes here
    printf("clang_getFileName\n");
  }

   ::clang::thrift::t64 clang_getFileTime(const  ::clang::thrift::CXFile file) {
    // Your implementation goes here
    printf("clang_getFileTime\n");
  }

   ::clang::thrift::u32 clang_isFileMultipleIncludeGuarded(const  ::clang::thrift::CXTranslationUnit unit, const  ::clang::thrift::CXFile file) {
    // Your implementation goes here
    printf("clang_isFileMultipleIncludeGuarded\n");
  }

   ::clang::thrift::CXFile clang_getFile(const  ::clang::thrift::CXTranslationUnit unit, const std::string& filename) {
    // Your implementation goes here
    printf("clang_getFile\n");
  }

  void clang_getNullLocation( ::clang::thrift::CXSourceLocation& _return) {
    // Your implementation goes here
    printf("clang_getNullLocation\n");
  }

   ::clang::thrift::u32 clang_equalLocations(const  ::clang::thrift::CXSourceLocation& loc1, const  ::clang::thrift::CXSourceLocation& loc2) {
    // Your implementation goes here
    printf("clang_equalLocations\n");
  }

  void clang_getLocation( ::clang::thrift::CXSourceLocation& _return, const  ::clang::thrift::CXTranslationUnit tu, const  ::clang::thrift::CXFile file, const  ::clang::thrift::u32 line, const  ::clang::thrift::u32 column) {
    // Your implementation goes here
    printf("clang_getLocation\n");
  }

  void clang_getLocationForOffset( ::clang::thrift::CXSourceLocation& _return, const  ::clang::thrift::CXTranslationUnit tu, const  ::clang::thrift::CXFile file, const  ::clang::thrift::u32 offset) {
    // Your implementation goes here
    printf("clang_getLocationForOffset\n");
  }

  void clang_getNullRange( ::clang::thrift::CXSourceRange& _return) {
    // Your implementation goes here
    printf("clang_getNullRange\n");
  }

  void clang_getRange( ::clang::thrift::CXSourceRange& _return, const  ::clang::thrift::CXSourceLocation& sourceBegin, const  ::clang::thrift::CXSourceLocation& sourceEnd) {
    // Your implementation goes here
    printf("clang_getRange\n");
  }

   ::clang::thrift::u32 clang_equalRanges(const  ::clang::thrift::CXSourceRange& range1, const  ::clang::thrift::CXSourceRange& range2) {
    // Your implementation goes here
    printf("clang_equalRanges\n");
  }

  int32_t clang_Range_isNull(const  ::clang::thrift::CXSourceRange& range) {
    // Your implementation goes here
    printf("clang_Range_isNull\n");
  }

  void clang_getExpansionLocation( ::clang::thrift::CXSourcePosition& _return, const  ::clang::thrift::CXSourceLocation& location) {
    // Your implementation goes here
    printf("clang_getExpansionLocation\n");
  }

  void clang_getPresumedLocation( ::clang::thrift::CXSourcePosition& _return, const  ::clang::thrift::CXSourceLocation& location) {
    // Your implementation goes here
    printf("clang_getPresumedLocation\n");
  }

  void clang_getInstantiationLocation( ::clang::thrift::CXSourcePosition& _return, const  ::clang::thrift::CXSourceLocation& location) {
    // Your implementation goes here
    printf("clang_getInstantiationLocation\n");
  }

  void clang_getSpellingLocation( ::clang::thrift::CXSourcePosition& _return, const  ::clang::thrift::CXSourceLocation& location) {
    // Your implementation goes here
    printf("clang_getSpellingLocation\n");
  }

  void clang_getRangeStart( ::clang::thrift::CXSourceLocation& _return, const  ::clang::thrift::CXSourceRange& range) {
    // Your implementation goes here
    printf("clang_getRangeStart\n");
  }

  void clang_getRangeEnd( ::clang::thrift::CXSourceLocation& _return, const  ::clang::thrift::CXSourceRange& range) {
    // Your implementation goes here
    printf("clang_getRangeEnd\n");
  }

   ::clang::thrift::u32 clang_getNumDiagnosticsInSet(const  ::clang::thrift::CXDiagnosticSet diags) {
    // Your implementation goes here
    printf("clang_getNumDiagnosticsInSet\n");
  }

   ::clang::thrift::CXDiagnostic clang_getDiagnosticInSet(const  ::clang::thrift::CXDiagnosticSet diags, const  ::clang::thrift::u32 index) {
    // Your implementation goes here
    printf("clang_getDiagnosticInSet\n");
  }

   ::clang::thrift::CXDiagnosticSet clang_loadDiagnostics(const std::string& filename) {
    // Your implementation goes here
    printf("clang_loadDiagnostics\n");
  }

  void clang_disposeDiagnosticSet(const  ::clang::thrift::CXDiagnosticSet diagnosticSet) {
    // Your implementation goes here
    printf("clang_disposeDiagnosticSet\n");
  }

   ::clang::thrift::CXDiagnosticSet clang_getChildDiagnostics(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getChildDiagnostics\n");
  }

   ::clang::thrift::u32 clang_getNumDiagnostics(const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_getNumDiagnostics\n");
  }

   ::clang::thrift::CXDiagnostic clang_getDiagnostic(const  ::clang::thrift::CXTranslationUnit unit, const  ::clang::thrift::u32 index) {
    // Your implementation goes here
    printf("clang_getDiagnostic\n");
  }

   ::clang::thrift::CXDiagnosticSet clang_getDiagnosticSetFromTU(const  ::clang::thrift::CXTranslationUnit unit) {
    // Your implementation goes here
    printf("clang_getDiagnosticSetFromTU\n");
  }

  void clang_disposeDiagnostic(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_disposeDiagnostic\n");
  }

  void clang_formatDiagnostic(std::string& _return, const  ::clang::thrift::CXDiagnostic diagnostic, const  ::clang::thrift::u32 options) {
    // Your implementation goes here
    printf("clang_formatDiagnostic\n");
  }

   ::clang::thrift::u32 clang_defaultDiagnosticDisplayOptions() {
    // Your implementation goes here
    printf("clang_defaultDiagnosticDisplayOptions\n");
  }

   ::clang::thrift::CXDiagnosticSeverity::type clang_getDiagnosticSeverity(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticSeverity\n");
  }

  void clang_getDiagnosticLocation( ::clang::thrift::CXSourceLocation& _return, const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticLocation\n");
  }

  void clang_getDiagnosticSpelling(std::string& _return, const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticSpelling\n");
  }

  void clang_getDiagnosticOption( ::clang::thrift::CXDiagnosticOption& _return, const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticOption\n");
  }

   ::clang::thrift::u32 clang_getDiagnosticCategory(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticCategory\n");
  }

  void clang_getDiagnosticCategoryName(std::string& _return, const  ::clang::thrift::u32 category) {
    // Your implementation goes here
    printf("clang_getDiagnosticCategoryName\n");
  }

  void clang_getDiagnosticCategoryText(std::string& _return, const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticCategoryText\n");
  }

   ::clang::thrift::u32 clang_getDiagnosticNumRanges(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticNumRanges\n");
  }

  void clang_getDiagnosticRange( ::clang::thrift::CXSourceRange& _return, const  ::clang::thrift::CXDiagnostic diagnostic, const  ::clang::thrift::u32 range) {
    // Your implementation goes here
    printf("clang_getDiagnosticRange\n");
  }

   ::clang::thrift::u32 clang_getDiagnosticNumFixIts(const  ::clang::thrift::CXDiagnostic diagnostic) {
    // Your implementation goes here
    printf("clang_getDiagnosticNumFixIts\n");
  }

  void clang_getDiagnosticFixIt( ::clang::thrift::CXDiagnosticFixIt& _return, const  ::clang::thrift::CXDiagnostic Diagnostic, const  ::clang::thrift::u32 FixIt) {
    // Your implementation goes here
    printf("clang_getDiagnosticFixIt\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<ClangHandler> handler(new ClangHandler());
  shared_ptr<TProcessor> processor(new ClangProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
