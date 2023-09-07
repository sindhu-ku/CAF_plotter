#include "CAFPlotter.h"

int main(int argc, char** argv) {
    if (argc != 4) {
        std::cout << "\n USAGE: " << argv[0] << " input_caf_file_list output_root_file output_plots_folder\n" << std::endl;
        return 1;
    }

    std::string input_file_list = argv[1];
    std::string output_rootfile = argv[2];
    std::string output_plots_folder = argv[3];

    CAFPlotter caf_plotter(input_file_list, output_rootfile, output_plots_folder);
    caf_plotter.process();

    return 0;
}
