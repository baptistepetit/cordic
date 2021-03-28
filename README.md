# A naive CORDIC implementation

[![main_ci](https://img.shields.io/github/workflow/status/baptistepetit/cordic/Main%20Branch%20Event)](https://github.com/baptistepetit/cordic/actions?query=workflow%3A%22Main+Branch+Event%22)
[![live_demo](https://img.shields.io/badge/demo-live-brightgreen)](https://baptistepetit.github.io/cordic/)
[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)
[![License](https://img.shields.io/github/license/baptistepetit/cordic)](LICENSE)


This repository aims at taking a classical computer science algorithm, the **CO**ordinate **R**otation **DI**gital **C**omputer, and refine it step by step into an FPGA design in VHDL.

The underlying goal of this project is to experiment with a set of good practices in design that can be scalable to bigger projects. This is why each step of the project was built with CI integration in mind, even the hardware design part.

## Proof of Concept

Stored in the `poc/` folder, this is the first step of this implementation journey. A simple static webpage with JavaScript code implementing the algorithm in a naive way, written to get to know better the algorithm.

The [live demo webpage](https://baptistepetit.github.io/cordic/) for this project is based on this code.

More details in its [README](poc/README.md).

## Fixed Point Refinement

Stored in the `fixed_point/` folder, this is the second step of the work. An application in C++ implementing the CORDIC algorithm with fixed point arithmetic to get a fist estimate of bit precision needed and uncover potential hardware implementation problems.

More details in its [README](fixed_point/README.md).

## Hardware Implementation

Stored in the `hardware_design/` folder, this step of the process consists in implementing in hardware the algorithm using the model elaborated at the previous step as a golden reference. Here VHDL is used to describe the implementation, while a combination of ghdl and VUnit allows its automated testing.

More details in its [README](hardware_design/README.md).

## Lesson Learnt (... so far)

 * Modelling basic fixed point data representation and arithmetic took much more time than expected: in the future a dedicated library such as SystemC seems worth using for hardware modelling, even for a small scale project such as this one.

 * Test driven development with a CI environment is possible in hardware design, and even easy to setup once the correct tools are installed.

## Further Improvements

There are several ways to improve this project further, time allowing:
 * A first way would be to develop a wrapper to the hardware design to allow it connect to standard IPs, for instance through AXI4Stream, and use this occasion to experiment with system testing using UVVM and ghdl in the CI environment.
 * An other way would be to use more automated tools in the project, for instance to report the quality of the codebase or generate versions.
