from pathlib import Path
from vunit import VUnit
from subprocess import call
import os


VU = VUnit.from_argv()


def merge_coverages(results):
    print("VU._output_path: " + VU._output_path)
    results.merge_coverage(file_name=VU._output_path + "/coverage_data")
    if VU.get_simulator_name() == "ghdl":
        try:
            os.mkdir(VU._output_path + "/coverage_report")
        except OSError:
            pass
        call(["gcovr", VU._output_path + "/coverage_data"])
        call(["gcovr", VU._output_path + "/coverage_data", "--html", "--html-details", "-o", VU._output_path + "/coverage_report/index.html"])


CORDIC_LIB = VU.add_library("cordic_lib")

BASE_PATH = Path(__file__).parent
CORDIC_LIB.add_source_files(BASE_PATH / "rtl" / "*.vhd")
CORDIC_LIB.add_source_files(BASE_PATH / "test" / "*.vhd")

CORDIC_LIB.set_sim_option("enable_coverage", True)
CORDIC_LIB.set_compile_option("enable_coverage", True)


VU.main(post_run=merge_coverages)
