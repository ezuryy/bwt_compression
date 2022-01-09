#include "functions.h"

std::ifstream bfile_in;
std::ofstream bfile_out;

uchar mask;
int rack;

// Количество битов в коде
#define BITS 12
// Максимальное значение кода (2 ^ 12 - 1)
#define MAX_CODE ((1 << BITS) - 1)
// Размер алфавита, является также кодом конца потока
#define ALPHABET_SIZE 256
// Код первой добавляемой в словарь фразы после записи символов алфавита
#define FIRST_CODE 257

void show_options() {
    std::cout
        << "To compress enter:\n./main -c path/to/input.txt "
           "path/to/output.txt\n"
           "or\n./main --compress path/to/input.txt path/to/output.txt\n"
           "To decompress enter:\n./main -d path/to/input.txt "
           "path/to/output.txt\n"
           "or\n./main --decompress path/to/input.txt path/to/output.txt\n";
}

void OpenOutputBFile(const string& name) {
    bfile_out.open(name, std::ios::out | std::ios::binary);
    if (!bfile_out.is_open()) {
        throw std::invalid_argument("can't open file " + name);
    }
    rack = 0;
    mask = 0x80;
}

void OpenInputBFile(const string& name) {
    bfile_in.open(name, std::ios::in | std::ios::binary);
    if (!bfile_in.is_open()) {
        throw std::invalid_argument("can't open file " + name);
    }
    rack = 0;
    mask = 0x80;
}

void CloseOutputBFile() {
    if (mask != 0x80) {
        bfile_out.put(static_cast<char>(rack));
    }
    bfile_out.close();
}

void CloseInputBFile() { bfile_in.close(); }

void WriteBits(size_t code, int count) {
    size_t mask_;
    mask_ = 1L << (count - 1);
    while (mask_ != 0) {
        if (mask_ & code) {
            rack |= mask;
        }
        mask >>= 1;
        if (mask == 0) {
            bfile_out.put(static_cast<char>(rack));
            rack = 0;
            mask = 0x80;
        }
        mask_ >>= 1;
    }
}

size_t ReadBits(int bit_count) {
    size_t mask_;
    size_t return_value;

    mask_ = 1L << (bit_count - 1);
    return_value = 0;
    while (mask_ != 0) {
        if (mask == 0x80) {
            rack = bfile_in.get();
            if (bfile_in.eof()) {
                throw std::logic_error("error in function ReadBits");
            }
        }
        if (rack & mask) return_value |= mask_;
        mask_ >>= 1;
        mask >>= 1;
        if (mask == 0) mask = 0x80;
    }
    return return_value;
}

size_t filesize(const string& filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

size_t CompressionRatio(const string& input_filename,
                        const string& output_filename) {
    size_t input_size;
    size_t output_size;

    input_size = filesize(input_filename);
    output_size = filesize(output_filename);
    if (output_size == 0) output_size = 1;
    size_t ratio = input_size * 100 / output_size;
    std::cout << "Input size : \t\t" << input_size << " bytes\n";
    std::cout << "Output size : \t\t" << output_size << " bytes\n";
    std::cout << "Сompression ratio : " << ratio << "%\n";
    return ratio;
}

void CompressFile(std::ifstream& input) {
    char symbol;
    std::string full_input;
    while (input.get(symbol)) {
        full_input += symbol;
    }
    auto [bwt_text, bwt_coefficient] = BWT_encode(full_input);

    std::vector<size_t> codes = LZW_encode(bwt_text);

    bfile_out << bwt_coefficient << ' ';
    for (const size_t& code : codes) {
        WriteBits(code, BITS);
    }
    WriteBits(ALPHABET_SIZE, BITS);
}

void ExpandFile(std::ofstream& output) {
    string bwt_coefficient_str;
    int symbol = bfile_in.get();
    while (symbol != int(' ')) {
        bwt_coefficient_str += char(symbol);
        symbol = bfile_in.get();
    }
    size_t bwt_coefficient = stol(bwt_coefficient_str);

    std::vector<size_t> codes;
    size_t new_code;
    size_t old_code = ReadBits(BITS);
    if (old_code == ALPHABET_SIZE) return;
    codes.push_back(old_code);
    while ((new_code = ReadBits(BITS)) != ALPHABET_SIZE) {
        codes.push_back(new_code);
    }
    string bwt_text = LZW_decode(codes);

    string original_text = BWT_decode(bwt_coefficient, bwt_text);

    output << original_text;
}
