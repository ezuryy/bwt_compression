#ifndef MY_PROJECT_BWT_H
#define MY_PROJECT_BWT_H

#include "variables.h"

pair<ustring, int> BWT_encode(const ustring& input);

ustring BWT_decode(const size_t& k, const ustring& last, const bool& use_optimized);

#endif  // MY_PROJECT_BWT_H
