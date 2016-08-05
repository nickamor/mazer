#include <string>
#include <iostream>

#ifndef __FILEREADER_H__
#define __FILEREADER_H__

class FileReader
{
	std::string filename;

	friend std::ostream & operator<<(std::ostream &, const FileReader &);
public:
	FileReader(const char * filename);
	~FileReader();
	
	void read();
};

#endif
