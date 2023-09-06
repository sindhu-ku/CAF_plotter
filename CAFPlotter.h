#ifndef CAFPLOTTER_H
#define CAFPLOTTER_H

#include <string>
#include "HistogramManager.h"
#include "TreeLoader.h"
#include "TChain.h"

class CAFPlotter {
public:
    CAFPlotter(const std::string& input_file_list, const std::string& output_rootfile);
    void process();

private:
    std::string input_file_list_;
    std::string output_rootfile_;
    TChain* caf_chain_;
};

#endif // CAFPLOTTER_H
