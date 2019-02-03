#include <iostream>
#include <fstream>
#include <cstring> // for strlen
#include <vector>
#include <numeric> // for std::accumulate
#include <fstream>
#include "types.h"
#include "filters.h"

#include <unistd.h> // for getopt

const std::string AUTOWALK_VER = "0.2";

// TO-DO:
// - more filters
// - confirmed windows and mac support
// - a better gui for finds like the one from binwalk
// - better descriptions for filters
// - make the code more self explainationary
// - eventually c support
// - documentation
// - "--help" argument support

std::vector<find> finds;

// thanks to @Jackojc#2309 for helping me out with file reading - btw: it's a modified version of his code
// this function loads a whole file into a single string
std::string read_file(const std::string& fname) {
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
void safe_file(std::string name, std::string contents, int offset, int size) {
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
	std::cout << fnd.type << "\t at offset\t" << fnd.offset << std::endl;
}

// this function is here to prevent an unreadable code full of if's
void debugPrint(bool print, std::string text) {
	if(print == true)
		std::cout << text << std::endl;
}

// print help text and then exit(0)
void printHelp() {
	std::cout << "autowalk V" << AUTOWALK_VER << " help" << std::endl;
	std::cout << "Usage: autowalk [OPTIONS] [FILE]" << std::endl;
	std::cout << "  -h                         write this help message" << std::endl;
	std::cout << "  -x                         do not extract the data after file parsing" << std::endl;
	std::cout << "  -q                         be quiet and do not write debug/info output" << std::endl;
	std::cout << "Exit status:" << std::endl;
	std::cout << " 0\tif\tOK" << std::endl;
	std::cout << " 1\tif\tproblems" << std::endl;
	exit(0);
}

// extract the data and then 
void extractData(std::string & content) {
	if(finds.size() == 1) {
		safe_file("autowalk_found0.dat", content, finds[0].offset, content.size());
		safe_file("autowalk_found0.nfo", finds[0].type, 0, finds[0].type.length());
	} else if(finds.size() > 1) {
		for(int i = 0; i < finds.size(); i++) {
			int size = i == finds.size() - 1 ? (content.length() - finds[i].offset) : finds[i+1].offset - finds[i].offset;
			safe_file("autowalk_found" + std::to_string(i) + ".dat", content, finds[i].offset, size);
			safe_file("autowalk_found" + std::to_string(i) + ".nfo", finds[i].type, 0, finds[i].type.length());
		}
	}
}

int main(int argc, char * argv[]) {
	// BASIC FILE READING AND ARGUMENT PARSING //
	
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
	
	debugPrint(!quiet, "1/3\treading file...");
	std::string content = read_file(file);
	size_t length = content.size();
	
	// BASIC FILE CONTENT PARSING //
		
	// do this check for every char in the file
	debugPrint(!quiet, "2/3\tparsing file...");
	for(uint64_t i = 0; i < length; i++) {
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
				finds.push_back({i, std::string(f.type)});
			
		}
	}
	
	if(quiet == false) {
		for(find f : finds)
			reportFind(f);
	}
	
	if(extract == true) {
		debugPrint(!quiet, "3/3 extracting the data into files...");
		extractData(content);
	} else {
		debugPrint(!quiet, "3/3 skipped data extraction");
	}
	
}
