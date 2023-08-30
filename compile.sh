source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh

#Taken from ND_CAFMaker, some of these might not be necessary
setup cmake v3_22_2
setup gcc v9_3_0
setup ifdhc
setup geant4 v4_11_0_p01c -q e20:debug
setup dk2nugenie   v01_10_01k -q debug:e20
setup genie_xsec   v3_04_00 -q AR2320i00000:e1000:k250
setup genie_phyopt v3_04_00 -q dkcharmtau
setup duneanaobj v03_01_00 -q e20:prof
setup jobsub_client
setup eigen v3_3_5

# shut up ROOT include errors
export ROOT_INCLUDE_PATH=$ROOT_INCLUDE_PATH:$GENIE_INC/GENIE

#compile the CAF plotter
g++ -std=c++17 -O2 -g -pedantic -Wall `root-config --cflags --glibs` caf_plotter.cc -o plotter -I/cvmfs/dune.opensciencegrid.org/products/dune/duneanaobj/v03_01_00/include
if [ $? -eq 0 ]; then
    echo "Compilation successful"
else
    echo "Compilation failed"
fi
