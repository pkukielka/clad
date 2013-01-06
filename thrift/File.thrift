namespace * clang.thrift

/**
 * File manipulation routines
 */

include "Types.thrift"
include "TranslationUnit.thrift"
 
/**
 * \brief A particular source file that is part of a translation unit.
 */
typedef Types.ResourceId CXFile

service File {
	/**
	 * \brief Retrieve the complete file and path name of the given file.
	 */
	string clang_getFileName(1: CXFile file),

	/**
	 * \brief Retrieve the last modification time of the given file.
	 */
	Types.time_t clang_getFileTime(1: CXFile file),

	/**
	 * \brief Determine whether the given header is guarded against
	 * multiple inclusions, either with the conventional
	 * \#ifndef/\#define/\#endif macro guards or with \#pragma once.
	 */
	Types.uint clang_isFileMultipleIncludeGuarded(1: TranslationUnit.CXTranslationUnit unit, 
																								2: CXFile file),

	/**
	 * \brief Retrieve a file handle within the given translation unit.
	 *
	 * \param tu the translation unit
	 *
	 * \param file_name the name of the file.
	 *
	 * \returns the file handle for the named file in the translation unit \p tu,
	 * or a NULL file handle if the file was not a part of this translation unit.
	 */
	CXFile clang_getFile(1: TranslationUnit.CXTranslationUnit unit, 2: string filename)
}
