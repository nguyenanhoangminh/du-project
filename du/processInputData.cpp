//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "processInputData.hpp"
#include "report.hpp"

using namespace std;
using namespace std::experimental::filesystem;

// put cmd arguement to a vector for later process
vector<string> loadInputToVector(int argc, char* argv[])
{
	vector<string> cmdArgue;//command arguments
	for (int index = 0; index < argc; index++)
	{
		cmdArgue.push_back(argv[index]);
	}
	return cmdArgue;
}
// process input from cmd arguement
int processInput(path& f, vector<string> cmdArgue, bool& sSwitch, bool& bSwitch, bool& hSwitch, bool& zSwitch,
	bool& nSwitch, bool& rSwitch, bool& kSwitch, bool& blockSizeSwitch, bool& helpSwitch, unsigned& clusterSize)
{
	//last element in the vector is path and first element in the vector is du.exe
	for (size_t index = 1; index < cmdArgue.size(); index++)
	{

		// 1 for dupicated switch
		// 2 for bad switch
		// 3 for just only entered --block-size= with no data benhind =
		// 4 for bad number on block-size
		if (cmdArgue[index].at(0) == '-' && cmdArgue[index].at(1) != '-')
		{
			for (size_t i = 1; i < cmdArgue[index].length(); i++)
			{
				if (cmdArgue[index].at(i) == 's')
				{
					if (sSwitch == true)// if switch alredy pressed before return 1
						return 1;
					else// else set switch = true
						sSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'b')
				{
					if (bSwitch == true)
						return 1;
					else
						bSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'h')
				{
					if (hSwitch == true)
						return 1;
					else
						hSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'z')
				{

					if (zSwitch == true)
						return 1;
					else
						zSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'n')
				{
					if (nSwitch == true)
						return 1;
					else
						nSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'r')
				{
					if (rSwitch == true)
						return 1;
					else
						rSwitch = true;
				}
				else if (cmdArgue[index].at(i) == 'k')
				{
					if (kSwitch == true)
						return 1;
					else
					{
						kSwitch = true;
						clusterSize = 1024;
					}
				}
				else
					return 2;
			}
		}
		else if (cmdArgue[index].at(0) == '-' && cmdArgue[index].at(1) == '-')
		{
			if (cmdArgue[index].substr(2, 11).compare("block-size=") == 0)// the first 12 character of this string
			{
				if (blockSizeSwitch == true)
					return 1;
				else
				{
					blockSizeSwitch = true;
					if (cmdArgue[index].length() > 13)
					{
						if (is_number(cmdArgue[index].substr(13)))// if string is positive numberic 
						{
							clusterSize = stoi(cmdArgue[index].substr(13));//parse string to number
							if (clusterSize == 0)//cluster size can't equal 0
								return 4;//bad number
						}
						else
							return 4;//bad number
					}
					else//string only have 12 character
						return 3;
				}
			}
			else if (cmdArgue[index].substr(2, 4).compare("help") == 0)
			{
				if (cmdArgue[index].length() > 6)//--help have length == 6
					return 2;
				if (helpSwitch == true)
					return 1;
				else
					helpSwitch = true;
			}
		}
		else if (index == cmdArgue.size() - 1)
		{
			f = cmdArgue[index];
		}
		else
			return 2;
	}
	return 0;
}
// function to check is a string a positive numberic string
bool is_number(const string& s)
{
	string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}
//clusteSize
unsigned getClusterSize()
{
	string drive = absolute("Java").root_name().string() + '\\';
	DWORD sectorsPerCluster, bytesPerSector, numberFreeClusters, totalNumberOfClusters;
	if (GetDiskFreeSpaceA(drive.c_str(), &sectorsPerCluster, &bytesPerSector, &numberFreeClusters, &totalNumberOfClusters))
	{

		return (sectorsPerCluster * bytesPerSector);
	}
	else
		return 4096;
}
// process path
bool getPath(path& f, bool bSwitch, bool hSwitch, unsigned clusterSize)
{
	// process path
	if (f.string().compare("") == 0)//   no path provided
	{
		path current = ".";// the current folder
		f = current;
	}
	else
	{
		if (!exists(f))// check if the path entered is exist
		{
			cerr << "Error: folder <" << f << "> doesn't exist." << endl;
			return false;//path doesn't exist
		}
		if (is_regular_file(f))// if the path is a normal file 
		{
			//calculate file size on disk
			double fileNumberOfCluster = file_size(f) / (double)(clusterSize);
			if (fileNumberOfCluster > floor(fileNumberOfCluster))
			{
				fileNumberOfCluster = (floor(fileNumberOfCluster) + 1);
			}
			long fileSizeOnDisk = (long)(fileNumberOfCluster);
			// print out file name and it size
			printReport(f.string(), fileSizeOnDisk, bSwitch, hSwitch, clusterSize);
		}

	}
	return true;//path exist
}
