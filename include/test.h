#ifndef MY_PROJECT_TEST_H
#define MY_PROJECT_TEST_H

#include "CompressDecompress.h"

void CompressDecompressTest(const string& test_filename, const string& compressed_filename,
                            const string& decompressed_filename, const size_t& expected_ratio);

void CompressDecompressExpectError(const string& test_filename, const string& compressed_filename,
                                   const string& decompressed_filename);

#endif //MY_PROJECT_TEST_H
