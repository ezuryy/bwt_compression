#ifndef MY_PROJECT_LZW_H
#define MY_PROJECT_LZW_H

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

vector<size_t> LZW_encode(const std::string& input);

string LZW_decode(const vector<size_t>& input);

#endif  // MY_PROJECT_LZW_H
