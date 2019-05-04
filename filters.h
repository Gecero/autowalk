#include "types.h"
#include <vector>
#ifndef FILTERS_H
#define FILTERS_H
std::vector<filter> filters {
	// archives
	{".rar", 0, "\x52\x61\x72\x21\x1A\x07\x00", 7, "rar archive"},
	{".rar", 0, "\x52\x61\x72\x21\x1A\x07\x01\x00", 8, "rar5 archive"},
	{".7z", 0, "\x37\x7A\xBC\xAF\x27\x1C", 6, "7z archive"},
	{".zip", 0, "\x50\x4B\x03\x04", 4, "zip archive"},
	{".zip", 0, "\x50\x4B\x05\x06", 4, "zip archive (empty)"},
	{".zip", 0, "\x50\x4B\x07\x08", 4, "zip archive (spanned)"},
	{".lha", 2, "\x2D\x6C\x68", 3, "lha archive"},
	{".xz", 0, "\xFD\x37\x7A\x58\x5A\x00", 6, "xz archive"},
	
	// compressed data
	{".dat", 0, "\x78\x01", 2, "zlib no/low compressed data"},
	{".dat", 0, "\x78\x9C", 2, "zlib default compressed data"},
	{".dat", 0, "\x78\xDA", 2, "zlib best compressed data"},
	{".gz", 0, "\x1F\x8B\x08", 2, "gzip compressed data"},
	{".bz2", 0, "\x42\x5A\x68\x31\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 100k"}, // i added the XXXkb info as extra information and, the more important thing, to
	{".bz2", 0, "\x42\x5A\x68\x32\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 200k"}, // confirm it's bzip using the following 6 bytes that are same for every archive
	{".bz2", 0, "\x42\x5A\x68\x33\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 300k"},
	{".bz2", 0, "\x42\x5A\x68\x34\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 400k"},
	{".bz2", 0, "\x42\x5A\x68\x35\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 500k"},
	{".bz2", 0, "\x42\x5A\x68\x36\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 600k"},
	{".bz2", 0, "\x42\x5A\x68\x37\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 700k"},
	{".bz2", 0, "\x42\x5A\x68\x38\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 800k"},
	{".bz2", 0, "\x42\x5A\x68\x39\x31\x41\x59\x26\x53\x59", 10, "bzip2 compressed data, block size = 900k"},
	
	// misc. data containers
	{".ogg", 0, "\x4F\x67\x67\x53", 4, "ogg data container"},
	{".img", 0, "\x00\x01\x00\x00\x53\x74\x61\x6E\x64\x61\x72\x64\x20\x4A\x65\x74\x20\x44\x42", 19, "img data container"},
	{".iso", 32769, "\x43\x44\x30\x30\x31", 5, "iso data container"},
	{".cab", 0, "\x49\x53\x63\x28", 4, "microsoft cabinet data container"},
	
	// documents (e.g. microsoft office stuff)
	{".fm", 0, "\x3C\x4D\x61\x6B\x65\x72\x46\x69\x6C\x65\x20", 11, "adobe framemaker document"},
	{".wk4", 0, "\x00\x00\x1A\x00\x02\x10\x04\x00\x00\x00\x00\x00", 12, "lotus 123 document"},
	{".wk3", 0, "\x00\x00\x1A\x00\x00\x10\x04\x00\x00\x00\x00\x00", 12, "lotus 123 document"},
	{".wk1", 0, "\x00\x00\x02\x00\x06\x04\x06\x00\x08\x00\x00\x00\x00\x00", 14, "lotus 123 document"},
	{".apr", 0, "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", 8, "lotus approach document"},
	{".nsf", 0, "\x1A\x00\x00\x04\x00\x00", 6, "lotus notes aka. ibm notes document"},
	{".org", 0, "\x41\x4F\x4C\x56\x4D\x31\x30\x30", 8, "lotus organizer document"},
	{".lwp", 0, "\x57\x6F\x72\x64\x50\x72\x6F", 7, "lotus wordpro document"},
	{".sam", 0, "\x5B\x50\x68\x6F\x6E\x65\x5D", 7, "lotus wordpro doucment"},
	{".doc", 0, "\x0D\x44\x4F\x43", 4, "microsoft word document"},
	{".rtf", 0, "\x7B\x5C\x72\x74\x66\x31", 6, "microsoft rich text document"},
	{".xls", 512, "\x09\x08\x10\x00\x00\x06\x05\x00", 9, "microsoft excel document"},
	{".xla", 0, "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", 8, "microsoft excel document"},
	{".ppt", 512, "\x00\x6E\x1E\xF0", 5, "microsoft powerpoint document"},
	{".pps", 0, "\xD0\xCF\x11\xE0\xA1\xB1\x1A\xE1", 8, "microsoft powerpoint document"},
	{".wks", 0, "\x0E\x57\x4B\x53", 4, "microsoft works document"},
	{".mny", 0, "\x00\x01\x00\x00\x4D\x53\x49\x53\x41\x4D\x20\x44\x61\x74\x61\x62\x61\x73\x65", 19, "microsoft money document"},
	{".xps", 0, "\x50\x4B\x03\x04", 4, "microsoft xps document"},
	{".pptx", 0, "\x50\x4B\x03\x04\x14\x00\x06\x00", 8, "openoffice document"},
	{".epub", 0, "\x50\x4B\x03\x04\x0A\x00\x02\x00", 8, "epub document"},
	{".pdf", 0, "\x25\x50\x44\x46", 4, "pdf document"},
	
	
	// video
	{".mkv", 0, "\x1A\x45\xDF\xA3", 4, "mkv video"},
	{".mp4", 0, "\x00\x00\x00\x18\x66\x74\x79\x70\x6D\x70\x34\x32", 12, "mp4 video"},
	{".flv", 0, "\x46\x4C\x56", 3, "flv video"},
	{".3gp", 0, "\x00\x00\x00\x14\x66\x74\x79\x70\x33\x67\x70", 11, "3gp video"},
	{".mp4", 0, "\x00\x00\x00\x14\x66\x74\x79\x70\x69\x73\x6F\x6D", 12, "mp4 video"},
	{".m4v", 0, "\x00\x00\x00\x18\x66\x74\x79\x70\x6D\x70\x34\x32", 12, "mp4 video"},
	{".mpeg", 0, "\x00\x00\x01\x00", 4, "mpeg video"},
	{".mov", 0, "\x00\x00\x00\x14\x66\x74\x79\x70\x71\x74\x20\x20", 12, "quicktime video"},
	{".webm", 0, "\x1A\x45\xDF\xA3", 4, "webm video"},
	{".avi", 0, "\x52\x49\x46\x46", 4, "avi video"},
	
	// audio
	{".mp3", 0, "\xFF\xFB", 2, "mp3 audio"},
	{".mp3", 0, "\x49\x44\x33", 2, "mp3 audio"},
	{".midi", 0, "\x4D\x54\x68\x64", 4, "midi audio"},
	{".flac", 0, "\x66\x4C\x61\x43", 4, "flac audio"},
	{".amr", 0, "\x23\x21\x41\x4D\x52", 5, "amr audio"},
	{".au", 0, "\x2E\x73\x6E\x64", 4, "au audio"},
	{".m4a", 0, "\x00\x00\x00\x20\x66\x74\x79\x70\x4D\x34\x41\x20", 12, "mp4 audio"},
	{".mp3", 0, "\x49\x44\x33", 3, "mp3 audio"},
	{".qcp", 0, "\x52\x49\x46\x46", 4, "qcelp audio"},
	{".ram", 0, "\x72\x74\x73\x70\x3A\x2F\x2F", 7, "realaudio audio"},
	{".ra", 0, "\x2E\x52\x4D\x46\x00\x00\x00\x12\x00", 9, "realaudio audio"},
	{".wav", 0, "\x52\x49\x46\x46", 4, "wavefont audio"},
	
	// image
	{".gif", 0, "GIF87a", 6, "gif image"},
	{".gif", 0, "GIF89a", 6, "gif image"},
	{".jpg", 0, "\xFF\xD8", 2, "jpeg image"},
	{".bmp", 0, "\x42\x4D", 2, "windows bitmap image"},
	{".png", 0, "\x89\x50\x4e\x47\x0d\x0a\x1a\x0a", 8, "png image"},
	{".bmp", 0, "\x42\x4D", 2, "microsoft windows bitmap image"},
	{".fits", 0, "\x53\x49\x4D\x50\x4C\x45\x20\x20\x3D\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x54", 30, "fits image"},
	{".jp2", 0, "\x00\x00\x00\x0C\x6A\x50\x20\x20\x0D\x0A", 10, "jpeg 2000 image"},
	{".tiff", 0, "\x49\x20\x49", 3, "tiff image"},
	{".psd", 0, "\x38\x42\x50\x53", 4, "adobe photoshop image"},
	{".ico", 0, "\x00\x00\x01\x00", 4, "microsoft icon image"},
	{".pcx", 512, "\x09\x08\x10\x00\x00\x06\x05\x00", 9, "pcx image"},
	{".webp", 0, "\x52\x49\x46\x46", 4, "webp image"},
	
	// executables
	{"", 0, "\x7F\x45\x4c\x46\x01", 5, "ELF based 32-bit executable"},
	{"", 0, "\x7F\x45\x4c\x46\x02", 5, "ELF based 64-bit executable"},
	{"", 0, "\xFE\xED\xFA\xCE", 4, "Mach-O based 32-bit executable"},
	{"", 0, "\xFE\xED\xFA\xCF", 4, "Mach-O based 64-bit executable"},
	{".exe", 0, "\x4D\x5A", 2, "microsoft windows executable"}, 
	{".class", 0, "\xCA\xFE\xBA\xBE", 4, "compiled java class"},
	{".jar", 0, "\x4A\x41\x52\x43\x53\x00", 6, "jar executable"},
	{".swf", 0, "\x43\x57\x53", 3, "shockwave flash executable"},
	
	// other
	{".cpl", 0, "\x4D\x5A", 2, "microsoft windows control panel data"},
	{".kmz", 0, "\x50\x4B\x03\x04", 4, "google earth coordinates"},
	{".chm", 0, "\x49\x54\x53\x46", 4, "compiled html file"},
	
};

std::vector<encoding> encodings {
	{"base64 encoded", "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ/+=\n", 66, nullptr, NULL},
	{"plain text", nullptr, NULL, "\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0B\x0C\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F", 32}
};
#endif
