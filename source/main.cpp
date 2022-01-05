#include <BWT.h>
#include <LZW.h>

int main() {
    string input;
    std::cin >> input;
    auto output = LZW_encode(input);
    for (const auto& number : output) {
        std::cout << number << " ";
    }
    std::cout << "\n";

    string result_of_decoding = LZW_decode(output);
    std::cout << result_of_decoding << "\n";
}

//int main(int argc, char *argv[]) {
//    if (argc == 1) {
//        string input;
//        std::cin >> input;
//        auto compressed = bwt(input);
//        std::cout << compressed.first << " " << compressed.second << "\n";
//        string decompressed = bwt_inverse(compressed.second, compressed.first);
//        std::cout << decompressed << "\n";
//    } else if (argc == 4) {
//        string work_type = argv[1];
//        string input_filename = argv[2];
//        string output_filename = argv[3];
//        if (work_type == "-c" || work_type == "--compress") {
//            //compress
//        } else if (work_type == "-d" || work_type == "--decompress") {
//            //decompress
//        } else {
//            show_options();
//        }
//    } else {
//        show_options();
//    }
//    return 0;
//}
