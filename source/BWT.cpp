#include "BWT.h"

pair<ustring, int> BWT_encode(const ustring& input) {
    vector<ustring> cyclic_shifts;                // memory: O(N ^ 2)
    for (size_t i = 0; i < input.size(); ++i) {  // time: O(N)
        ustring next = ustring(input, i, input.size() - i) + ustring(input, 0, i);
        cyclic_shifts.push_back(next);
    }
    std::sort(cyclic_shifts.begin(), cyclic_shifts.end());  // time: O(N*logN)
    auto iter = std::find(cyclic_shifts.begin(), cyclic_shifts.end(),
                          input);  // time: O(N)
    size_t index = iter - cyclic_shifts.begin();
    ustring compressed;
    for (size_t i = 0; i < input.size(); ++i) {  // time: O(N)
        compressed += cyclic_shifts[i][input.size() - 1];
    }
    return {compressed, index};
}

ustring BWT_decode(const size_t& k, const ustring& last, const bool& use_optimized) {
    // get first column in matrix of cyclic shifts
    ustring first = last;           // memory: O(N)

    std::sort(first.begin(), first.end());  // time: O(N*logN)

    // match the characters to their first positions in the sorted array
    std::unordered_map<uchar, size_t>
        first_positions;  // memory: O(N) -- in the worst case
    for (size_t i = 0; i < first.size(); ++i) {  // time: O(N)
        if (first_positions.find(first[i]) == first_positions.end()) {
            first_positions[first[i]] = i;
        }
    }

    // build list of predecessor characters
    // T represents a one-to-one correspondence between elements of 'first' and
    // elements of 'last'
    vector<size_t> T;        // memory: O(N)
    for (uchar ch : last) {  // time: O(N)
        T.push_back(first_positions.at(ch));
        ++first_positions[ch];
    }

    ustring answer;                              // memory: O(N)
    size_t current_index = k;                   // memory: O(1)
    for (size_t i = 0; i < last.size(); ++i) {  // time: O(N)
        answer.push_back(last[current_index]);
        current_index = T[current_index];
    }
    std::reverse(answer.begin(), answer.end());  // time: O(N/2)
    if (use_optimized) {
        return {answer.begin() + 1, answer.end()};
    }
    return {answer.begin(), answer.end()};
}
