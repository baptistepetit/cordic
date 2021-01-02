.PHONY: all test check clean build clean

all: build

run: build
	cd build && ./app/fixed-point-cordic

test: build
	cd build/lib/ && ./cordic-lib-test

check:
	cppcheck -I lib/include/ app/include/ app/src/ --enable=all --suppress=missingIncludeSystem

build:
	mkdir -p build && cd build && cmake .. && make

clean:
	rm -rf build
