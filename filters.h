#include "types.h"
#include <vector>
#ifndef FILTERS_H
#define FILTERS_H
std::vector<filter> filters {
	// compressed data - compression types
	{"\x78\x01", 2, "application/x-compress\t\taka. zlib no/low compression\t\t"},
	{"\x78\x9C", 2, "application/x-compress\t\taka. zlib default compression\t\t"},
	{"\x78\xDA", 2, "application/x-compress\t\taka. zlib best compression\t\t"},
	{"\x1F\x8B", 2, "application/gzip\t\taka. gzip compression\t\t\t"},
	// i added the XXXkb info as extra information and, the more important thing, to 
	// confirm it's bzip because of the following 6 bytes that are same for every archive
	{"\x42\x5A\x68\x31\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 100k"},
	{"\x42\x5A\x68\x32\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 200k"},
	{"\x42\x5A\x68\x33\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 300k"},
	{"\x42\x5A\x68\x34\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 400k"},
	{"\x42\x5A\x68\x35\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 500k"},
	{"\x42\x5A\x68\x36\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 600k"},
	{"\x42\x5A\x68\x37\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 700k"},
	{"\x42\x5A\x68\x38\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 800k"},
	{"\x42\x5A\x68\x39\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 900k"},
	{"\x42\x5A\x30\x31\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 100k"},
	{"\x42\x5A\x30\x32\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 200k"},
	{"\x42\x5A\x30\x33\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 300k"},
	{"\x42\x5A\x30\x34\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 400k"},
	{"\x42\x5A\x30\x35\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 500k"},
	{"\x42\x5A\x30\x36\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 600k"},
	{"\x42\x5A\x30\x37\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 700k"},
	{"\x42\x5A\x30\x38\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 800k"},
	{"\x42\x5A\x30\x39\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip1 compression, block size = 900k"},
	
	// compressed data - compression data formats
	{"\x52\x61\x72\x21\x1A\x07\x00", 7, "application/x-rar-compressed\t\taka. rar packed data\t\t"},
	{"\x52\x61\x72\x21\x1A\x07\x01\x00", 8, "application/x-rar-compressed\t\taka. rar5 packed data\t\t"},
	{"\x37\x7A\xBC\xAF\x27\x1C", 6, "application/x-7z-compressed\t\taka. 7z packed data\t\t"}
};
#endif