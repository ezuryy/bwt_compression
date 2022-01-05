#ifndef MY_PROJECT_LZW_H
#define MY_PROJECT_LZW_H

#include <vector>
#include <unordered_map>
#include <string>

using std::vector;
using std::string;
using std::unordered_map;

vector<size_t> LZW_encode(const std::string& input);

string LZW_decode(const vector<size_t>& input);

#endif //MY_PROJECT_LZW_H
