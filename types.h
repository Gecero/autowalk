#ifndef TYPES_H
#define TYPES_H
struct find {
	uint64_t offset;
	std::string type;
};

struct filter {
	char * pattern;
	const size_t length;
	std::string type;
};
#endif