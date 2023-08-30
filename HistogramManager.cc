#include "HistogramManager.h"
#include "TFile.h"

HistogramCollection HistogramManager::defineHistograms() {
    HistogramCollection histograms;
    
    histograms.part_energy_histogram = new TH1D("part_energy", "part_energy", 100, 0, 300);

    return histograms;
}

void HistogramManager::fillHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart){
    histograms.part_energy_histogram->Fill(sr->common.ixn.dlp[nixn].part.dlp[npart].E);

}

void HistogramManager::writeHistograms(const HistogramCollection& histograms, const std::string& output_rootfile) {
    TFile* caf_out_file = new TFile(output_rootfile.c_str(), "recreate");
    histograms.part_energy_histogram->Write();
    caf_out_file->Close();
}
