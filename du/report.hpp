#include<locale>
#include<iostream>
#include <string> 
#include<fstream>
#include <Windows.h>
#include <map> 
#include <math.h>       /* floor */
//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "library.hpp"
// print help report
void reportSwitchHelp();
// print out one line of the report
void printReport(std::string path, long size, bool bSwitch, bool hSwitch, unsigned clusterSize);
// make a full report 
void report(std::experimental::filesystem::path const& f, std::map<std::string, long> dirContainer, bool sSwitch, bool bSwitch,
	bool hSwitch, bool zSwitch, bool nSwitch, bool rSwitch, bool helpSwitch, unsigned clusterSize);