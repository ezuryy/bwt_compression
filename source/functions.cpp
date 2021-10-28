#include <functions.h>

void show_options() {
    std::cout << "To compress enter:\n./main -c path/to/input.txt path/to/output.txt\n"
                 "or\n./main --compress path/to/input.txt path/to/output.txt\n"
                 "To decompress enter:\n./main -d path/to/input.txt path/to/output.txt\n"
                 "or\n./main --decompress path/to/input.txt path/to/output.txt\n";
}
