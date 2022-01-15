#include <gtest/gtest.h>

#include "test.h"

void CompressDecompressTest(const string& test_filename, const string& compressed_filename,
                            const string& decompressed_filename, const size_t& expected_ratio,
                            const bool& use_optimized ) {
    CompressFile(test_filename, compressed_filename, use_optimized);
    ExpandFile(compressed_filename, decompressed_filename, use_optimized);

    std::ifstream test_f(test_filename, std::ios::in);
    if (!test_f.is_open()) {
        throw std::invalid_argument("can't open file " + test_filename);
    }
    std::string line, test_input;
    while (std::getline(test_f, line)) {
        test_input += (line + '\n');
        line.clear();
    }
    test_f.close();

    std::ifstream decompressed_f(decompressed_filename, std::ios::in);
    if (!decompressed_f.is_open()) {
        throw std::invalid_argument("can't open file " + decompressed_filename);
    }
    std::string decompressed_input;
    while (std::getline(decompressed_f, line)) {
        decompressed_input += (line + '\n');
    }
    decompressed_f.close();

    EXPECT_EQ(test_input, decompressed_input);

    size_t ratio = CompressionRatio(test_filename, compressed_filename);
    EXPECT_TRUE(ratio >= expected_ratio);
}

TEST(Test1, textAboutInternetAndMind) {
    string test_filename = "../tests/text001.txt";
    string compressed_filename = "../tests/compressed001.txt";
    string decompressed_filename = "../tests/decompressed001.txt";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 160, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 160, true);
}

TEST(Test2, repeatedFourTimesText) {
    string test_filename = "../tests/text002.txt";
    string compressed_filename = "../tests/compressed002.txt";
    string decompressed_filename = "../tests/decompressed002.txt";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 250, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 250, true);
}

TEST(Test3, textAboutLZW) {
    string test_filename = "../tests/text003.txt";
    string compressed_filename = "../tests/compressed003.txt";
    string decompressed_filename = "../tests/decompressed003.txt";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 145, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 145, true);
}

TEST(Test4, simpleString) {
    string test_filename = "../tests/text004.txt";
    string compressed_filename = "../tests/compressed004.txt";
    string decompressed_filename = "../tests/decompressed004.txt";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 150, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 150, true);
}

TEST(Test5, russianText) {
    string test_filename = "../tests/text005.txt";
    string compressed_filename = "../tests/compressed005.txt";
    string decompressed_filename = "../tests/decompressed005.txt";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, true);
}

TEST(Test6, ASCIItable) {
    string test_filename = "../tests/text006.txt";
    string compressed_filename = "../tests/compressed006.txt";
    string decompressed_filename = "../tests/decompressed006.txt";

    std::ofstream test_f(test_filename);
    if (!test_f.is_open()) {
        throw std::invalid_argument("can't open file " + test_filename);
    }
    for (size_t i = 0; i + 1 < ALPHABET_SIZE; ++i) {
        test_f << static_cast<uchar>(i);
    }
    test_f.close();

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, false);
    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, true);
}

TEST(Test7, bmp) {
    string test_filename = "../tests/file007.bmp";
    string compressed_filename = "../tests/compressed007.txt";
    string decompressed_filename = "../tests/decompressed007.bmp";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, false);
}

TEST(Test8, jpg) {
    string test_filename = "../tests/file008.jpg";
    string compressed_filename = "../tests/compressed008.txt";
    string decompressed_filename = "../tests/decompressed008.jpg";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, false);
}

TEST(Test9, jpgCat) {
    string test_filename = "../tests/file009.jpg";
    string compressed_filename = "../tests/compressed009.txt";
    string decompressed_filename = "../tests/decompressed009.jpg";

    CompressDecompressTest(test_filename, compressed_filename, decompressed_filename, 50, false);
}
