importScripts('vendor/thrift.js');
importScripts('clad/Clang_types.js');
importScripts('clad/Diagnostic_types.js');
importScripts('clad/File_types.js');
importScripts('clad/Index_types.js');
importScripts('clad/Location_types.js');
importScripts('clad/TranslationUnit_types.js');
importScripts('clad/Types_types.js');
importScripts('clad/Clang.js');

function initThriftClient() {
  var transport = new Thrift.Transport("http://localhost:9090/");
  var protocol  = new Thrift.Protocol(transport);
  var client    = new clad.ClangClient(protocol);
  return client;
}

function getDiagnostics(client, source) {
  var tmp_file_name = Math.random().toString(36).substring(7) + ".cpp";
  var unsaved_files = [new clad.CXUnsavedFile({Filename : tmp_file_name, Contents : source})];
  var cmd_line_args = ["-Weverything", "-Werror", "-Wno-c++98-compat", "-std=c++11"];

  var index = client.createIndex(0, 0);
  var unit  = client.createTranslationUnitFromSourceFile(index, tmp_file_name, cmd_line_args, unsaved_files);

  var diagnostics = [];
  var diagnostics_count  = client.getNumDiagnostics(unit);

  for (var i=0; i<diagnostics_count; i++) {
    var diagnostic = client.getDiagnostic(unit, i);
    var error_msg = client.getDiagnosticCategoryText(diagnostic) + ": " + client.getDiagnosticSpelling(diagnostic);
    var location = client.getSpellingLocation(client.getDiagnosticLocation(diagnostic));

    diagnostics.push({
      row:    location.line - 1,
      column: location.column - 1,
      offset: location.offset,
      text:   error_msg,
      type:   "warning"
    });
    client.disposeDiagnostic(diagnostic);
  }

  client.disposeTranslationUnit(unit);
  client.disposeIndex(index);

  return diagnostics;
}

var client = initThriftClient();

self.onmessage = function(event) {
  self.postMessage(getDiagnostics(client, event.data));
};