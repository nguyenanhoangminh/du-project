//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder
// this class for report
//import library
#include "report.hpp"
#include "reportOrder.hpp"
#include "reportSize.hpp"

using namespace std;
using namespace std::experimental::filesystem;

void report(path const& f, map<string, long> dirContainer, bool sSwitch, bool bSwitch,
	bool hSwitch, bool zSwitch, bool nSwitch, bool rSwitch, bool helpSwitch, unsigned clusterSize)
{
	if (helpSwitch == true)// if --help switch is pressed print only help
	{
		reportSwitchHelp();
	}
	else
	{
		if (sSwitch == true)// if s switch pressed the root folder, showing the sum of all clusters
		{
			for (auto it = dirContainer.begin(); it != dirContainer.end(); it++)
			{
				if (it->first.compare(f.string()) == 0)
				{
					printReport(it->first, it->second, bSwitch, hSwitch, clusterSize);
				}
			}
		}
		else//print full report
		{
			// report base on report order
			vector<string> order = reportOrder(f, dirContainer, zSwitch, nSwitch, rSwitch);
			for (auto itr = order.begin(); itr != order.end(); itr++)
			{
				for (auto it = dirContainer.begin(); it != dirContainer.end(); it++)
				{
					if (it->first.compare(*itr) == 0)// compare pathname if the same path name print ou the size 
					{
						printReport(it->first, it->second, bSwitch, hSwitch, clusterSize);
					}
				}
			}
		}
	}
}

// function for whether to display size in byte, cluster or KiB, MiB, GiB, TiB
void printReport(string path, long size, bool bSwitch, bool hSwitch, unsigned clusterSize)
{
	if (bSwitch == false && hSwitch == false)// both -b and -h switch not entered
	{
		//normal report
		reportNotSwitchBAndH(path, size);
	}
	else if (bSwitch == true && hSwitch == false)//-b switch entered
	{
		// b switch report
		reportSwitchB(path, size, clusterSize);
	}
	else//-h switch entered. -b and -h can't enter in the same time
	{
		// h switch report"
		reportSwitchH(path, size, clusterSize);
	}
}

void reportSwitchHelp()
{
	cout << "du(c) 2019, Minh Nguyen " << endl;
	cout << "===========================================================" << endl;
	cout << "Version 1.0.0" << endl << endl;
	cout << "A disk usage utility inspired by the UNIX du command." << endl << endl;
	cout << "Usage: du[-skhb][--help][--block - size = dddd][folder] *" << endl << endl;
	cout << "Examples :" << endl;
	cout << "  du" << endl;
	cout << "    > display the sum of the cluster sizes of each directory" << endl;
	cout << "      starting the cwd" << endl << endl;
	cout << "  du folder" << endl;
	cout << "    > display the sum of the cluster sizes of each directory" << endl;
	cout << "      starting with 'folder'" << endl << endl;
	cout << "  du - h" << endl;
	cout << "    > display the results in a human readable form" << endl << endl;
	cout << "  du - s" << endl;
	cout << "    > display only the final summary" << endl << endl;
	cout << "  du - b" << endl;
	cout << "    > display in bytes" << endl << endl;
	cout << "  du - k" << endl;
	cout << "    > cluster size is 1024" << endl << endl;
	cout << "  du - z" << endl;
	cout << "    > display the list sorted by size" << endl << endl;
	cout << "  du - n" << endl;
	cout << "    > display the list sorted by name" << endl << endl;
	cout << "  du - r" << endl;
	cout << "    > display the list in reverse order" << endl << endl;
	cout << "  du --block - size = dddd" << endl;
	cout << "    > set the cluster size to the specified integer > 0" << endl << endl;
	cout << "  du --help" << endl;
	cout << "    > displays the help" << endl;
}