# File locations

Run used: Minirun4

Inputs for ND_CAFMaker:

* MLreco h5 files: `/dune/data/users/drielsma/minirun4/*.h5`

CAF files:

* Structured CAF rootfiles without any truth: `/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun4/notruth/*.root`
* Flat CAF rootfiles with pass through truth from reco: `/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun4/noGENIEtruth/flat/*.root`

# Preparation

* Clone this repository: `git clone https://github.com/sindhu-ku/CAF_plotter.git`
* Set up environment: `source setup.sh`

# What is in this repository

* simple macro directory: A simple C++ macro that plots the energy of contained reconstructed particles (works on DUNE gpvm)
* python_flatCAF directory: Plots truth and reco interaction vertex x from flat CAFs using uproot and pandas (does not work on DUNE gpvm)
* main directory: something framework-y that manages histograms and cuts in different Classes. Writes and plots the following histograms: contained reco particle energy, interaction vertices, calorimetric energy vs track length for reconstructed tracks (works on DUNE gpvm) 

# Plotting structured CAFs

* Make an input list of CAF files:
`ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun4/notruth/*.root >> input_str-caf_notruth.list`

## Using a simple macro

* Go to directory: `cd simple_macro`
* Compile: `./compile_simple.sh`
* Run the code: `./simple_plotter ../input_str-caf_notruth.list output_simple_minirun4.root`

## Using the "framework"

* Go to main directory: `cd ..`
* Compile: `./compile.sh`
* Run the code: `./plotter input_str-caf_notruth.list output_minirun4_notruth.root plots_minirun4`
  
# Plotting flat CAFs

The python code unfortunately does not work on gpvm due to uproot and possibly panda dependencies. Make sure you have the dependencies on your computer if you are planning on using it.

* Download a flat CAF file on your computer directly from workshop indico or: `scp <username>@dunegpvm07.fnal.gov:/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun4/noGENIEtruth/flat/outputCAF_notruth_27023276_40.flat.root`
* Go to directory: `cd python_flatCAF`
* Run the code: `python3 plot_flat_caf.py outputCAF_notruth_27023276_40.flat.root`
* You should have file named `reco_vs_truth_ixn_vtx_x.png` now



