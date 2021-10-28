#include <compression.h>

pair<string, size_t> bwt(const string& input) {
    vector<string> cyclic_shifts;
    for (size_t i = 0; i < input.size(); ++i) {
        string next = string(input, i, input.size() - i) + string(input, 0, i);
        cyclic_shifts.push_back(next);
    }
    std::sort(cyclic_shifts.begin(), cyclic_shifts.end());
    auto iter = std::find(cyclic_shifts.begin(), cyclic_shifts.end(), input);
    size_t index = iter - cyclic_shifts.begin();
    string compressed;
    for (size_t i = 0; i < input.size(); ++i) {
        compressed += cyclic_shifts[i][input.size() - 1];
    }
    return {compressed, index};
}