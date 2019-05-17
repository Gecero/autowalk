#include "types.h"
#include "filters.h"
#include "benchmark.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <thread>
#include <cmath>

#define MINIMALISTIC

#ifndef MINIMALISTIC
	#define __CLASS__ __PRETTY_FUNCTION__
	#define INFO time_now = std::time(nullptr); std::cout << std::put_time(std::localtime(&time_now), "[%d.%m.%y %OH:%OM:%OS]") << "  " << __FILE__ << "(" << __CLASS__ << ":" << __LINE__ << ")  INFO:  "
	#define PROBLEM time_now = std::time(nullptr); std::cout << std::put_time(std::localtime(&time_now), "[%d.%m.%y %OH:%OM:%OS]") << "  " << __FILE__ << "(" << __CLASS__ << ":" << __LINE__ << ")  PROBLEM:  "
#else
	#define INFO time_now = std::time(nullptr); std::cout << std::put_time(std::localtime(&time_now), "[%d.%m.%y %OH:%OM:%OS]") << "  INFO:  "
	#define PROBLEM time_now = std::time(nullptr); std::cout << std::put_time(std::localtime(&time_now), "[%d.%m.%y %OH:%OM:%OS]") <<"  PROBLEM:  "	
#endif

static std::time_t time_now = std::time(nullptr);

class tester {
private:
	struct entry { void (*function) (); };
	std::vector<entry> entries;

public:
	
	template<class T>
	void push_back() {
		entries.push_back({&T::main});
	}

	void do_tests() {
		for (int i = 0; i < entries.size(); i++) {
			entries[i].function();
		}
	}

};

class test {
public:
	test() {}
	
	static void main() {} // you have to override this
};

class patternOverride : public test {
private:
	// returns true if they are the same
	static bool txtcmp(char * first, int firstLen, char * second, int secondLen) {
		if (firstLen != secondLen)
			return false;
		for (int i = 0; i < firstLen; i++) {
			if (first[i] != second[i])
				return false;
		}
		return true;
	}
	
	static bool compare(filter a, filter b) {
		if (a.fileEnding != b.fileEnding)
			return false;
		if (a.length != b.length)
			return false;
		if (a.offset != b.offset)
			return false;
		if (txtcmp(a.pattern, a.length, b.pattern, b.length) == false)
			return false;
		if (a.type != b.type)
			return false;
		return true;
	}

public:
	patternOverride() {}
	
	static void main() {
		for (filter a : filters) {
			for (filter b : filters) {
				// if they are not exactly the same
				if (!compare(a, b)) {
					// if they have the same pattern and pattern length
					if (txtcmp(a.pattern, a.length, b.pattern, b.length) == true) {
						PROBLEM << "filter pattern duplicate found between '" << a.type << "'  and  '" << b.type << "'\n";
					}
				}
				
			}
		}
	}
};

class speedTest : public test {
private:
	static void doBenchmark() {
		int benchs = 50;
		clock_t begin;
		clock_t end;
		benchmark<double> benchmarker;
		
		benchmarker.setNumberOfEstimatedBenchmarks(benchs);
		for(int i = 0; i < benchs; i++)
			benchmarker.runFunctionBenchmark([](){system("autowalk -qx ./64Knullbytes");});
		
		std::cout.precision(8);
		INFO << "benchmark results:\n";
		INFO << "avg. time (should only be used for comparison):  " << benchmarker.getAverageBenchmarkTime() << std::endl;
	}
	
public:
	speedTest() { }
	
	static void main() {
		doBenchmark();
	}
};

int main(int argc, char * argv[]) {
	INFO << "Now running a collection of tests. estimated time:  about 15 seconds.\n";
	tester Tester;
	Tester.push_back<patternOverride>();
	Tester.push_back<speedTest>();
	Tester.do_tests();
	
	return 0;
}
