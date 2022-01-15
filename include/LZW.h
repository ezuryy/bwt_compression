#ifndef MY_PROJECT_LZW_H
#define MY_PROJECT_LZW_H

#include "variables.h"

vector<size_t> LZW_encode(const ustring& input);

ustring LZW_decode(const vector<size_t>& input);

#endif  // MY_PROJECT_LZW_H
