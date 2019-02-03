help:
	@echo "arguments:"
	@echo "    make install      install/download all requirements"
	@echo "    make build        build the current code base"
	@exit
install:
	rm strict_fstream.hpp
	rm zstr.hpp
	wget -q -t 3 --waitretry 1 --no-dns-cache https://raw.githubusercontent.com/mateidavid/zstr/master/src/strict_fstream.hpp
	wget -q -t 3 --waitretry 1 --no-dns-cache https://raw.githubusercontent.com/mateidavid/zstr/master/src/zstr.hpp
	@exit
build:
	g++ -std=c++11 autowalk.cpp
	@exit
