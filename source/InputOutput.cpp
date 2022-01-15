#include "InputOutout.h"

void InputOutput::OpenOutputBFile(const string& name) {
    bfile_out.open(name, std::ios::out | std::ios::binary);
    if (!bfile_out.is_open()) {
        throw std::invalid_argument("can't open file " + name);
    }
//    rack = 0;
//    mask = 0x80;
}

void InputOutput::OpenInputBFile(const string& name) {
    bfile_in.open(name, std::ios::in | std::ios::binary);
    if (!bfile_in.is_open()) {
        throw std::invalid_argument("can't open file " + name);
    }
//    rack = 0;
//    mask = 0x80;
//    return bfile_in;
}

void InputOutput::CloseOutputBFile() {
    if (mask != 0x80) {
        bfile_out.put(static_cast<char>(rack));
    }
    bfile_out.close();
}

void InputOutput::CloseInputBFile() {
    bfile_in.close();
}

void InputOutput::WriteBits(size_t code, int count) {
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

size_t InputOutput::ReadBits(int bit_count) {
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

bool InputOutput::InputReadable() {
    return !bfile_in.eof();
}

void ShowOptions() {
    std::cout
            << "To compress enter:\n./main -c path/to/input.txt "
               "path/to/output.txt\n"
               "or\n./main --compress path/to/input.txt path/to/output.txt\n"
               "To decompress enter:\n./main -d path/to/input.txt "
               "path/to/output.txt\n"
               "or\n./main --decompress path/to/input.txt path/to/output.txt\n";
}

size_t Filesize(const string& filename) {
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

