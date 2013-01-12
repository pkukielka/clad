namespace * clang.thrift

include "Types.thrift"
include "TranslationUnit.thrift"
 
/**
 * \brief A particular source file that is part of a translation unit.
 */
typedef Types.ResourceId CXFile
