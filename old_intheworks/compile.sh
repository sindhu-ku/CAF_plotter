#compile the CAF plotter
g++ -std=c++17 -O2 -g -pedantic -Wall `root-config --cflags --glibs` main.cc CAFPlotter.cc TreeLoader.cc HistogramManager.cc ApplyCuts.cc -o plotter -I/cvmfs/dune.opensciencegrid.org/products/dune/duneanaobj/v03_01_00/include
if [ $? -eq 0 ]; then
    echo "Compilation successful"
else
    echo "Compilation failed"
fi
