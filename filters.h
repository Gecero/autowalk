#include "types.h"
#include <vector>
#ifndef FILTERS_H
#define FILTERS_H
std::vector<filter> filters {
	// compressed data - compression types
	{"\x78\x01", 2, "zlib no/low compressed data", ".dat"},
	{"\x78\x9C", 2, "zlib default compressed data", ".dat"},
	{"\x78\xDA", 2, "zlib best compressed data", ".dat"},
	{"\x1F\x8B", 2, "gzip compressed data", ".tar.gz"},
	{"\x42\x5A\x68\x31\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 100k", ".bz2"}, // i added the XXXkb info as extra information and, the more important thing, to
	{"\x42\x5A\x68\x32\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 200k", ".bz2"}, // confirm it's bzip using the following 6 bytes that are same for every archive
	{"\x42\x5A\x68\x33\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 300k", ".bz2"},
	{"\x42\x5A\x68\x34\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 400k", ".bz2"},
	{"\x42\x5A\x68\x35\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 500k", ".bz2"},
	{"\x42\x5A\x68\x36\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 600k", ".bz2"},
	{"\x42\x5A\x68\x37\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 700k", ".bz2"},
	{"\x42\x5A\x68\x38\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 800k", ".bz2"},
	{"\x42\x5A\x68\x39\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 900k", ".bz2"},
	
	// compressed data - compression data formats
	{"\x52\x61\x72\x21\x1A\x07\x00", 7, "rar archive", ".rar"},
	{"\x52\x61\x72\x21\x1A\x07\x01\x00", 8, "rar5 archive", ".rar"},
	{"\x37\x7A\xBC\xAF\x27\x1C", 6, "7z archive", ".7z"},
	{"\x50\x4B\x03\x04", 4, "zip archive", ".zip"},
	{"\x50\x4B\x05\x06", 4, "empty zip archive", ".zip"},
	{"\x50\x4B\x07\x08", 4, "spanned zip packed", ".zip"},
	
	// multimedia formats - images
	{"GIF87a", 6, "gif image", ".gif"},
	{"GIF89a", 6, "gif image", ".gif"},
	{"\xFF\xD8", 2, "jpeg image", ".jpg"},
	{"\x42\x4D", 2, "windows bitmap image", ".bmp"},
	{"\x89\x50\x4e\x47\x0d\x0a\x1a\x0a", 8, "png image", ".png"},
	
	// multimedia formats - video
	{"\x1A\x45\xDF\xA3", 4, "mkv video", ".mkv"},
	{"\x00\x00\x00\x18\x66\x74\x79\x70\x6D\x70\x34\x32", 12, "mp4 video", ".mp4"},
	{"\x46\x4C\x56", 3, "flv video", ".flv"},
	
	// multimedia formats - audio
	{"\xFF\xFB", 2, "mp3 audio", ".mp3"},
	{"\x49\x44\x33", 2, "mp3 audio", ".mp3"},
	{"\x4D\x54\x68\x64", 4, "midi audio", ".midi"},
	{"\x4F\x67\x67\x53", 4, "ogg data container", ".ogg"},
	{"\x66\x4C\x61\x43", 4, "flac audio", ".flac"},

	// binary formats
	{"\x7F\x45\x4c\x46\x01", 5, "ELF based 32-bit executable", ""},
	{"\x7F\x45\x4c\x46\x02", 5, "ELF based 64-bit executable", ""},
	{"\xFE\xED\xFA\xCE", 4, "Mach-O based 32-bit executable", ""},
	{"\xFE\xED\xFA\xCF", 4, "Mach-O based 64-bit executable", ""}
	
	
	
};
#endif
