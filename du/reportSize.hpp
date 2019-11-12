//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "library.hpp"
// function  to round data measurement
double dataMeasurementRound(double dataMeasurement);
//Makes human readable. Outputs is in KiB, MiB, GiB, TiB 
void reportSwitchH(std::string path, long size, unsigned clusterSize);
//Displays in bytes, not clusters
void reportSwitchB(std::string path, long size, unsigned clusterSize);
//Displays in clusters
void reportNotSwitchBAndH(std::string path, long size);
// format H switch report
void formatOutput(double sizeValue);
// calculate a length of a number
int numberLength(double sizeValue);