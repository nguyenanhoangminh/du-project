/** @file: du.cpp
@author Minh Nguyen
 @author m_nguyen88630@fanshawec.ca
 @date 2019-08-10
 @version 1.0
@note Developed for Visual C++ 11.0/GCC 3.2
@brief Implementation of size of root folder
 */
#include "processInputData.hpp"
#include "validation.hpp"
#include "scan.hpp"
#include "report.hpp"

using namespace std;
using namespace std::experimental::filesystem;

int main(int argc, char* argv[])
{
	// declare and initial variable
	bool sSwitch = false;
	bool bSwitch = false;
	bool hSwitch = false;
	bool zSwitch = false;
	bool nSwitch = false;
	bool rSwitch = false;
	bool kSwitch = false;
	bool blockSizeSwitch = false;
	bool helpSwitch = false;
	path folder;
	unsigned clusterSize;

	// process cluster size
	clusterSize = getClusterSize();

	//proccess input from cmd
	vector<string> cmdArgue = loadInputToVector(argc, argv);//vector cotain all cmd arguement
	int state = processInput(folder, cmdArgue, sSwitch, bSwitch, hSwitch, zSwitch,
		nSwitch, rSwitch, kSwitch, blockSizeSwitch, helpSwitch, clusterSize);

	//validate
	if (validationIsError(state, bSwitch, hSwitch, zSwitch, nSwitch, kSwitch, blockSizeSwitch))
	{
		return EXIT_FAILURE;
	}

	// process path
	if (!getPath(folder, bSwitch, hSwitch, clusterSize))
	{
		return EXIT_FAILURE;
	}
	if (is_directory(folder))// if a path is a folder print out report
	{
		// get file name and file size
		map<string, long> dir = dirNameAndSize(folder, clusterSize);
		//report
		report(folder, dir, sSwitch, bSwitch, hSwitch, zSwitch, nSwitch, rSwitch, helpSwitch, clusterSize);
	}
}

