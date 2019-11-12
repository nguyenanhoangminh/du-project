//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "library.hpp"

//Function declarations
// store all the dir name and folder size 
std::map<std::string, long> dirNameAndSize(std::experimental::filesystem::path const& folder, unsigned clusterSize);
// store all the dir name
std::map<std::string, long> scanDir(std::experimental::filesystem::path const& f);
// this function to store all the file, dir name and file size 
std::map<std::string, long> rscan(std::experimental::filesystem::path const& f, unsigned clusterSize);

