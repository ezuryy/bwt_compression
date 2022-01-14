#ifndef MY_PROJECT_FUNCTIONS_H
#define MY_PROJECT_FUNCTIONS_H

#include "variables.h"
#include "BWT.h"
#include "LZW.h"
#include "SuffixTree.h"

void ShowOptions();

void OpenOutputBFile(const string& name);

void OpenInputBFile(const string& name);

void CloseOutputBFile();

void CloseInputBFile();

void WriteBits(size_t code, int count);

size_t ReadBits(int bit_count);

size_t Filesize(const string& filename);

size_t CompressionRatio(const string& input_filename,
                        const string& output_filename);

void CompressFile(const std::string& input_filename, const std::string& output_filename);

void ExpandFile(const std::string& input_filename, const std::string& output_filename);

#endif  // MY_PROJECT_FUNCTIONS_H
