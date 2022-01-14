#include "variables.h"
#include "LZW.h"

vector<size_t> LZW_encode(const vector<uchar>& input) {
    unordered_map<string, size_t> dictionary;
    vector<size_t> output;

    if (input.empty()) {
        return output;
    }

    // add all symbols from alphabet to our dictionary
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        dictionary[string(1, char(i))] = dictionary.size();
    }

    string x;
    x += input[0];
    string y;
    size_t next_code = FIRST_CODE;
    for (size_t i = 1; i < input.size(); ++i) {
        y += input[i];

        if (dictionary.find(x + y) != dictionary.end()) {
            x += y;
        } else {
            if (next_code <= MAX_CODE) {
                dictionary[x + y] = next_code;
                ++next_code;
            }
            output.push_back(dictionary[x]);
            x = y;
        }

        if (i + 1 == input.size()) {
            output.push_back(dictionary[y]);
        }
        y.clear();
    }
    return output;
}

string LZW_decode(const vector<size_t>& input) {
    string output;
    vector<string> dictionary;

    // add all symbols from alphabet to our dictionary
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        dictionary.emplace_back(1, char(i));
    }

    if (input.empty()) {
        return output;
    }

    string symbol = dictionary[input[0]];
    output += symbol;
    dictionary.emplace_back("");
    dictionary.push_back(symbol);
    for (size_t i = 1; i < input.size(); ++i) {
        symbol = dictionary[input[i]];
        dictionary[dictionary.size() - 1] += symbol[0];
        symbol = dictionary[input[i]];
        output += symbol;
        if (dictionary.size() <= MAX_CODE) dictionary.push_back(symbol);
    }
    return output;
}