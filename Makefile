help:
	@echo "arguments:"
	@echo "    make setup        set up all dependencies (requires internet connection)"
	@echo "    make install      build autowalk and then make it accessible from the console"
	@echo "                      (eg. 'autowalk a.txt' instead of './a.out a.txt') and make the"
	@echo "                      autowalk man page globally accessible"
	@echo "    make build        build the current code base"
	@exit
setup:
	@rm -f simplyzip.hpp
	@rm -f simplyzip.hpp.1
	@sudo apt install wget
	@wget -q -t 5 --dns-timeout=5 --connect-timeout=5 --read-timeout=5 -w 5 --no-cache --no-cookies --no-check-certificate --tries=3 https://raw.githubusercontent.com/noelmartinon/mboxzilla/1a9a0d20a9c4b24943bfd7f100cf38afac03efe4/simplyzip.hpp -o simplyzip.hpp
	@rm -f simplyzip.hpp
	@mv -f simplyzip.hpp.1 simplyzip.hpp
	@exit
build:
	g++ -std=c++11 -Wall -Wpedantic -O3 autowalk.cpp -lz
	@exit
install:
	sudo g++ -std=c++11 -Wall -Wpedantic -O3 autowalk.cpp -lz -o /usr/bin/autowalk
	sudo apt install gzip
	sudo rm -f /usr/share/man/man1/autowalk.1.gz
	sudo gzip -kfc1 autowalk.man > autowalk.1.gz
	sudo mv -f autowalk.1.gz /usr/share/man/man1/autowalk.1.gz
	rm -f autowalk.1.gz