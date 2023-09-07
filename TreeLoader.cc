#include "TreeLoader.h"
#include <fstream>
#include <iostream>

void TreeLoader::SetBranchStatus(TChain* chain){

    chain->SetBranchStatus("*", 0);
    chain->SetBranchStatus("rec.common.ixn.dlp", 1);
    chain->SetBranchStatus("rec.nd.lar.dlp.tracks", 1);
}

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
    }

    if (!caf_chain || caf_chain->GetEntries() == 0) {
        std::cerr << "No tree found in input files" << std::endl;
        delete caf_chain;
        return nullptr;
    }

    caf_list.close();
    
    //Not able to activate ixn branch, not using for now
    //SetBranchStatus(caf_chain); //Activate just the branches needed. 
    
    return caf_chain;
}

