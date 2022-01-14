#ifndef MY_PROJECT_BWT_H
#define MY_PROJECT_BWT_H

#include "variables.h"

pair<string, size_t> BWT_encode(const string& input);

string BWT_decode(const size_t& k, const string& last);

#endif  // MY_PROJECT_BWT_H
