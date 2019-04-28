#include <iostream>
#include <fstream>
#include <cstring> // for strlen
#include <vector>
#include <numeric> // for std::accumulate
#include <iomanip> // for std::setw and std::setfill
#include "types.h"
#include "filters.h"
#include "simplyzip.hpp"
#include <cmath> // for pow
#include <unistd.h> // for getopt
#include <chrono> // for the "estimated time left: *" text

const int findReportLength = 65;

// TO-DO:
// - more filters
// - confirmed windows and mac support
// - a better gui for finds like the one from binwalk
// - better descriptions for filters
// - make the code more self explainationary
// - eventually c support
// - documentation

std::vector<find> finds;

std::string readFile(const std::string& fname);
void safeFile(std::string name, std::string contents, int offset, int size);
char getChar(const char * text, uint64_t index);
void reportFind(find fnd);
void debugPrint(bool print, std::string text);
void printHelp();
void handleData(int findNumber, std::string & data, int offset, int size);
void extractData(std::string & content);
bool encoding_match(char * text, size_t len, encoding enc);
int main(int argc, char * argv[]);

// thanks to @Jackojc#2309 for helping me out with file reading - btw: it's a modified version of his code
// this function loads a whole file into a single string
std::string readFile(const std::string& fname) {
    std::ifstream is(fname, std::ios::binary | std::ios::ate);

    // If file does not exist, return empty string and error.
    if (!is.is_open()) {
        return "\0";
    }

    // Create and fill buffer.
    size_t size = is.tellg();
    std::string str(size, '\0');
    is.seekg(0);
    is.read(&str[0], size);

    // Cleanup.
    is.close();

    // Return string and success.
    return str;
}

// save data from a specific offset to a file
void safeFile(std::string name, std::string contents, int offset, int size) {
	std::string content = contents.substr(offset, size);
	
	std::ofstream ofs;
	ofs.open(name, std::ios::out | std::ios::binary | std::ios::trunc);
	if(ofs.is_open())
		ofs << content;
	else
		return;
	ofs.close();
}

// this function is there to prevent an out_of_range exception
char getChar(const char * text, uint64_t index) {
	if(index > strlen(text))
		return '\0';
	else
		return text[index];
}

// output a find
void reportFind(find fnd) {
	std::string tmp = "                                       ";
	if(fnd.type.size() > findReportLength - 15) {
		std::cerr << "find type text too long (>" << findReportLength - 15 << ")" << std::endl;
		exit(1);
	}
	int index = (findReportLength - 15) - fnd.type.length();
	//std::string idk = tmp.substr(0, index) + fnd.type + "     " + "0x" + std::hex << std::setw(8) << std::setfill('0') << fnd.offset << std::endl;
	std::cout << tmp.substr(0, index) << fnd.type << "  at " << "0x" << std::hex << std::setw(8) << std::setfill('0') << fnd.offset << std::endl;
	
	//auto written = std::snprintf(&tmp[0], tmp.size(), "%c", fnd.);
	//tmp.resize(written);			
	
}

// this function is here to prevent an unreadable code full of if's
void debugPrint(bool print, std::string text) {
	if(print == true)
		std::cout << text << std::endl;
}

// print help text and then exit(0)
void printHelp() {
	std::cout << "autowalk help" << std::endl;
	std::cout << "Usage: autowalk [OPTIONS] [FILE]" << std::endl;
	std::cout << "  -h                         write this help message" << std::endl;
	std::cout << "  -x                         do not extract the data after file parsing" << std::endl;
	std::cout << "  -q                         be quiet and do not write debug/info output" << std::endl;
	std::cout << "Exit status:" << std::endl;
	std::cout << " 0\tif\tOK" << std::endl;
	std::cout << " 1\tif\tproblems" << std::endl;
	exit(0);
}

// an extra routine for more specific data handling
void handleData(int findNumber, std::string & data, int offset, int size) {
	// zlib decompression
	if(finds[findNumber].type.substr(0, 4) == "zlib") {
		std::string decompressed = decompress_deflate(data.substr(offset, size));
		safeFile("autowalk_found" + std::to_string(findNumber) + "_decompressed" + ".dat", decompressed, 0, decompressed.length());
		return;
	}
	
	// gzip decompression
	if(finds[findNumber].type.substr(0, 4) == "gzip") {
		std::string decompressed = decompress_gzip(data.substr(offset, size));
		safeFile("autowalk_found" + std::to_string(findNumber) + "_decompressed" + ".dat", decompressed, 0, decompressed.length());
		return;
	}
}

// extract the data and then 
void extractData(std::string & content) {
	if(finds.size() == 1) {
		safeFile("autowalk_found0" + finds[0].fileEnding, content, finds[0].offset, content.size());
		safeFile("autowalk_found0.nfo", finds[0].type, 0, finds[0].type.length());
		
		handleData(0, content, finds[0].offset, content.size());
	} else if(finds.size() > 1) {
		for(int i = 0; i < finds.size(); i++) {
			int size = (i == finds.size() - 1) ? (content.length() - finds[i].offset) : finds[i+1].offset - finds[i].offset;
			safeFile("autowalk_found" + std::to_string(i) + finds[i].fileEnding, content, finds[i].offset, size);
			safeFile("autowalk_found" + std::to_string(i) + ".nfo", finds[i].type, 0, finds[i].type.length());		
			
			handleData(i, content, finds[i].offset, size);
		}
	}
}

bool encoding_match(char * text, size_t len, encoding enc) {
	signed int index;
	for(uint64_t i = 0; i < len; i++) {
		
		// if we aren't using a whitelist
		if(enc.neededChars != nullptr) {
			index = -1;
			
			for(uint64_t j = 0; j < enc.neededCharsLength; j++) {
				if(enc.neededChars[j] == text[i]) {
					index = j;
					break;
				}
			}
			// index didn't changed - none of the needed chars were found
			if(index == -1)
				return false;
		}
		
		// if we aren't using a blacklist
		if(enc.disallowedChars != nullptr) {
			index = -1;
			for(uint64_t j = 0; j < enc.disallowedCharsLength; j++) {
				if(enc.disallowedChars[j] == text[i]) {
					index = j;
					break;
				}
			}
			// index changed - a disallowed char was found
			if(index != -1)
				return false;
		}
		
	}
	return true;
}

int main(int argc, char * argv[]) {
	// BASIC FILE READING AND ARGUMENT PARSING //
	
	// running this code without this check and without arguments will result in a segmentation fault
	if(argc <= 1)
		printHelp();
	
	std::string file;
	bool extract = true;
	bool quiet = false;
	
	int c;
	while((c = getopt(argc, argv, "hqx")) != -1) {
		switch(c) {
		case 'x':
			extract = false;
			break;
		case 'q':
			quiet = true;
			break;
		case 'h':
			printHelp();
			break;
		case '?':
			printHelp();
			break;
		default:
			printHelp();
			break;
		}
	}
	
	file = argv[optind];
	if(!std::fstream(file.c_str()).good()) {
		std::cerr << "could not open/find/read file." << std::endl;
		exit(1);
	}
	
	debugPrint(!quiet, "1/4    opening file..");
	std::string content = readFile(file);
	size_t length = content.size();
	size_t progressInterval = pow(length, 0.75);
	
	// BASIC FILE CONTENT PARSING //
	
	std::chrono::high_resolution_clock::time_point timeSync1 = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point timeSync2 = std::chrono::high_resolution_clock::now();
	
	debugPrint(!quiet, "2/4    extra information gathering..");
	for(encoding enc : encodings) {
		debugPrint(!quiet, "       file is " + std::string(encoding_match(const_cast<char *>(content.c_str()), length, enc) == true ? "probably " : "probably not ") + enc.description);
	}
	// do this check for every char in the file
	for(uint64_t i = 0; i < length; i++) {
		if(i % progressInterval == 0 && quiet == false) {
			timeSync2 = std::chrono::high_resolution_clock::now();
			double timePerLoop = (std::chrono::duration<double>(timeSync2 - timeSync1).count() / (double)progressInterval);
			std::string tmp(43, '\0');
			auto written = std::snprintf(&tmp[0], tmp.size(), "%06.2f%%, estimated time left: %09.2f", ((double)i / (double)length)*100.0f, timePerLoop*(double)(length-i));
			tmp.resize(written);			
			debugPrint(!quiet, "3/4    parsing file..  (" + tmp + "s)");
			timeSync1 = std::chrono::high_resolution_clock::now();
			// fun fact: using this time stopping method if the files get larger the "estimated time left" amounts get more precise
		}
		// check if any of the filters matches
		for(filter f : filters) {
			// a array to check wich chars of the text are matching the chars of the filter
			bool applies[f.length];
			for(int j = 0; j < f.length; j++) {
				applies[j] = false;
				// if the char is equal to the char of the filter
				// set the associated value in the "applies" array
				if(getChar(content.c_str(), i+j) == f.pattern[j])
					applies[j] = true;
			}
			
			// if all booleans added together (true = +1, false = same) equals the length of the filter
			// or in other words, the filter applies, add the filter with offset to the "finds" vector
			if(std::accumulate(applies, applies + f.length, 0) == f.length)
				finds.push_back({i, f.type, f.fileEnding});
			
		}
	}
	
	if(quiet == false) {
		for(find f : finds)
			reportFind(f);
	}
	
	if(extract == true && finds.size() > 0) {
		debugPrint(!quiet, "4/4    extracting the data into files..");
		extractData(content);
	} else if (extract == true) {
		debugPrint(!quiet, "4/4    there is no data to extract");
	} else {
		debugPrint(!quiet, "4/4    skipped data extraction");
	}
	
}
