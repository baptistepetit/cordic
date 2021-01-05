# A naive CORDIC implementation

[![main_ci](https://img.shields.io/github/workflow/status/baptistepetit/cordic/Main%20Branch%20Event)](https://github.com/baptistepetit/cordic/actions?query=workflow%3A%22Main+Branch+Event%22)
[![Commitizen friendly](https://img.shields.io/badge/commitizen-friendly-brightgreen.svg)](http://commitizen.github.io/cz-cli/)
[![License](https://img.shields.io/github/license/baptistepetit/cordic)](LICENSE)


This repository aims at taking a classical computer science algorithm, the **CO**ordinate **R**otation **DI**gital **C**omputer, and refine it step by step into an FPGA design in VHDL.


## Proof of Concept

Stored in the `poc/` folder, this is the first step of this implementation journey. A simple static webpage with JavaScript code implementing the algorithm in a naive way, written to get to know better the algorithm.

More details in its [README](poc/README.md).

## Fixed Point Refinement

Stored in the `fixed_point/` folder, this is the second step of the work. An application in C++ implementing the CORDIC algorithm with fixed point arithmetic to get a fist estimate of bit precision needed and uncover potential hardware implementation problems.

More details in its [README](fixed_point/README.md).
