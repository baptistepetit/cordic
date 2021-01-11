.PHONY: all test check clean build clean

repo_root_dir = $(realpath ..)

all: build

run: run_measure run_print

run_measure: build
	cd build && ./apps/measure-error-app

run_print: build
	cd build && ./apps/print-fixed-point-app

generate: build
	cd build && ./apps/generate-cordic-pipeline-app -p $(repo_root_dir)/hardware_design/rtl/cordic_pipeline.vhd

test: build
	cd build/lib/ && ./cordic-lib-test

check:
	cppcheck -I lib/include/ apps/include/ apps/src/ --enable=all --suppress=missingIncludeSystem

build:
	mkdir -p build && cd build && cmake .. && make

clean:
	rm -rf build
