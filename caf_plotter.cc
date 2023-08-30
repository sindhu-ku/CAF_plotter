#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include <string>
#include "duneanaobj/StandardRecord/StandardRecord.h"

int caf_plotter(std::string input_file_list, std::string output_rootfile){

  //Define histograms;
  TH1D *ev = new TH1D("ev", "ev", 6, 189000, 189006);

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

  //maybe add set branch status here
  long Nentries = caf_chain->GetEntries();
  std::cout << Form("Total number of spills = %ld", Nentries) << std::endl;

  //Define Standard Record and link it to the caf_tree
  auto sr = new caf::StandardRecord;
  caf_chain->SetBranchAddress("rec", &sr);

  for(long n = 0; n < Nentries; ++n){ //Loop over spills/triggers
	if(n%10000 == 0) std::cout << Form("Processing trigger %ld of %ld", n, Nentries) << std::endl;
	caf_chain->GetEntry(n); //Get spill from tree
	ev->Fill(sr->meta.nd_lar.event);
//		std::cout << sr->common.ixn.ndlp << std::endl;
  }// end for spills
  TFile *caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
  ev->Write();
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
