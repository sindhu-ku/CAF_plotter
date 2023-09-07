#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include <string>
#include "duneanaobj/StandardRecord/StandardRecord.h"

int caf_plotter(std::string input_file_list, std::string output_rootfile){

  //Define histograms
  TH1D *part_energy_hist = new TH1D("recpart_energy", "Reco particle energy in GeV", 100, 0, 1);

  //Give an input list
  std::ifstream caf_list(input_file_list.c_str());

  //Check if input list is present
  if(!caf_list.is_open()){
	std::cerr << Form("File %s not found", input_file_list.c_str()) << std::endl;
	return 1;
  }

  //Add files to CAF chain from input list
  std::string tmp;
  TChain *caf_chain = new TChain("cafTree");

  while(caf_list >> tmp){
	caf_chain->Add(tmp.c_str());
	std::cout << Form("Adding File %s", tmp.c_str()) << std::endl;
  }

  //Check if CAF tree is present
  if(!caf_chain){
	std::cerr << Form("There is no tree in %s", tmp.c_str()) << std::endl;
	return 1;
  }

  long Nentries = caf_chain->GetEntries();
  std::cout << Form("Total number of spills = %ld", Nentries) << std::endl;

  //Define Standard Record and link it to the CAF tree branch "rec"
  auto sr = new caf::StandardRecord;
  caf_chain->SetBranchAddress("rec", &sr);

  for(long n = 0; n < Nentries; ++n){ //Loop over spills/triggers

	if(n%10000 == 0) std::cout << Form("Processing trigger %ld of %ld", n, Nentries) << std::endl;
	caf_chain->GetEntry(n); //Get spill from tree

	for(long unsigned nixn = 0; nixn < sr->common.ixn.dlp.size(); nixn++){ //loop over interactions
		for(long unsigned npart=0; npart < sr->common.ixn.dlp[nixn].part.dlp.size(); npart++){ //loop over particles
			if(!sr->common.ixn.dlp[nixn].part.dlp[npart].contained) continue; // just select contained particles
			part_energy_hist->Fill(sr->common.ixn.dlp[nixn].part.dlp[npart].E);
		} //end for particles
	} //end for interactions
  }// end for spills

  //Create output file and write your histograms
  TFile *caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
  part_energy_hist->Write();
  caf_out_file->Close();

  return 1;  
}

int main(int argc, char** argv){

  if(argc!=3){
    std::cout << "\n USAGE: " << argv[0] << "input_caf_file_list output_root_file\n" << std::endl;
    return 1;
  }

  std::string input_file_list = argv[1];
  std::string output_rootfile = argv[2];

  caf_plotter(input_file_list, output_rootfile);

  return 0;
}
