# Overview
*pixgen* is a tool used for generating various particle interactions inside a liquid argon time projection chamber (LArTPC). This tool uses a modified version of [larsim](https://cdcvs.fnal.gov/redmine/projects/larsim) for the event generation and simulation. The modifications were intended to allow for a more detector independent simulation by introducing the *DetectorGeometry* service. 

# Setup and build
Assuming one has read access to [dunetpc](https://cdcvs.fnal.gov/redmine/projects/dunetpc)
```
export DUNEDEVDIR=/path/to/my/project
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
version=v08_22_00
export LOCAL_DUNE=${DUNEDEVDIR}
cd ${DUNEDEVDIR}
mrb newDev -v ${version} -q e17:prof -f
setup dunetpc ${version} -q e17:prof
source localProducts_larsoft_v08_22_00_e17_prof/setup
cd srcs
mrb newProduct pixgen
mv pixgen pixgen_temp
git clone https://github.com/hcsullivan12/pixgen.git
rm -rf pixgen_temp
source localProducts_larsoft_v08_22_00_e17_prof/setup
mrbsetenv
cd $MRB_BUILDDIR
mrb i -j4
