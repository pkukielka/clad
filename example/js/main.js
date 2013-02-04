function initThrift() {
  var transport = new Thrift.Transport("http://localhost:9090/");
  var protocol  = new Thrift.Protocol(transport);
  var client    = new clad.ClangClient(protocol);
  return client;
}

function parse(client) {
  var tmp_file_name = Math.random().toString(36).substring(7) + ".cpp";
  var unsaved_files = [new clad.CXUnsavedFile({Filename : tmp_file_name, Contents : editor.getValue()})];
  var cmd_line_args = ["-Weverything","-Werror"];

  var index = client.createIndex(0, 0);
  var unit  = client.createTranslationUnitFromSourceFile(index, tmp_file_name, cmd_line_args, unsaved_files);

  var warnings = [];
  var diagnostics_count  = client.getNumDiagnostics(unit);

  for (var i=0; i<diagnostics_count; i++) {
    var diagnostic = client.getDiagnostic(unit, i);
    var error_msg = client.getDiagnosticCategoryText(diagnostic) + ": " + client.getDiagnosticSpelling(diagnostic);
    var location = client.getSpellingLocation(client.getDiagnosticLocation(diagnostic));

    warnings.push({
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

  return warnings;
}