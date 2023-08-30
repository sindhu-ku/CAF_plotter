#ifndef TREELOADER_H
#define TREELOADER_H

#include <string>
#include "TChain.h"

class TreeLoader {
public:
    static TChain* loadTree(const std::string& input_file_list);
};

#endif // TREELOADER_H
