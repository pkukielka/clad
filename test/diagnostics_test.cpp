#include <gtest/gtest.h>
#include "ClangHandler.h"

TEST(FixItTest, ShowCorrectDiagnostics) {
  ClangHandler Clad;
  std::string categoryText;
  ::clad::CXUnsavedFile file;
  file.Filename = "main.cpp";
  file.Contents = "void f1() {};";

  auto index = Clad.createIndex(0, 0);
  auto unit = Clad.createTranslationUnitFromSourceFile(index, "main.cpp", {"-Weverything", "-Werror"}, {file});

  EXPECT_EQ(3, Clad.getNumDiagnostics(unit));

  auto diagnostic = Clad.getDiagnostic(unit, 0);
  EXPECT_EQ(CXDiagnostic_Error, Clad.getDiagnosticSeverity(diagnostic));
  Clad.getDiagnosticCategoryText(categoryText, diagnostic);
  EXPECT_EQ("Semantic Issue", categoryText);
  EXPECT_EQ(0, Clad.getDiagnosticNumFixIts(diagnostic));
  Clad.disposeDiagnostic(diagnostic);

  diagnostic = Clad.getDiagnostic(unit, 1);
  EXPECT_EQ(CXDiagnostic_Error, Clad.getDiagnosticSeverity(diagnostic));
  EXPECT_EQ(1, Clad.getDiagnosticNumFixIts(diagnostic));
  Clad.disposeDiagnostic(diagnostic);

  diagnostic = Clad.getDiagnostic(unit, 2);
  EXPECT_EQ(CXDiagnostic_Error, Clad.getDiagnosticSeverity(diagnostic));
  EXPECT_EQ(1, Clad.getDiagnosticNumFixIts(diagnostic));
  Clad.disposeDiagnostic(diagnostic);

  Clad.disposeDiagnostic(diagnostic);
  Clad.disposeTranslationUnit(unit);
  Clad.disposeIndex(index);
}
