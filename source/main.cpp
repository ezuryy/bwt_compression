#include "functions.h"

int main(int argc, char *argv[]) {
    if (argc == 4) {
        string work_type = argv[1];
        string input_filename = argv[2];
        string output_filename = argv[3];
        if (work_type == "-c" || work_type == "--compress") {
            // compress
            CompressFile(input_filename, output_filename);

            std::cout << "Compression of file " << input_filename
                      << " into file " << output_filename << " is completed.\n";

            CompressionRatio(input_filename, output_filename);

        } else if (work_type == "-d" || work_type == "--decompress") {
            // decompress
            ExpandFile(input_filename, output_filename);

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
