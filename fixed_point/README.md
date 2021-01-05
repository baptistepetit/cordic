# CORDIC Cos/Sin Fixed Point Implementation

This standalone cpp library implements the CORDIC algorithm to calculate cos and sin functions with fixed point arithmetic. An application using the library and estimating error to standard cpp implementation for several data width is also provided.

Implementation and basic testing related to CORDIC is in the `lib/` folder as a header only library.

Application headers and source files are stored the `app/` folder.


## Prerequisistes

The following software is required on your machine:

* CMake >= 3.9
* gcc >= 6.1
* googletest (tested with official ubuntu debian package version 1.10.0-2)

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

In this folder, run:
```bash
make run
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
