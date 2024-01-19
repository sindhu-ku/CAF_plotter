## CAF structure

A quick overview of the CAF structure can be found [here](https://drive.google.com/file/d/1-jdDoc89lTVQGPX4RDChJjJKRoMrtY84/view?usp=sharing).
If you want to know more about all the variables in the different branches, see the Doxygen page for the `StandardRecord` objects defined in [here](https://dune.github.io/duneanaobj/classcaf_1_1StandardRecord.html)

## How to make CAFs

Run used: Picorun 4.2

MLreco inputs for [`ND_CAFMaker`](https://github.com/DUNE/ND_CAFMaker) that produces the CAF files:

* MLreco h5 files: `/dune/data/users/drielsma/minirun4/*.h5`
* An example cfg file to produce CAFs: `/dune/app/users/skumara/CAFs/ND_CAFMaker/cfg/ndcafmakerjob_picorun.fcl`

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
  git clone https://github.com/sindhu-ku/CAF_plotter.git --branch v2.0.0 --depth 1
  ```
* Set up environment (same as `ND_CAFMaker`):
  ```
  source setup.sh
  ```

## What is in this repository (Version used for tutorial v2.0.0)


* A C++ macro that plots some histograms from a list of CAF files.

  -Can take structured or flat CAFs.

  -Works on DUNE gpvm and needs it.
  
* A python script that plots some histograms from a root file or a list of root files.

  -Can only take flat CAFs.

  -Does not work on DUNE gpvm and does not need it.

## C++ using SRProxy for structured and flat CAFs

Make an input list of CAF files:
```
ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/*.root >> structured_caf_Picorun4.2.list
```
```
ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/*.root >> flat_caf_Picorun4.2.list
```

* Compile:
  ```
  ./compile_simple.sh
  ```
* Run the code:
  ```
  ./simple_plotter structured_caf_Picorun4.2.list output_structured_picorun4.2.root structured
  ```
  (or)
  ```
  ./simple_plotter_flat flat_caf_Picorun4.2.list output_flat_picorun4.2.root flat
  ```

* This should produce output rootfiles with histograms.
* This uses `SRProxy.h` that activates only the branches you need and is quicker. Do not recommend directly using `StandardRecord.h`. Even faster if you use flat CAFs (about twice!).
* But, `TChain` breaks when using `SRProxy`, so it loops over files. This is tackled in `CAFAna` in a better way.
* There is a difference in how you link the CAF tree to `SRProxy` for structured and flat CAFs:

  Structured:`caf::SRProxy sr(caf_tree, "");` Flat:`caf::SRProxy sr(caf_tree, "rec");`
  
## Python for flat CAFs

The python code unfortunately does not work on gpvm due to uproot and possibly other dependencies. Make sure you have the dependencies on your computer if you are planning on using it.

* Download just the python script in the python_flatCAF directory on your computer
* Download a flat CAF file on your computer directly from workshop indico or make a list of flat CAF files:
  ```
  scp -r <username>@dunegpvm07.fnal.gov:/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/Picorun4.2/flat/ .
  ```
  ```
  ls flat/* >> PicoRun4.2_flatCAF_list
  ```
* Run the code:
  ```
  python3 plot_flat_caf.py PicoRun4.2_1E17_RHC.flow.00004.FLOW_CAF.flat.root
  ```
  (or)
  ```
  python3 plot_flat_caf.py PicoRun4.2_flatCAF_list
  ```
* It should show some histograms



