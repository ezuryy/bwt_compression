#ifndef MY_PROJECT_BWT_H
#define MY_PROJECT_BWT_H

#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

using std::pair;
using std::string;
using std::vector;

typedef unsigned char uchar;

pair<string, size_t> BWT_encode(const string& input);

string BWT_decode(const size_t& k, const string& last);

string BWT_decode_optimized(const size_t& k, const string& last);

#endif  // MY_PROJECT_BWT_H
