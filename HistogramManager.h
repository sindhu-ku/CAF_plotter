#ifndef HISTOGRAMMANAGER_H
#define HISTOGRAMMANAGER_H

#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include <vector>
#include "duneanaobj/StandardRecord/StandardRecord.h"
 
struct HistogramCollection {
    TH1D* part_energy;
    TH1D* interaction_vtx_x;
    TH1D* interaction_vtx_y;
    TH1D* interaction_vtx_z;
    TH2D* tracks_Erange_len;
};


class HistogramManager {
public:
    static HistogramCollection defineHistograms();
    static void fillRecoPartHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart);
    static void fillRecoTracksHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int ntrack);
    static void fillRecoIxnHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn);
    static void plotWriteHistograms(const HistogramCollection& histograms, const std::string& output_folder, const std::string& output_rootfile);
    template <typename HistogramType>
    static void setStyleTitleHistogram(HistogramType* hist, const std::string& Xtitle, const std::string& Ytitle, const std::string& output_folder, bool H2D);
};

#endif // HISTOGRAMMANAGER_H

