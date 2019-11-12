//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

// this class select whether to report file size in cluster, byte, or MB KB GB TB
//import library
#include "reportSize.hpp"

using namespace std;
using namespace std::experimental::filesystem;

// normal report when either -b and -h switch not entered
void reportNotSwitchBAndH(string path, long size)
{
	//cluster size report 
	cout << left;
	cout << setw(20) << size << setw(20) << path << endl;
}
//-b Switch

void reportSwitchB(string path, long size, unsigned clusterSize)
{
	cout << left;
	cout << setw(20) << size * clusterSize << setw(20) << path << endl;//byte size report
}


//h Switch
void reportSwitchH(string path, long size, unsigned clusterSize)
{
	//readable size report kb mb gb tb
	size *= clusterSize;

	//if size value greater than 1024 convert it to other type
	if (size >= 1024)
	{
		double KB = size / 1024.0;

		if (KB >= 1024)
		{
			double MB = KB / 1024.0;
			if (MB >= 1024)
			{
				double GB = MB / 1024.0;
				if (GB >= 1024)
				{
					double TB = GB / 1024.0;
					cout << left;
					cout << dataMeasurementRound(TB) << setw(10) << "T";
					formatOutput(dataMeasurementRound(TB));
					cout << path << endl;
				}
				else
				{
					cout << left;
					cout << dataMeasurementRound(GB) << setw(10) << "G";
					formatOutput(dataMeasurementRound(GB));
					cout << path << endl;
				}
			}
			else
			{
				cout << left;
				cout << dataMeasurementRound(MB) << setw(10) << "M";
				formatOutput(dataMeasurementRound(MB));
				cout << path << endl;
			}
		}
		else
		{
			cout << left;
			cout << dataMeasurementRound(KB) << setw(10) << "K";
			formatOutput(dataMeasurementRound(KB));
			cout << path << endl;
		}
	}
	else
	{
		cout << left;
		cout << setw(10) << size << " ";
		formatOutput((double)(size));
		cout << path << endl;
	}

}
void formatOutput(double sizeValue)
{
	for (int i = 0; i < 10 - numberLength(sizeValue); i++)//display white space to format
	{
		cout << " ";
	}
}
int numberLength(double sizeValue)
{
	int length = 0;
	if (sizeValue != round(sizeValue))// size is rounded at one demical if size <10
		length += 2; // example .x
	sizeValue = round(sizeValue);// round and convert to int
	length += to_string((int)(sizeValue)).length();//size
	return length;
}
double dataMeasurementRound(double dataMeasurement)
{
	if (dataMeasurement < 10)
		return round(dataMeasurement * 10) / 10.0;// size is rounded at one demical if size <10
	else
		return round(dataMeasurement);//round size

}