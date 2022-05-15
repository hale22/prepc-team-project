.PHONY: all build rebuild check clean

all: clean check build

clean:
	rm -rf build

build:
	./build.sh

rebuild: clean build

check:
	./run_linters.sh