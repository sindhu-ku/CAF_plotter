## CAF structure

A quick overview of the CAF structure can be found [here](https://drive.google.com/file/d/1-jdDoc89lTVQGPX4RDChJjJKRoMrtY84/view?usp=sharing).
If you want to know more about all the variables in the different branches, see the object format for the `StandardRecord` objects defined in [`duneanaobj`](https://github.com/DUNE/duneanaobj)

## How to make CAFs

Run used: Picorun 4.2


MLreco inputs for [`ND_CAFMaker`](https://github.com/DUNE/ND_CAFMaker) that produces the CAF files:

* MLreco h5 files:
  ```
  /dune/data/users/drielsma/minirun4/*.h5
  ```
* An example cfg file to produce CAFs: 

## File locations

CAF files:

* Structured CAFs:
   ```
  /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/*.root
  ```
* Flat CAFs:
  ```
  /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/*.root
  ```

## Preparation

* Clone this repository on DUNE gpvm:
  ```
  git clone https://github.com/sindhu-ku/CAF_plotter.git
  ```
* Set up environment (same as `ND_CAFMaker`):
  ```
  source setup.sh
  ```

## What is in this repository (Version used for tutorial v2.0.0)

* simple_macro directory:

  -A simple C++ macro that plots the energy of reconstructed particles tagged as muons.

  -Can take structured or flat CAFs.

  -Works on DUNE gpvm and needs it.
  
* python_flatCAF directory:

  -Plots truth and reco interaction vertex x from flat CAFs using uproot and pandas.

  -Can only take flat CAFs.

  -Does not work on DUNE gpvm and does not need it.

## Plotting structured CAFs

Make an input list of CAF files:
```
ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/*.root >> structured_caf_Picorun4.2.list
```
(or)

ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/*.root >> flat_caf_Picorun4.2.list

### Using a simple macro

* Go to directory:
  ```
  cd simple_macro
  ```
* Compile:
  ```
  ./compile_simple.sh
  ```
  (or)
  ```
  ./compile_simple_flat.sh
  ```
* Run the code:
  ```
  ./simple_plotter ../structured_caf_Picorun4.2.list output_structured_picorun4.2.root
  ```
  (or)
  ```
  ./simple_plotter_flat ../flat_caf_Picorun4.2.list output_flat_picorun4.2.root
  ```

* This should produce an output rootfile with the reco particle energy of muons.
* This uses `SRProxy.h` that activates only the branches you need and is quicker. Do not recommend directly using `StandardRecord.h`
* But, `TChain` breaks when using `SRProxy`. This is tackled in `CAFAna` in a better way.
* The difference between the two macros is how you link the CAF tree to `SRProxy`:

  Structured:`caf::SRProxy sr(caf_tree, "");` Flat:`caf::SRProxy sr(caf_tree, "rec");`
  
## Plotting flat CAFs

The python code unfortunately does not work on gpvm due to uproot and possibly other dependencies. Make sure you have the dependencies on your computer if you are planning on using it.

* Download just the python script in the python_flatCAF directory on your computer
* Download a flat CAF file on your computer directly from workshop indico or:
  ```
  scp <username>@dunegpvm07.fnal.gov:/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/PicoRun4.2_1E17_RHC.flow.00004.FLOW_CAF.flat.root .
  ```
* Run the code:
  ```
  python3 plot_flat_caf.py PicoRun4.2_1E17_RHC.flow.00004.FLOW_CAF.flat.root
  ```
* You should have a file named `reco_vs_truth_ixn_vtx_x.png` now



