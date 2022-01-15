#include "CompressDecompress.h"

size_t CompressionRatio(const string& input_filename,
                        const string& output_filename) {
    size_t input_size;
    size_t output_size;

    input_size = Filesize(input_filename);
    output_size = Filesize(output_filename);
    if (output_size == 0) output_size = 1;
    size_t ratio = input_size * 100 / output_size;
    std::cout << "Input size : \t\t" << input_size << " bytes\n";
    std::cout << "Output size : \t\t" << output_size << " bytes\n";
    std::cout << "Сompression ratio : " << ratio << "%\n";
    return ratio;
}

void CompressFile(const std::string& input_filename, const std::string& output_filename, const bool& use_optimized) {
    std::ifstream input(input_filename, std::ios::in);
    if (!input.is_open()) {
        throw std::invalid_argument("can't open file " +
                                    input_filename);
    }
    ofstream bfile_out = OpenOutputBFile(output_filename);

    char symbol;
    ustring full_input;
    while(!input.eof()) {
        size_t i = 0;
        while (i < BATCH_SIZE && input.get(symbol)) {
            full_input += uchar(symbol);
            ++i;
        }
        ustring bwt_text;
        int bwt_coefficient;
        std::vector<size_t> codes;
        if (use_optimized) {
            AdoptedSuffixTree tree(full_input);
            auto result = tree.BWT_encode_optimized();
            bwt_text = result.first;
            bwt_coefficient = result.second;
        } else {
            auto result = BWT_encode(full_input);
            bwt_text = result.first;
            bwt_coefficient = result.second;
        }
        codes = LZW_encode(bwt_text);
        WriteBits(bfile_out, bwt_coefficient, BITS);
        for (const size_t &code: codes) {
            WriteBits(bfile_out, code, BITS);
        }
        WriteBits(bfile_out, ALPHABET_SIZE, BITS);
        full_input.clear();
    }
    CloseOutputBFile(bfile_out);
    input.close();
}

void ExpandFile(const std::string& input_filename, const std::string& output_filename, const bool& use_optimized) {
    std::ofstream output(output_filename, std::ios::out);
    if (!output.is_open()) {
        throw std::invalid_argument("can't open file " +
                                    output_filename);
    }
    ifstream bfile_in = OpenInputBFile(input_filename);

    string bwt_coefficient_str;

    while(!bfile_in.eof()) {
        size_t bwt_coefficient = 0;
        try {
            bwt_coefficient = ReadBits(bfile_in, BITS);
        } catch (...) {
            break;
        }
        std::vector<size_t> codes;
        size_t new_code;

        while ((new_code = ReadBits(bfile_in, BITS)) != ALPHABET_SIZE) {
            codes.push_back(new_code);
        }
        ustring bwt_text = LZW_decode(codes);

        ustring original_text = BWT_decode(bwt_coefficient, bwt_text, use_optimized);

        for (const auto &ch: original_text) {
            output << ch;
        }
    }

    CloseInputBFile(bfile_in);
    output.close();
}
