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

void CompressFile(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input(input_filename, std::ios::in);
    if (!input.is_open()) {
        throw std::invalid_argument("can't open file " +
                                    input_filename);
    }
    ofstream bfile_out = OpenOutputBFile(output_filename);

    char symbol;
    std::string full_input;
    while (input.get(symbol)) {
        full_input += symbol;
    }

    AdoptedSuffixTree tree;
    tree.createTree(full_input);
    auto [bwt_text, bwt_coefficient] = tree.BWT_encode_optimized();

    std::vector<size_t> codes = LZW_encode(bwt_text);

    bfile_out << bwt_coefficient << ' ';
    for (const size_t& code : codes) {
        WriteBits(bfile_out, code, BITS);
    }
    WriteBits(bfile_out, ALPHABET_SIZE, BITS);

    CloseOutputBFile(bfile_out);
    input.close();
}

void ExpandFile(const std::string& input_filename, const std::string& output_filename) {
    std::ofstream output(output_filename, std::ios::out);
    if (!output.is_open()) {
        throw std::invalid_argument("can't open file " +
                                    output_filename);
    }
    ifstream bfile_in = OpenInputBFile(input_filename);

    string bwt_coefficient_str;
    int symbol = bfile_in.get();
    while (symbol != int(' ')) {
        bwt_coefficient_str += char(symbol);
        symbol = bfile_in.get();
    }
    size_t bwt_coefficient = stol(bwt_coefficient_str);

    std::vector<size_t> codes;
    size_t new_code;
    size_t old_code = ReadBits(bfile_in, BITS);
    if (old_code == ALPHABET_SIZE) return;
    codes.push_back(old_code);
    while ((new_code = ReadBits(bfile_in, BITS)) != ALPHABET_SIZE) {
        codes.push_back(new_code);
    }
    string bwt_text = LZW_decode(codes);

    string original_text = BWT_decode(bwt_coefficient, bwt_text);

    output << original_text;

    CloseInputBFile(bfile_in);
    output.close();
}
