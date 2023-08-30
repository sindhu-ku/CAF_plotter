#ifndef HISTOGRAMMANAGER_H
#define HISTOGRAMMANAGER_H

#include "TH1D.h"
#include <vector>
#include "duneanaobj/StandardRecord/StandardRecord.h"
 
struct HistogramCollection {
    TH1D* part_energy_histogram;
};

class HistogramManager {
public:
    static HistogramCollection defineHistograms();
    static void fillHistograms(HistogramCollection& histograms, const caf::StandardRecord* sr, int nixn, int npart);
    static void writeHistograms(const HistogramCollection& histograms, const std::string& output_rootfile);
};

#endif // HISTOGRAMMANAGER_H

