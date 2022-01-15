#ifndef MY_PROJECT_COMPRESSDECOMPRESS_H
#define MY_PROJECT_COMPRESSDECOMPRESS_H

#include "variables.h"
#include "BWT.h"
#include "LZW.h"
#include "SuffixTree.h"
#include "InputOutout.h"

size_t CompressionRatio(const string& input_filename,
                        const string& output_filename);

void CompressFile(const std::string& input_filename, const std::string& output_filename, const bool& use_optimized);

void ExpandFile(const std::string& input_filename, const std::string& output_filename, const bool& use_optimized);

#endif  // MY_PROJECT_COMPRESSDECOMPRESS_H
