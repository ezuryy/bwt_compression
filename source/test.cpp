#include <gtest/gtest.h>

#include "functions.h"

TEST(Test1, textAboutInternetAndMind) {
    string test_filename = "../tests/text001.txt";
    string compressed_filename = "../tests/compressed001.txt";
    string decompressed_filename = "../tests/decompressed001.txt";

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
    EXPECT_TRUE(ratio >= 160);
}

TEST(Test2, repeatedFourTimesText) {
    string test_filename = "../tests/text002.txt";
    string compressed_filename = "../tests/compressed002.txt";
    string decompressed_filename = "../tests/decompressed002.txt";

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
    EXPECT_TRUE(ratio >= 250);
}

TEST(Test3, textAboutLZW) {
    string test_filename = "../tests/text003.txt";
    string compressed_filename = "../tests/compressed003.txt";
    string decompressed_filename = "../tests/decompressed003.txt";

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
    EXPECT_TRUE(ratio >= 145);
}

TEST(Test4, simpleString) {
    string test_filename = "../tests/text004.txt";
    string compressed_filename = "../tests/compressed004.txt";
    string decompressed_filename = "../tests/decompressed004.txt";

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
