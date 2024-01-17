#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include <iostream>
#include <fstream>
#include <string>
#include "duneanaobj/StandardRecord/Proxy/SRProxy.h"


int caf_plotter(std::string input_file_list, std::string output_rootfile){   
  //Define histograms
  TH1D *part_energy_hist = new TH1D("recpart_energy", "Reco particle energy of muons in GeV", 1000, 0, 1);

  //Give an input list
  std::ifstream caf_list(input_file_list.c_str());

  //Check if input list is present
  if(!caf_list.is_open()){
	std::cerr << Form("File %s not found", input_file_list.c_str()) << std::endl;
	return 1;
  }

  //Count the number of files
  int total_files = 0;
  std::string line;
  while (std::getline(caf_list, line)){
	total_files++;
  }
  std::cout << "Total number of CAF trees = " << total_files << std::endl;

  //Rewind the input stream to the beginning of the file
  caf_list.clear();  // Clear any error flags
  caf_list.seekg(0, std::ios::beg);

  long int global_n = 0; //total number of spills
  int treeIndex = 0; //total number of trees

  std::string tmp;
  while(caf_list >> tmp){
 	
		
	TFile *caf_file = new TFile(tmp.c_str(), "read");
    	
	if (!caf_file || caf_file->IsZombie()) {
      		std::cerr << "Error opening file: " << tmp << std::endl;
      		return 1;
    	}
  	
	TTree *caf_tree = (TTree*)caf_file->Get("cafTree");

	if (!caf_tree) {
      		std::cerr << "cafTree not found in file: " << tmp << std::endl;
     		caf_file->Close();
	      	return 1;
    	}
        
 
        if(treeIndex%10 == 0) std::cout << Form("Processing tree %d of %d", treeIndex+1, total_files) << std::endl;
 	
	// Link SRProxy to the current CAF tree

 	caf::SRProxy sr(caf_tree, "");

 	int tree_entries = caf_tree->GetEntries();

 	for(int n = 0; n < tree_entries; ++n){ //Loop over spills/triggers

 	       caf_tree->GetEntry(n); //Get spill from tree

 	       for(long unsigned int nixn = 0; nixn < sr.common.ixn.ndlp; nixn++){ //loop over interactions
           
	           	for(int npart=0; npart < sr.common.ixn.dlp[nixn].part.ndlp; npart++){ //loop over particles

 	       			if(abs(sr.common.ixn.dlp[nixn].part.dlp[npart].pdg) != 13) continue; // just select muons
 	       			part_energy_hist->Fill(sr.common.ixn.dlp[nixn].part.dlp[npart].E);
 	       	 	} //end for particles


	       } //end for interactions
 	 
         }// end for spills
 	
	 global_n = global_n + tree_entries;
	 treeIndex++;
	 caf_file->Close();
	
  } //end loop for trees

  std::cout << Form("Total number of spills processed = %ld", global_n) << std::endl;

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
