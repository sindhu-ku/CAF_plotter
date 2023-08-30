#include "CAFPlotter.h"
#include "TFile.h"
#include <iostream>
#include <fstream>

CAFPlotter::CAFPlotter(const std::string& input_file_list, const std::string& output_rootfile)
    : input_file_list_(input_file_list), output_rootfile_(output_rootfile),
      caf_chain_(nullptr) {}

void CAFPlotter::process() {
    caf_chain_ = TreeLoader::loadTree(input_file_list_);
    if (!caf_chain_) {
        return;
    }

    HistogramCollection histograms = HistogramManager::defineHistograms();
    
    caf::StandardRecord* sr = nullptr;
    caf_chain_->SetBranchAddress("rec", &sr);

    long Nentries = caf_chain_->GetEntries();
    std::cout << "Total number of spills = " << Nentries << std::endl;

    for (long n = 0; n < Nentries; n++) { // loop over spills/triggers
        if (n % 10000 == 0) std::cout << "Processing trigger " << n << " of " << Nentries << std::endl; 
        caf_chain_->GetEntry(n);
	for(long unsigned nixn = 0; nixn < sr->common.ixn.ndlp; nixn++){ //loop over interactions
		for(long npart = 0; npart < sr->common.ixn.dlp[nixn].part.ndlp; npart++){ //loop over particles
        		if (ApplyCuts(sr, nixn, npart)) HistogramManager::fillHistograms(histograms, sr, nixn, npart);
		}
	}
        
    }

    HistogramManager::writeHistograms(histograms, output_rootfile_);
    
    if (caf_chain_) {
        delete caf_chain_;
    }
}

