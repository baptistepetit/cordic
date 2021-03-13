# CORDIC Cos/Sin Hardware Design

This hardware design aims at implementing the CORDIC algorithm to calculate cosine and sine. It is described at an RTL level using a hardware description language. Here VHDL is used to describe the hardware.

The `rtl` folder contains all hardware design sources. A tcl script is provided to generate a Vivado project from the sources in the rtl folder.

The `test` folder contains testbenches for each design source. Those tesbenches are using the VUnit test framework, which allows for easy CI integration.

**Note:** [This app](../fixed_point/apps/src/generate_cordic_pipeline.cpp) of the fixed_point folder was used for generating the `cordic_pipeline.vhd` file. A code generation approach was chosen over using the VHDL `for loop` construct to easily generate CORDIC constants based on the pipeline size requested.

## Prerequisistes

### Design elaboration

As this design is completely standalone, it can be used in any VHDL capable design suite like Xilinx Vivado or Intel Quartus Prime.

### Running the testbenches

Although to run the testbenches any [VUnit](https://vunit.github.io/) compatible VHDL Simulator can be used, this project was built with using [GHDL](https://ghdl.readthedocs.io/en/latest/about.html) in mind. In addition, using GHDL in its gcc backend configuration allows creating a gcov testbenches coverage report.

#### Natively with VUnit and GHDL

The VUnit testing framework can be simply installed with the command:

```bash
pip3 install vunit_hdl
```

GHDL can be installed following [these instructions](https://github.com/ghdl/ghdl#getting-ghdl) from the official project.

**Notes:**
 * Avoid using official Ubuntu/Debian packages of GHDL older than version 1.0.0, as they may ship with the openieee vhdl libraries instead of the ieee vhdl libraries. Openieee libraries are not suitable for use in this project.
 * GHDL needs to be more recent than version 0.33 for VUnit to work correctly with it.

#### Using a docker image

If you are not willing to install dependencies on your computers, this docker image provided by the GHDL project can also be used: [ghdl/vunit:gcc](https://hub.docker.com/r/ghdl/vunit).

## How to run

### Generating the Vivado Project

To get ready simply run from this folder:

```bash
vivado -source generate_project.tcl
```

**Note:** You need to source Vivado settings in your environment first, on linux it can be done by sourcing the `settings64.sh` file.

### Running the testbenches with VUnit and GHDL

In this folder, run:
```bash
python3 run.py -o build
```

**Note:** Values used in testbenches have been pre-computed using [this app](../fixed_point/apps/src/print_fixed_point.cpp) of the fixed_point folder.
