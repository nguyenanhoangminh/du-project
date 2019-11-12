//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

// this class use to scan all the subfolder of path
//import library
#include "scan.hpp"
using namespace std;
using namespace std::experimental::filesystem;

//recursively scan the current folder and all subfolders to get all the file size
map<string, long> rscan(path const& f, unsigned clusterSize)
{
	recursive_directory_iterator dir(f);
	recursive_directory_iterator end;

	//begin the search
	map<string, long>	file;//cotainer string for file name long for file size
	while (dir != end)
	{
		//find and store all file size of file
		if (is_regular_file(dir->status()))
		{
			//calculate file size on disk
			double fileNumberOfCluster = file_size(dir->path()) / (double)(clusterSize);
			if (fileNumberOfCluster > floor(fileNumberOfCluster))
			{
				fileNumberOfCluster = (floor(fileNumberOfCluster) + 1);
			}
			long fileSizeOnDisk = (long)(fileNumberOfCluster);
			//store filesize and file name
			file.insert({ dir->path().string(),fileSizeOnDisk });
		}

		++dir;
	}
	return file;
}

//store directory_entry folder name of a directory (but does not visit the subdirectories)
map<string, long> scanDir(path const& f)
{
	directory_iterator dir(f);
	directory_iterator end;
	map<string, long> dirContainer;
	//begin the search
	while (dir != end)
	{
		if (is_directory(dir->status()))
		{
			dirContainer.insert({ dir->path().string(),0 });// assign folder size =0 and will calculate file size later
		}
		++dir;
	}
	dirContainer.insert({ f.string(),0 });// store the folder name of the path
	return dirContainer;
}

//store all the name and size of all [dir]
map<string, long> dirNameAndSize(path const& folder, unsigned clusterSize)
{
	map<string, long> file = rscan(folder, clusterSize);
	map<string, long> dir = scanDir(folder);
	for (auto itr = dir.begin(); itr != dir.end(); itr++)
	{
		for (auto it2 = file.begin(); it2 != file.end(); it2++)
		{
			string folderName = itr->first;
			if (folderName.substr(folderName.length() - 1).compare("\\") != 0)// if (path don't have "\" in the end)
				folderName.append("\\");// add "\" to path
			if (it2->first.find(folderName) != string::npos)// cehck if a file or folder is subfoler of  folder
			{
				itr->second += it2->second;// size of foler =size of subfolder
			}
		}
	}
	return dir;
}

