#include "LZW.h"

vector<size_t> LZW_encode(const std::string& input) {
    unordered_map<string, size_t> dictionary;
    vector<size_t> output;

    if (input.empty()) {
        return output;
    }

    // add all symbols from alphabet to our dictionary
    for (size_t i = 0; i < 256; ++i) {
        dictionary[string(1, char(i))] = dictionary.size();
    }

    string x;
    x += input[0];
    string y;
    for (size_t i = 1; i < input.size(); ++i) {
        y += input[i];

        if (dictionary.find(x + y) != dictionary.end()) {
            x += y;
        } else {
            dictionary[x + y] = dictionary.size();
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
    for (size_t i = 0; i < 256; ++i) {
        dictionary.emplace_back(1, char(i));
    }

    if (input.empty()) {
        return output;
    }

    string symbol = dictionary[input[0]];
    output += symbol;
    dictionary.push_back(symbol);
    for (size_t i = 1; i < input.size(); ++i) {
        symbol = dictionary[input[i]];
        dictionary[dictionary.size() - 1] += symbol[0];
        output += symbol;
        dictionary.push_back(symbol);
    }
    return output;
}
