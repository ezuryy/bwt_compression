#include <gtest/gtest.h>

#include "functions.h"

TEST(Test1, a) {
    string test_filename = "../results/text.txt";
    string compressed_filename = "../results/compressed.txt";
    string decompressed_filename = "../results/decompressed.txt";

    CompressFile(test_filename, compressed_filename);
    ExpandFile(compressed_filename, decompressed_filename);

    std::ifstream test_f(test_filename, std::ios::in);
    if (!test_f.is_open()) {
        throw std::invalid_argument("can't open file " + test_filename);
    }
    std::string line, test_input;
    while (std::getline(test_f, line)) {
        test_input += (line + '\n');
        line.clear();
    }

    std::ifstream decompressed_f(decompressed_filename, std::ios::in);
    if (!decompressed_f.is_open()) {
        throw std::invalid_argument("can't open file " + decompressed_filename);
    }
    std::string decompressed_input;
    while (std::getline(decompressed_f, line)) {
        decompressed_input += (line + '\n');
    }

    EXPECT_EQ(test_input, decompressed_input);

    size_t ratio = CompressionRatio(test_filename, compressed_filename);
    EXPECT_TRUE(ratio >= 150);
}
