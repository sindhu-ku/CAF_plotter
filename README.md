## CAF plotter

Preliminary attempt at an analysis setup for reading DUNE NDLAr 2x2 CAF files.

## Usage:

### Set up the environment:

`source setup.sh`


### Using a simple macro with SRProxy for structured and flat CAFs

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
  ./simple_plotter <input_list> <output_rootfile> <CAF_type>
  ```
* This should produce an output rootfile with the contained reco particle energy 
  
### Plotting flat CAFs with python

The python code unfortunately does not work on gpvm due to uproot and possibly other dependencies. Make sure you have the dependencies on your computer if you are planning on using it.

* Download the python script in the python_flatCAF directory on your computer
* Download a flat CAF file on your computer directly:
  ```
  scp <username>@dunegpvm07.fnal.gov:/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/PicoRun4.2_1E17_RHC.flow.00004.FLOW_CAF.flat.root .
  ```
* Run the code:
  ```
  python3 plot_flat_caf.py PicoRun4.2_1E17_RHC.flow.00004.FLOW_CAF.flat.root
  ```
* You should have an output png file now
