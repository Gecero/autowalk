#include "types.h"
#include <vector>
#ifndef FILTERS_H
#define FILTERS_H
std::vector<filter> filters {
	// compressed data - compression types
	{"\x78\x01", 2, "application/x-compress\t\taka. zlib no/low compression\t\t", ".dat"},
	{"\x78\x9C", 2, "application/x-compress\t\taka. zlib default compression\t\t", ".dat"},
	{"\x78\xDA", 2, "application/x-compress\t\taka. zlib best compression\t\t", ".dat"},
	{"\x1F\x8B", 2, "application/gzip\t\taka. gzip compression\t\t\t", ".tar.gz"},
	{"\x42\x5A\x68\x31\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 100k", ".bz2"}, // i added the XXXkb info as extra information and, the more important thing, to
	{"\x42\x5A\x68\x32\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 200k", ".bz2"}, // confirm it's bzip using the following 6 bytes that are same for every archive
	{"\x42\x5A\x68\x33\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 300k", ".bz2"},
	{"\x42\x5A\x68\x34\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 400k", ".bz2"},
	{"\x42\x5A\x68\x35\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 500k", ".bz2"},
	{"\x42\x5A\x68\x36\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 600k", ".bz2"},
	{"\x42\x5A\x68\x37\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 700k", ".bz2"},
	{"\x42\x5A\x68\x38\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 800k", ".bz2"},
	{"\x42\x5A\x68\x39\x31\x41\x59\x26\x53\x59", 10, "application/x-bzip2\t\taka. bzip2 compression, block size = 900k", ".bz2"},
	
	// compressed data - compression data formats
	{"\x52\x61\x72\x21\x1A\x07\x00", 7, "application/x-rar-compressed\t\taka. rar packed data\t\t", ".rar"},
	{"\x52\x61\x72\x21\x1A\x07\x01\x00", 8, "application/x-rar-compressed\t\taka. rar5 packed data\t\t", ".rar"},
	{"\x37\x7A\xBC\xAF\x27\x1C", 6, "application/x-7z-compressed\t\taka. 7z packed data\t\t", ".7z"},
	{"\x50\x4B\x03\x04", 4, "application/zip aka. zip archive", ".zip"},
	{"\x50\x4B\x05\x06", 4, "application/zip aka. empty zip", ".zip"},
	{"\x50\x4B\x07\x08", 4, "application/zip aka. spanned zip packed", ".zip"},
	
	// multimedia formats - images
	{"GIF87a", 6, "image/gif\t\t\taka. gif image\t\t\t\t", ".gif"},
	{"GIF89a", 6, "image/gif\t\t\taka. gif image\t\t\t\t", ".gif"},
	{"\xFF\xD8", 2, "image/jpeg\t\t\taka. jpeg image\t\t\t\t", ".jpg"},
	{"\x42\x4D", 2, "image/x-ms-bmp\t\t\taka. windows bitmap encoded image\t", ".bmp"},
	{"\x89\x50\x4e\x47\x0d\x0a\x1a\x0a", 8, "image/png\t\t\taka. png image\t\t", ".png"},
	
	// multimedia formats - video
	{"\x1A\x45\xDF\xA3", 4, "video/x-matroska\t\taka. mkv video", ".mkv"},
	{"\x00\x00\x00\x18\x66\x74\x79\x70\x6D\x70\x34\x32", 12, "mp4 video", ".mp4"},
	{"\x46\x4C\x56", 3, "flv video", ".flv"},
	
	// multimedia formats - audio
	{"\xFF\xFB", 2, "audio/mpeg\t\t\taka. mp3 encoded audio\t\t\t", ".mp3"},
	{"\x49\x44\x33", 2, "audio/mpeg\t\t\taka. mp3 encoded audio\t\t\t", ".mp3"},
	{"\x4D\x54\x68\x64", 4, "midi audio\t\t\t\t\t", ".midi"},
	{"\x4F\x67\x67\x53", 4, "application/ogg\t\t\taka. ogg encoded data", ".ogg"},
	{"\x66\x4C\x61\x43", 4, "audio/flac\t\t\taka. flac audio\t\t", ".flac"},

	// binary formats
	{"\x7F\x45\x4c\x46\x01", 5, "ELF based 32-bit executable", ""},
	{"\x7F\x45\x4c\x46\x02", 5, "ELF based 64-bit executable", ""},
	{"\xFE\xED\xFA\xCE", 4, "Mach-O based 32-bit executable", ""},
	{"\xFE\xED\xFA\xCF", 4, "Mach-O based 64-bit executable", ""}
	
	
	
};
#endif
