.PHONY: all test clean build clean

all: build

run: build
	cd build && ./app/fixed-point-cordic

test: build
	cd build/lib/ && ./cordic-lib-test

build:
	mkdir -p build && cd build && cmake .. && make

clean:
	rm -rf build
