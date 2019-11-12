//@author Minh Nguyen
//@author m_nguyen88630@fanshawec.ca
//@date 2019 - 08 - 10
//@version 1.0
//@note Developed for Visual C++ 11.0 / GCC 3.2
//@brief Implementation of size of root folder
//class for validate input
//import library
#include "validation.hpp"
using namespace std;
using namespace std::experimental::filesystem;

//  validation
bool validationIsError(int state, bool bSwitch, bool hSwitch, bool zSwitch, bool nSwitch, bool kSwitch, bool blockSizeSwitch)
{
	if (bSwitch == true && hSwitch == true)
	{
		//Detects b and h cant both be used
		cerr << "Error b and h can not both be used" << endl;
		return true;
	}
	if (kSwitch == true && blockSizeSwitch == true)
	{
		// Detects k and block - size cant both be used.
		cerr << "Error k and block size can not both be used" << endl;
		return true;
	}
	if (zSwitch == true && nSwitch == true)
	{
		//Detects z and n cant both be used.
		cerr << "Error z and n can not both be used" << endl;
		return true;
	}
	if (state == 1)
	{
		//Detects duplicate switch
		cerr << "Error duplicate switch" << endl;
		return true;
	}
	if (state == 2)
	{
		//Detects bad switch 
		cerr << "Error bad switch" << endl;
		return true;
	}
	if (state == 3)
	{
		cerr << "Error must enter number when using block size switch" << endl;
		return true;
	}
	if (state == 4)
	{
		//bad number on block-size 
		cerr << "Error bad number on block size switch" << endl;
		return true;
	}
	return false;
}