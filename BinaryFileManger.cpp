#include "BinaryFileManger.h"

void BinaryFileManger::test()
{
	Remove();

	WriteHeader(1, 100);
	std::string s = "11111111111111111";
	WriteData(s.c_str());
	ReadData(nullptr, 1);

	ReadHeader();
	WriteHeader(2, 105);
	s = "2222222222222222222";
	WriteData(s.c_str());
	ReadData(nullptr, 2);

	ReadHeader();
	WriteHeader(3, 105);
	s = "333333333333333333333";
	WriteData(s.c_str());
	ReadData(nullptr, 3);

	ReadHeader();
	WriteHeader(4, 605);
	ReadHeader();
	s = "44444444444444444444";
	WriteData(s.c_str());
	ReadData(nullptr, 4);
}

void BinaryFileManger::Init()
{

}

void BinaryFileManger::Remove()
{
	remove(_headerFile.c_str());
	remove(_dataFile.c_str());
}

void BinaryFileManger::WriteHeader(int count, int time)
{
	FILE* fwriteHeaderFile = fopen(_headerFile.c_str(), "rb+");

	if (fwriteHeaderFile == NULL)
	{
		FILE* fwriteFile = fopen(_headerFile.c_str(), "wb");
		fclose(fwriteFile);

		fwriteHeaderFile = fopen(_headerFile.c_str(), "rb+");
		if (fwriteHeaderFile == NULL)
			return;
	}

	fseek(fwriteHeaderFile, 0, SEEK_SET);
	fwrite(&count, sizeof(int), 1, fwriteHeaderFile);
	
	//fseek(fwriteHeaderFile, sizeof(int) + sizeof(int)*(count-1), SEEK_SET);
	fseek(fwriteHeaderFile, 0, SEEK_END);
	fwrite(&time, sizeof(int), 1, fwriteHeaderFile);

	fclose(fwriteHeaderFile);
}

void BinaryFileManger::ReadHeader()
{
	char* cmd = NULL;
	FILE* freadfile;
	freadfile = fopen(_headerFile.c_str(), "rb");
	fseek(freadfile, 0, SEEK_SET);
	int count = 0;
	fread(&count, sizeof(int), 1, freadfile);

	std::vector<int> _timeList;
	for (int i = 1; i <= count;i++)
	{
		fseek(freadfile, sizeof(int) + sizeof(int)*(i-1), SEEK_SET);
		int time = -1;
		fread(&time, sizeof(int), 1, freadfile);
		int t = time;
		_timeList.push_back(time);
	}
	fclose(freadfile);
}

void BinaryFileManger::WriteData(const char* msg)
{
	FILE* fwriteHeaderFile = fopen(_dataFile.c_str(), "rb+");

	if (fwriteHeaderFile == NULL)
	{
		FILE* fwriteFile = fopen(_dataFile.c_str(), "wb");
		fclose(fwriteFile);

		fwriteHeaderFile = fopen(_dataFile.c_str(), "rb+");
		if (fwriteHeaderFile == NULL)
			return;
	}

	fseek(fwriteHeaderFile, 0, SEEK_END);
	fwrite(msg, 4096, 1, fwriteHeaderFile);

	fclose(fwriteHeaderFile);
}

void BinaryFileManger::ReadData(char* msg, int index)
{
	char* cmd = NULL;
	FILE* freadfile;
	freadfile = fopen(_dataFile.c_str(), "rb");

	for (int i = 1; i <= index; i++)
	{
		fseek(freadfile, 4096 * (i - 1), SEEK_SET);
		char info[4096];
		fread(&info, 4096, 1, freadfile);
		int g = 0;
	}
	
	fclose(freadfile);
}