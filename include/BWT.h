#pragma once

#include <functions.h>
#include <unordered_map>

pair<string, size_t> BWT_encode(const string& input);

string BWT_decode(const size_t& k, const string& last);

string BWT_decode_optimized(const size_t& k, const string& last);