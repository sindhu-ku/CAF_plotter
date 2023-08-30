#include "TreeLoader.h"
#include <fstream>
#include <iostream>

TChain* TreeLoader::loadTree(const std::string& input_file_list) {
    TChain* caf_chain = new TChain("cafTree");

    std::ifstream caf_list(input_file_list.c_str());

    if (!caf_list.is_open()) {
        std::cerr << "File " << input_file_list << " not found" << std::endl;
        return nullptr;
    }

    std::string tmp;
    while (caf_list >> tmp) {
        caf_chain->Add(tmp.c_str());
        std::cout << "Adding File " << tmp << std::endl;
    }

    if (!caf_chain || caf_chain->GetEntries() == 0) {
        std::cerr << "No tree found in input files" << std::endl;
        delete caf_chain;
        return nullptr;
    }

    caf_list.close();
    return caf_chain;
}

