//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder

//import library
#include "library.hpp"

// this function will process the path if user enter path in cmd the path will be the input
//else it will create path to the folder contain .exe file
bool getPath(std::experimental::filesystem::path& f, bool bSwitch, bool hSwitch, unsigned clusterSize);
// this function to calculate cluster size
unsigned getClusterSize();
//this function to check is a string are postive interger
bool is_number(const std::string& s);
// this function take cmd arguement and process all the switch
int processInput(std::experimental::filesystem::path& f, std::vector<std::string> cmdArgue, bool& sSwitch, bool& bSwitch, bool& hSwitch, bool& zSwitch,
	bool& nSwitch, bool& rSwitch, bool& kSwitch, bool& blockSizeSwitch, bool& helpSwitch, unsigned& clusterSize);
std::vector<std::string> loadInputToVector(int argc, char* argv[]);