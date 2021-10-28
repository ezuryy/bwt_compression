#include <decompression.h>

string bwt_inverse(const size_t& k, const string& s) {
    vector<size_t> count(256, 0);
    for (char c : s) {
        count[static_cast<size_t>(c)]++;
    }
    size_t sum = 0;
    for (size_t i = 0; i < 256; ++i) {
        sum = sum + count[i];
        count[i] = sum - count[i];
    }
    vector<size_t> reverse_conversion(256,0);
    for (size_t i = 0; i < s.size(); ++i) {
        reverse_conversion[count[s[i]]] = i;
        count[static_cast<size_t>(s[i])]++;
    }
    string answer;
    size_t j = reverse_conversion[k];
    for (size_t i = 0; i < s.size(); ++i) {
        answer += s[j];
        j = reverse_conversion[j];
    }
    return answer;
}
