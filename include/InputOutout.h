#ifndef MY_PROJECT_INPUTOUTOUT_H
#define MY_PROJECT_INPUTOUTOUT_H

#include "variables.h"

struct InputOutput {
    uchar mask = 0x80;
    int rack = 0;
    ofstream bfile_out;
    ifstream bfile_in;

    void OpenOutputBFile(const string& name);
    void OpenInputBFile(const string& name);
    void CloseOutputBFile();
    void CloseInputBFile();
    void WriteBits(size_t code, int count);
    size_t ReadBits(int bit_count);
    bool InputReadable();
};

void ShowOptions();

size_t Filesize(const string& filename);

#endif //MY_PROJECT_INPUTOUTOUT_H
