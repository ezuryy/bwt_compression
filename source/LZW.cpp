#include "variables.h"
#include "LZW.h"

vector<size_t> LZW_encode(const ustring& input) {
    auto hash = [](const ustring& str){
        size_t hash = 5381;
        size_t c;
        size_t i = 0;
        while (i < str.size()) {
            c = (size_t) str[i];
            hash = ((hash << 5) + hash) + c;
            ++i;
        }
        return hash;
    };
    auto equal = [](const ustring& l, const ustring& r){
        return l == r;
    };
    std::unordered_map<ustring, size_t, decltype(hash), decltype(equal)> dictionary(8, hash, equal);

//    unordered_map<ustring, size_t> dictionary = unordered_map<ustring, size_t>();
    vector<size_t> output;

    if (input.empty()) {
        return output;
    }

    // add all symbols from alphabet to our dictionary
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        dictionary[ustring(1, char(i))] = dictionary.size();
    }

    ustring x;
    x += input[0];
    if (input.size() == 1) {
        output.push_back(dictionary[x]);
    }
    ustring y;
    size_t next_code = FIRST_CODE;
    for (size_t i = 1; i < input.size(); ++i) {
        y += input[i];
        if (dictionary.find(x + y) != dictionary.end()) {
            x += y;
            if (i + 1 == input.size()) {
                output.push_back(dictionary[x]);
                break;
            }
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

ustring LZW_decode(const vector<size_t>& input) {
    ustring output;
    vector<ustring> dictionary;

    // add all symbols from alphabet to our dictionary
    for (size_t i = 0; i < ALPHABET_SIZE; ++i) {
        ustring phrase = {uchar(i)};
        dictionary.emplace_back(phrase);
    }

    if (input.empty()) {
        return output;
    }

    ustring symbol = dictionary[input[0]];
    output += symbol;
    dictionary.push_back({END_SYMBOL});
    dictionary.push_back(symbol);
    for (size_t i = 1; i < input.size(); ++i) {
        symbol = dictionary[input[i]];
        dictionary[dictionary.size() - 1] += symbol[0];
        symbol = dictionary[input[i]];
        output += symbol;
        if (dictionary.size() <= MAX_CODE)
            dictionary.push_back(symbol);
    }
    return output;
}
