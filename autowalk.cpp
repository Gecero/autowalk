#include <iostream>
#include <fstream>
#include <cstring> // for strlen
#include <vector>
#include <numeric> // for std::accumulate
#include "types.h"
#include "filters.h"

// TO-DO:
// - add data extraction
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

// this function is there to prevent an out_of_range exception
char getChar(const char * text, uint64_t index) {
	if(index > strlen(text))
		return '\0';
	else
		return text[index];
}

void reportFind(find fnd) {
	std::cout << fnd.type << "\t at offset\t" << fnd.offset << std::endl;
}

int main(int argc, char * argv[]) {
	// BASIC FILE READING //
	
	std::string file = argv[1];
	std::string content = read_file(file);
	size_t length = content.size();
	
	// BASIC FILE CONTENT PARSING //
	
	// do this check for every char in the file
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
	
	for(find f : finds)
		reportFind(f);
}