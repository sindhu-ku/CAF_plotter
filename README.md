## CAF plotter

Preliminary attempt at an analysis setup for reading DUNE NDLAr 2x2 CAF files.

## Usage:

Set up the environment and compile the code:

`./compile.sh`

## Running the code:

`./plotter <input_rootfile_list> <output_rootfile.root>`

## Using a simple CAF plotter for reference:

Compile:

`g++ -std=c++17 -O2 -g -pedantic -Wall `root-config --cflags --glibs` simple_caf_plotter.cc -o simple_plotter -I/cvmfs/dune.opensciencegrid.org/products/dune/duneanaobj/v03_01_00/include`

Run it:

'./simple_plotter <input_rootfile_list> <output_rootfile.root>``
