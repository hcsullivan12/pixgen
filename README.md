# Overview
*pixgen* is a tool used for generating various particle interactions inside a liquid argon time projection chamber (LArTPC). This tool uses a modified version of [larsim](https://cdcvs.fnal.gov/redmine/projects/larsim) for the event generation and simulation. The modifications were intended to allow for a more detector independent simulation by introducing the *DetectorGeometry* service. 

## Setup and build
Assuming one has read access to [dunetpc](https://cdcvs.fnal.gov/redmine/projects/dunetpc)
```
$ export DUNEDEVDIR=/path/to/my/project
$ source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
$ version=v08_22_00
$ export LOCAL_DUNE=${DUNEDEVDIR}
$ cd ${DUNEDEVDIR}
$ mrb newDev -v ${version} -q e17:prof -f
$ setup dunetpc ${version} -q e17:prof
$ source localProducts_larsoft_v08_22_00_e17_prof/setup
$ cd srcs
$ mrb newProduct pixgen
$ mv pixgen pixgen_temp
$ git clone https://github.com/hcsullivan12/pixgen.git
$ rm -rf pixgen_temp
$ source ../localProducts_larsoft_v08_22_00_e17_prof/setup
$ mrbsetenv
$ mrb i -j4
```
## Geometry
Instead of using the built-in *Geometry* service, a new *DetectorGeometry* service was introduced that makes no reference to wires or pixels. The interface (pixgen/Geometry/DetectorGeometry.h) contains the minimal amount of information needed for the generation and simulation. Unfortunately, this means that if you want to use other tools in the LArSoft package, you may need to port the code into *pixgen* and make sure *DetectorGeometryService* is used.

In principle, any geometry or readout scheme (wires/pixels) could be used, provided there is an associated GDML in pixgen/Geometry/GDML/. The specific detector implentation is left to the subclasses, e.g. *PixGenGeometry* in pixgen/Geometry/.

## Simulation
Single muon, 10 events
```
lar -c prodsingle_muon_500_1000MeV.fcl -n 10
```

Nuclear decay, 10 events
```
lar -c prodndk.fcl -n 10
```

Argon-39, 10 events
```
lar -c pixgen_radiologicalgen.fcl -n 10
```

Neutrinos from DUNE flux files, 10 events
```
lar -c prodgenie.fcl -n 10
```
(Note if you get a segmentation fault, try running kinit first.)
