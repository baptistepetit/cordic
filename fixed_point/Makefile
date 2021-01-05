.PHONY: all test check clean build clean

all: build

run: build
	cd build && ./apps/measure-error-app

test: build
	cd build/lib/ && ./cordic-lib-test

check:
	cppcheck -I lib/include/ apps/include/ apps/src/ --enable=all --suppress=missingIncludeSystem

build:
	mkdir -p build && cd build && cmake .. && make

clean:
	rm -rf build
