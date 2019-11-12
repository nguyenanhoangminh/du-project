//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "library.hpp" 
// sort the report ore base on file name alphabet
std::vector<std::string> fileNameOrder(std::map<std::string, long> dirContainer);
//sort the report ore base on file size
std::vector<std::string> fileSizeOrder(std::map<std::string, long> dirContainer);
//sort the report from subfolders to root folder
std::vector<std::string> normalOrder(std::experimental::filesystem::path const& f,
	std::map<std::string, long> dirContainer);
// choose what order for the report to display
std::vector<std::string> reportOrder(std::experimental::filesystem::path const& f,
	std::map<std::string, long> dirContainer, bool zSwitch, bool nSwitch, bool rSwitch);