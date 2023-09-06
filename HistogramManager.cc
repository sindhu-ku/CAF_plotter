#include "HistogramManager.h"
#include "TFile.h"

HistogramCollection HistogramManager::defineHistograms() {
    HistogramCollection histograms;
    
    histograms.part_energy = new TH1D("part_energy","Reconstructed particle energy in GeV", 100, 0, 1);
    histograms.interaction_vtx_R = new TH1D("interaction_vtx_R", "Reconstructed interaction vertex R [cm]", 200, 0, 200);
    histograms.interaction_vtx_x = new TH1D("interaction_vtx_x", "Reconstructed interaction vertex x [cm]", 400, -200, 200);
    histograms.interaction_vtx_y = new TH1D("interaction_vtx_y", "Reconstructed interaction vertex y [cm]", 400, -200, 200);
    histograms.interaction_vtx_z = new TH1D("interaction_vtx_z", "Reconstructed interaction vertex z [cm]", 400, -200, 200);
    histograms.tracks_Ecalo_len = new TH2D("tracks_Ecalo_len", "Reconstructed tracks calorimetric energy (GeV) vs track length [cm]", 100, 0, 1, 200, 0, 200);    
    histograms.tracks_Erange_len = new TH2D("tracks_Erange_len", "Reconstructed tracks range-based energy (GeV) vs track length [cm]", 100, 0, 1, 200, 0, 200);    

    return histograms;
}

void HistogramManager::fillRecoIxnHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn){
    histograms.interaction_vtx_R->Fill(sqrt(pow(sr->common.ixn.dlp[nixn].vtx.x,2) + pow(sr->common.ixn.dlp[nixn].vtx.y,2) + pow(sr->common.ixn.dlp[nixn].vtx.z,2)));
    histograms.interaction_vtx_x->Fill(sr->common.ixn.dlp[nixn].vtx.x);
    histograms.interaction_vtx_y->Fill(sr->common.ixn.dlp[nixn].vtx.y);
    histograms.interaction_vtx_z->Fill(sr->common.ixn.dlp[nixn].vtx.z);

}

void HistogramManager::fillRecoPartHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart){
    histograms.part_energy->Fill(sr->common.ixn.dlp[nixn].part.dlp[npart].E);

}
void HistogramManager::fillRecoTracksHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int ntrack){
    histograms.tracks_Ecalo_len->Fill(sr->nd.lar.dlp[nixn].tracks[ntrack].Evis, sr->nd.lar.dlp[nixn].tracks[ntrack].len_cm);
    histograms.tracks_Erange_len->Fill(sr->nd.lar.dlp[nixn].tracks[ntrack].E, sr->nd.lar.dlp[nixn].tracks[ntrack].len_cm);

}


void HistogramManager::writeHistograms(const HistogramCollection& histograms, const std::string& output_rootfile) {
    TFile* caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
    histograms.part_energy->Write();
    histograms.interaction_vtx_R->Write();
    histograms.interaction_vtx_x->Write();
    histograms.interaction_vtx_y->Write();
    histograms.interaction_vtx_z->Write();
    histograms.tracks_Ecalo_len->Write();
    histograms.tracks_Erange_len->Write();
    caf_out_file->Close();
}
