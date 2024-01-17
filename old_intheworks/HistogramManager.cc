#include "HistogramManager.h"
#include "TFile.h"
#include "TStyle.h"
#include <filesystem>

HistogramCollection HistogramManager::defineHistograms() {
    HistogramCollection histograms;
    
    histograms.part_energy = new TH1D("part_energy","Reconstructed contained particle energy in GeV", 100, 0, 1);
    histograms.interaction_vtx_x = new TH1D("interaction_vtx_x", "Reconstructed interaction vertex x [cm]", 35, -70, 70);
    histograms.interaction_vtx_y = new TH1D("interaction_vtx_y", "Reconstructed interaction vertex y [cm]", 100, -400, -200);
    histograms.interaction_vtx_z = new TH1D("interaction_vtx_z", "Reconstructed interaction vertex z [cm]", 100, 1200, 1400);
    histograms.tracks_Erange_len = new TH2D("tracks_Erange_len", "Reconstructed contained tracks (pdg=13) range-based energy (GeV) vs track length [cm]", 100, 0, 1, 200, 0, 200);    

    return histograms;
}
void HistogramManager::fillRecoIxnHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn){
    histograms.interaction_vtx_x->Fill(sr->common.ixn.dlp[nixn].vtx.x);
    histograms.interaction_vtx_y->Fill(sr->common.ixn.dlp[nixn].vtx.y);
    histograms.interaction_vtx_z->Fill(sr->common.ixn.dlp[nixn].vtx.z);

}

void HistogramManager::fillRecoPartHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart){
    histograms.part_energy->Fill(sr->common.ixn.dlp[nixn].part.dlp[npart].E);

}
void HistogramManager::fillRecoTracksHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int ntrack){
    histograms.tracks_Erange_len->Fill(sr->nd.lar.dlp[nixn].tracks[ntrack].Evis, sr->nd.lar.dlp[nixn].tracks[ntrack].len_cm);

}



void HistogramManager::plotWriteHistograms(const HistogramCollection& histograms, const std::string& output_folder, const std::string& output_rootfile) {
 
    if (!std::filesystem::exists(output_folder.c_str())) std::filesystem::create_directory(output_folder.c_str());

  
    TFile* caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
    
    setStyleTitleHistogram(histograms.part_energy, "Reco. particle energy [GeV]", "No. of reco. particles", output_folder,  false);    
    setStyleTitleHistogram(histograms.interaction_vtx_x, "Reco. interaction vertex x [cm]", "No. of reco. interactions",  output_folder,  false);    
    setStyleTitleHistogram(histograms.interaction_vtx_y, "Reco. interaction vertex y [cm]", "No. of reco. interactions", output_folder,  false);    
    setStyleTitleHistogram(histograms.interaction_vtx_z, "Reco. interaction vertex z [cm]", "No. of reco. interactions", output_folder,  false);    
    setStyleTitleHistogram(histograms.tracks_Erange_len, "Range-based energy [GeV]", "Track length [cm]", output_folder,  true);    
    
    caf_out_file->Close();
    
}

template <typename HistogramType>
void HistogramManager::setStyleTitleHistogram(HistogramType* hist, const std::string& Xtitle, const std::string& Ytitle, const std::string& output_folder, bool H2D) {

    if(!hist){
	return;
    }
    
    TCanvas *c =  new TCanvas(hist->GetName(), hist->GetName(), 800, 600);
    gStyle->SetOptStat(0);
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    gStyle->SetTitleSize(0.06, "X");
    gStyle->SetTitleSize(0.06, "Y");
    
    hist->GetXaxis()->SetTitle(Xtitle.c_str());
    hist->GetYaxis()->SetTitle(Ytitle.c_str());
    
    if(H2D){
	hist->Draw("colz");
    }
    else{
	hist->SetLineWidth(2); 
	hist->Draw();
    }
    
    c->Write();
    
    std::string output_pngfile = output_folder + "/" + hist->GetName() + ".png";
    c->SaveAs(output_pngfile.c_str());
}

