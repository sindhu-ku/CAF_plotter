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
//to do: titles, plot styles should be done better, too repetitive now
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


void HistogramManager::writeHistograms(const HistogramCollection& histograms, const std::string& output_rootfile) {
    TFile* caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
    histograms.part_energy->Write();
    histograms.interaction_vtx_x->Write();
    histograms.interaction_vtx_y->Write();
    histograms.interaction_vtx_z->Write();
    histograms.tracks_Erange_len->Write();
    caf_out_file->Close();
}

void HistogramManager::plotHistograms(const HistogramCollection& histograms, const std::string& output_folder) {
    if (!std::filesystem::exists(output_folder.c_str())) std::filesystem::create_directory(output_folder.c_str());

   
    gStyle->SetLabelSize(0.05, "X");
    gStyle->SetLabelSize(0.05, "Y");
    gStyle->SetTitleSize(0.06, "X");
    gStyle->SetTitleSize(0.06, "Y");
    
    TCanvas *c =  new TCanvas("c", "c", 800, 600);
    gStyle->SetOptStat(0);
     plot1DHistogram(histograms.part_energy, "Reco. particle energy [GeV]", "No. of reco. particles", output_folder, c);    
    plot1DHistogram(histograms.interaction_vtx_x, "Reco. interaction vertex x [cm]", "No. of reco. interactions",  output_folder, c);    
    plot1DHistogram(histograms.interaction_vtx_y, "Reco. interaction vertex y [cm]", "No. of reco. interactions", output_folder, c);    
    plot1DHistogram(histograms.interaction_vtx_z, "Reco. interaction vertex z [cm]", "No. of reco. interactions", output_folder, c);    
    plot2DHistogram(histograms.tracks_Erange_len, "Range-based energy [GeV]", "Track length [cm]", output_folder, c);    
    
}

void HistogramManager::plot1DHistogram(TH1D* hist, const std::string& Xtitle, const std::string& Ytitle, const std::string& output_folder, TCanvas* c) {

    hist->SetLineWidth(2);
    hist->GetXaxis()->SetTitle(Xtitle.c_str());
    hist->GetYaxis()->SetTitle(Ytitle.c_str());
    hist->Draw();
    std::string output_pngfile = output_folder + "/" + hist->GetName() + ".png";
    c->SaveAs(output_pngfile.c_str());
}

void HistogramManager::plot2DHistogram(TH2D* hist, const std::string& Xtitle, const std::string& Ytitle, const std::string& output_folder, TCanvas* c) {

    hist->Draw("colz");
    hist->GetXaxis()->SetTitle(Xtitle.c_str());
    hist->GetYaxis()->SetTitle(Ytitle.c_str());
    std::string output_pngfile = output_folder + "/" + hist->GetName() + ".png";
    c->SaveAs(output_pngfile.c_str());
}

