#include "IntToBinStr.h"
#include <string>
#include <iostream>

void IntToBinStr(int digit)
{
	unsigned int udigit = *reinterpret_cast<unsigned int*>(&digit);
	std::string result(32, '0');
	auto resultIt = result.begin();
	while (udigit != 0)
	{
		*(resultIt++) = (udigit & 1) == 0?'0':'1';
		udigit >>= 1;
	}

	std::reverse(result.begin(), result.end());
	std::cout << result << std::endl;
}
