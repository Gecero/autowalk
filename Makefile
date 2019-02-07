help:
	@echo "arguments:"
	@echo "    make install      install/download all requirements"
	@echo "    make build        build the current code base"
	@exit
install:
	@exit
build:
	g++ -std=c++11 -Wall -Wpedantic -O3 autowalk.cpp
	@exit
