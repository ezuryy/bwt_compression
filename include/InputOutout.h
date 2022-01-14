#ifndef MY_PROJECT_INPUTOUTOUT_H
#define MY_PROJECT_INPUTOUTOUT_H

#include "variables.h"

void ShowOptions();

ofstream OpenOutputBFile(const string& name);

ifstream OpenInputBFile(const string& name);

void CloseOutputBFile(ofstream& bfile_out);

void CloseInputBFile(ifstream& bfile_in);

void WriteBits(ofstream& bfile_out, size_t code, int count);

size_t ReadBits(ifstream& bfile_in, int bit_count);

size_t Filesize(const string& filename);

#endif //MY_PROJECT_INPUTOUTOUT_H
