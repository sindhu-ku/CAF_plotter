## File locations

Run used: Minirun3 (half of the events ~ 30k)

Inputs for ND_CAFMaker:

* MLreco h5 files: `/dune/data/users/skumara/Datafiles_2x2/MLreco_h5files/minirun3_30k/*.h5`

* GENIE contained: `/pnfs/dune/tape_backed/users/mkramer/prod/MiniRun3/MiniRun3_1E19_RHC.nu/GENIE/*.root`

* GENIE uncontained: `/pnfs/dune/tape_backed/users/mkramer/prod/MiniRun3/MiniRun3_1E19_RHC.rock/GENIE/*.root`

CAF files:

* Structured CAF rootfiles: `/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun3_30k/notruth/*.root`

* Flat CAF rootfiles: `/dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun3_30k/notruth/flat/*.root`

## Using a simple macro to plot from CAFs

* Clone this repository: `git clone https://github.com/sindhu-ku/CAF_plotter.git`
* Example macro: `simple_caf_plotter.cc`
* Setup environment and compile: `./compile_simple.sh`
* Make an input list of CAF files:
`ls /dune/data/users/skumara/Datafiles_2x2/CAF_rootfiles/minirun3_30k/notruth/*.root >> input.list`
* Run the code: `./simple_plotter input.list output_test.root`

## Using the "framework"

* Setup environment and compile: `./compile.sh`
* Run the code: `./plotter input.list output_test.root`

### Code breakdown:

