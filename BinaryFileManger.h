#pragma once
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include <assert.h>
#include <string>
#include <vector>

struct Command
{
	int zl;
	char* zz;
};

struct DATA_HEADER
{
	int dataCount;				//整体数目
	std::vector<int> FrameRate; 
};

struct RuningDATA
{
	int   time;
	char* msg;
};

class BinaryFileManger
{
private:
	BinaryFileManger()
	{
		_headerFile = "playerHeader.info";
		_dataFile = "playerData.info";
		//Init();
	}

public:
	static BinaryFileManger & Instance()
	{
		static BinaryFileManger instance;
		return instance;
	}

public:
	void Init();
	void Remove();

	void test();

private:
	void WriteHeader(int count, int time);
	void ReadHeader();

	void ReadData(char* msg, int index);
	void WriteData(const char* msg);

private:
	std::string _headerFile;
	std::string _dataFile;
};

