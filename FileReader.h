#include <string>

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

class FileReader
{
	std::string filename;
public:
	FileReader(const char * filename);
	~FileReader();
	
	void read();
};

#endif
