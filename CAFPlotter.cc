#include "CAFPlotter.h"
#include "ApplyCuts.h"
#include "TFile.h"
#include <iostream>
#include <fstream>

CAFPlotter::CAFPlotter(const std::string& input_file_list, const std::string& output_rootfile, const std::string& output_plots_folder)
    : input_file_list_(input_file_list), output_rootfile_(output_rootfile), output_plots_folder_(output_plots_folder),
      caf_chain_(nullptr) {}


void CAFPlotter::process() {
    //Load CAF trees
    caf_chain_ = TreeLoader::loadTree(input_file_list_);
    if (!caf_chain_) {
        return;
    }
    std::cout << "Total number of CAF trees = " << caf_chain_->GetNtrees() << std::endl;
    
    //Define histograms
    HistogramCollection histograms = HistogramManager::defineHistograms();
    
    //Link Standard Record
    caf::StandardRecord* sr = nullptr;
    caf_chain_->SetBranchAddress("rec", &sr);

    long Nentries = caf_chain_->GetEntries();
    std::cout << "Total number of spills = " << Nentries << std::endl;

    //Event loop
    for (long n = 0; n < Nentries; n++) { // loop over spills/triggers
//	if(n > 5) continue;
        if (n % 10000 == 0) std::cout << "Processing trigger " << n << " of " << Nentries << std::endl; 
        caf_chain_->GetEntry(n);
	for(long unsigned nixn = 0; nixn < sr->common.ixn.dlp.size(); nixn++){ //loop over reconstructed interactions
		RecoIxn recixn_cuts = applyCuts(sr, nixn);
		bool skip_naninf = recixn_cuts.skip_naninf; //skipping values that are nan/inf for now, issue needs more study 

		//Fill reco interaction related histograms here
		if (skip_naninf) HistogramManager::fillRecoIxnHistograms(histograms, sr, nixn);

		for(long unsigned npart = 0; npart < sr->common.ixn.dlp[nixn].part.dlp.size(); npart++){ //loop over reconstructed particles
			//Write cuts for reco particles here
			RecoPart recp_cuts = applyCuts(sr,nixn, npart);
			bool contained = recp_cuts.contained; //Ideally one must get the correct interaction id from the truth branch, because the vec idx will be different inside dlp. Currently there is a bug in SR that should be fixed.
			
			//Fill reco particle histograms
        	        if(contained) HistogramManager::fillRecoPartHistograms(histograms, sr, nixn, npart);
		}
		
		for(long unsigned ntrack = 0; ntrack < sr->nd.lar.dlp[nixn].tracks.size(); ntrack++){ //loop over reconstructed tracks
                        
			int ixnid = sr->nd.lar.dlp[nixn].tracks[ntrack].truth.ixn; //Actual interaction id of the track
			//Find which idx in the vector corresponds to the interaction id ixnid
			auto itIxn = std::find_if(sr->common.ixn.dlp.begin(), sr->common.ixn.dlp.end(),
                                [ixnid](const caf::SRInteraction & ixn){ return ixn.id == ixnid; });
      			if (itIxn == sr->common.ixn.dlp.end())
     			{
        		std::cout << "Particle's interaction ID (" << ixnid << ") does not match any in the DLP set!" << std::endl;
      			}
			int intid_vecidx = std::distance(sr->common.ixn.dlp.begin(), itIxn); //vec idx of this interaction 
                        int partid = sr->nd.lar.dlp[intid_vecidx].tracks[ntrack].truth.part; //Get the particle id of this track to select muons

	
			//This should work once the SR bug is fixed
                /*      auto itPart = std::find_if(sr->common.ixn.dlp[initid_vecidx].part.dlp.begin(), sr->common.ixn.dlp[intid_vecidx].part.dlp.end(),
                                [partid](const caf::SRRecoParticle & part){ return part.id == partid; });
                        if (itPart == sr->common.ixn.dlp[intid_vecidx].part.dlp.end())
                        {
                        std::cout << "Particle ID (" << partid << ") does not match any in the DLP set!" << std::endl;
                        }
			
			int partid_vecidx = std::distance(sr->common.ixn.dlp[intid_vecidx].part.dlp.begin(), itPart);
		*/
			/*RecoTrack rect_cuts = applyCuts(sr, intid_vecidx, ntrack, partid_vecidx); //Select only muons
			bool muon = rect_cuts.muon;
			if(!muon) continue;			
			*/
			HistogramManager::fillRecoTracksHistograms(histograms, sr, nixn, ntrack);
		}
	}
        
    }

    
    //Write and plot histograms
    HistogramManager::writeHistograms(histograms, output_rootfile_);
    HistogramManager::plotHistograms(histograms, output_plots_folder_);
    
    if (caf_chain_) {
        delete caf_chain_;
    }
}

