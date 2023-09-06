#ifndef HISTOGRAMMANAGER_H
#define HISTOGRAMMANAGER_H

#include "TH1D.h"
#include "TH2D.h"
#include <vector>
#include "duneanaobj/StandardRecord/StandardRecord.h"
 
struct HistogramCollection {
    TH1D* part_energy;
    TH1D* interaction_vtx_R;
    TH1D* interaction_vtx_x;
    TH1D* interaction_vtx_y;
    TH1D* interaction_vtx_z;
    TH2D* tracks_Ecalo_len;
    TH2D* tracks_Erange_len;
};

class HistogramManager {
public:
    static HistogramCollection defineHistograms();
    static void fillRecoPartHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart);
    static void fillRecoTracksHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int ntrack);
    static void fillRecoIxnHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn);
    static void writeHistograms(const HistogramCollection& histograms, const std::string& output_rootfile);
};

#endif // HISTOGRAMMANAGER_H

