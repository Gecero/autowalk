#ifndef TYPES_H
#define TYPES_H
#include <string>
struct find {
	uint64_t offset;
	std::string type;
	std::string fileEnding;
};

struct filter {
	std::string fileEnding;
	unsigned int offset;
	char * pattern;
	const size_t length;
	std::string type;
};
struct encoding {
	std::string description;
	char * neededChars;
	size_t neededCharsLength;
	char * disallowedChars;
	size_t disallowedCharsLength;
};
#endif
