#compile the CAF plotter

g++ -std=c++17 -O2 -g -pedantic -Wall `root-config --cflags --glibs` simple_caf_plotter_flat.cc -o simple_plotter_flat -I/cvmfs/dune.opensciencegrid.org/products/dune/duneanaobj/v03_02_01/include -I$SRPROXY_INC -L$DUNEANAOBJ_LIB -lduneanaobj_StandardRecordProxy
if [ $? -eq 0 ]; then
    echo "Compilation successful"
else
    echo "Compilation failed"
fi
