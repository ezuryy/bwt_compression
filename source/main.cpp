#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc == 4) {
        string work_type = argv[1];
        string input_filename = argv[2];
        string output_filename = argv[3];
        if (work_type == "-c" || work_type == "--compress") {
            // compress
            std::ifstream input(input_filename, std::ios::in);
            if (!input.is_open()) {
                throw std::invalid_argument("can't open file " +
                                            input_filename);
            }
            OpenOutputBFile(output_filename);

            CompressFile(input);

            CloseOutputBFile();
            input.close();
            std::cout << "Compression of file " << input_filename
                      << " into file " << output_filename << " is completed.\n";

            CompressionRatio(input_filename, output_filename);

        } else if (work_type == "-d" || work_type == "--decompress") {
            // decompress
            std::ofstream output(output_filename, std::ios::out);
            if (!output.is_open()) {
                throw std::invalid_argument("can't open file " +
                                            output_filename);
            }
            OpenInputBFile(input_filename);

            ExpandFile(output);

            CloseInputBFile();
            output.close();
            std::cout << "Decompression of file " << input_filename
                      << " into file " << output_filename << " is completed.\n";

        } else {
            show_options();
        }
    } else {
        show_options();
    }
    return 0;
}
