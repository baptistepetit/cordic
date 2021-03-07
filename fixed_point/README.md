# CORDIC Cos/Sin Fixed Point Implementation

This standalone cpp library implements the CORDIC algorithm to calculate cos and sin functions with fixed point arithmetic.

Three applications are also provided. The first app is using the library and estimating error to standard cpp implementation for several data width. The second one prints hexadecimal representation of several constants used in the algorithm. The last app generates the vhdl code of the hardware design cordic pipeline [here](../hardware_design/rtl/cordic_pipeline.vhd).

Implementation and basic testing related to CORDIC is in the `lib/` folder as a header only library.

Application headers and source files are stored the `apps/` folder.


## Prerequisistes

The following software is required on your machine:

* CMake >= 3.9
* gcc >= 6.1
* googletest (tested with official ubuntu debian packages version 1.10.0-2)
* google-mock(tested with official ubuntu debian packages version 1.10.0-2)

Optional:
* cppcheck (tested with official ubuntu debian package version 1.90-4build1)

**Note:** This CMake configuration was tested under Ubuntu 20.04. The application compilation should pose no problems on any platforms. However, the unit test configuration in CMake is relying on the way GoogleTest is setup on your computer and may need modifications to run on your platform.


## How to run


### Build

To get ready simply run from this folder:

```bash
make -j
```

### Running the apps

To run all the apps, in this folder, run:
```bash
make run
```

To run the app measuring cordic error based on cmath, run:
```bash
make run_measure
```

To run the app printing fixed point constants used in implementation, run:
```bash
make run_print
```

To re-generate vhdl code for the cordic pipeline implementation in hardware_design, run:
```bash
make generate
```

### Running the unit tests

In this folder, run:
```bash
make test
```

### Running cppcheck

If you installed cppcheck on your computer you can analyse the source files here by running the command in this folder:
```bash
make check
```
