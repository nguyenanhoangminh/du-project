//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder
// this class use to define what order to report subfolder
//import library
#include"reportOrder.hpp"

using namespace std;
using namespace std::experimental::filesystem;

vector<string> reportOrder(path const& f, map<string, long> dirContainer, bool zSwitch, bool nSwitch, bool rSwitch)
{
	if (zSwitch == true && rSwitch == false)
	{
		//Z switch pressed 
		return fileSizeOrder(dirContainer);
	}
	else if (nSwitch == true && rSwitch == false)
	{
		//N switch pressed 
		return fileNameOrder(dirContainer);
	}
	else if (zSwitch == false && nSwitch == false && rSwitch == false)
	{
		//no Switch pressed 
		return normalOrder(f, dirContainer);
	}
	//reverse
	else if (zSwitch == true && rSwitch == true)
	{
		//Z and R switch pressed 
		vector<string> reverseFileSizeOrder;
		vector<string> fileSizeOrderCopy = fileSizeOrder(dirContainer);
		// copy fileSizeOrderCopy to reverseFileSizeOrder in reverse way 
		copy(fileSizeOrderCopy.rbegin(), fileSizeOrderCopy.rend(), back_inserter(reverseFileSizeOrder));
		return reverseFileSizeOrder;
	}
	else if (nSwitch == true && rSwitch == true)
	{
		//N and R switch pressed 
		vector<string> reverseFileNameOrder;
		vector<string> fileNameOrderCopy = fileNameOrder(dirContainer);
		copy(fileNameOrderCopy.rbegin(), fileNameOrderCopy.rend(), back_inserter(reverseFileNameOrder));
		return reverseFileNameOrder;
	}
	else // (zSwitch == false && nSwitch == false && rSwitch == true)
	{
		//R switch pressed 
		vector<string> reverseNormalOrder;
		vector<string> normalOrderCopy = normalOrder(f, dirContainer);
		copy(normalOrderCopy.rbegin(), normalOrderCopy.rend(), back_inserter(reverseNormalOrder));

		return reverseNormalOrder;
	}
}
// store path name in directory order
vector<string> normalOrder(path const& f, map<string, long> dirContainer)
{
	directory_iterator dir(f);
	directory_iterator end;
	vector<string> pathNormalOrder;
	//begin the search
	while (dir != end)
	{
		if (is_directory(dir->status()))
		{
			pathNormalOrder.push_back(dir->path().string());
		}
		++dir;
	}
	pathNormalOrder.push_back(f.string());
	return pathNormalOrder;
}
// store path name in size order
vector<string> fileSizeOrder(map<string, long> dirContainer)
{
	set<long> dirSortedBySize;//store unique size and sort size
	for (auto it = dirContainer.begin(); it != dirContainer.end(); it++)
	{
		dirSortedBySize.insert(it->second);
	}
	vector<string> pathFileSizeOrder;

	for (auto itr = dirSortedBySize.begin(); itr != dirSortedBySize.end(); itr++)
	{
		for (auto it = dirContainer.begin(); it != dirContainer.end(); it++)
		{
			if (it->second == *itr)//if size file == size
				pathFileSizeOrder.push_back(it->first);//add file name
		}
	}

	return pathFileSizeOrder;
}
// store path name in name order
vector<string> fileNameOrder(map<string, long> dirContainer)
{

	vector<string> pathFileNameOrder;
	for (auto it = dirContainer.begin(); it != dirContainer.end(); it++)
	{
		pathFileNameOrder.push_back(it->first);
	}
	return pathFileNameOrder;
}