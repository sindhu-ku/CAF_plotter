## CAF plotter

Preliminary attempt at an analysis setup for reading DUNE NDLAr 2x2 CAF files.

## Usage:

### Set up the environment:

`source setup.sh`


### Using a simple macro

* Go to directory:
  ```
  cd simple_macro
  ```
* Compile:
  ```
  ./compile_simple.sh
  ```
* Run the code:
  ```
  ./simple_plotter <input_list> <output_rootfile>`
  ```
* This should produce an output rootfile with the contained reco particle energy 

### Using the "framework"

* Go to main directory:
  ```
  cd ..
  ```
* Compile:
  ```
  ./compile.sh
  ```
* Run the code:
  ```
  ./plotter i <input_list> <output_rootfile> <output_plots_folder>`
  ```
* This should produce an output rootfile and png files of the above-mentioned histograms
  
## Plotting flat CAFs

The python code unfortunately does not work on gpvm due to uproot and possibly other dependencies. Make sure you have the dependencies on your computer if you are planning on using it.

* Download just the python script in the python_flatCAF directory on your computer
* Download a flat CAF file on your computer directly from workshop indico or:
  ```
  scp <username>@dunegpvm07.fnal.gov:/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun4/noGENIEtruth/flat/outputCAF_notruth_27023276_40.flat.root .
  ```
* Run the code:
  ```
  python3 plot_flat_caf.py outputCAF_notruth_27023276_40.flat.root
  ```
* You should have a file named `reco_vs_truth_ixn_vtx_x.png` now
