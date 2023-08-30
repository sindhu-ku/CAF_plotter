#include "CAFPlotter.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "\n USAGE: " << argv[0] << " input_caf_file_list output_root_file\n" << std::endl;
        return 1;
    }

    std::string input_file_list = argv[1];
    std::string output_rootfile = argv[2];

    CAFPlotter caf_plotter(input_file_list, output_rootfile);
    caf_plotter.process();

    return 0;
}
