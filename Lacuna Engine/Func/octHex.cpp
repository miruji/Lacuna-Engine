#include "octHex.h"

int LE::hexCharToInt(char N)
{
	if (N == '0') return 0; else
	if (N == '1') return 1; else
	if (N == '2') return 2; else
	if (N == '3') return 3; else
	if (N == '4') return 4; else
	if (N == '5') return 5; else
	if (N == '6') return 6; else
	if (N == '7') return 7; else
	if (N == '8') return 8; else
	if (N == '9') return 9; else
	if (N == 'A' || N == 'a') return 10; else
	if (N == 'B' || N == 'b') return 11; else
	if (N == 'C' || N == 'c') return 12; else
	if (N == 'D' || N == 'd') return 13; else
	if (N == 'E' || N == 'e') return 14; else
	if (N == 'F' || N == 'f') return 15; else
	return 0;
}
std::string LE::hexToOct(std::string Str)
{
	int N1 = hexCharToInt(Str[0]);
	int N2 = hexCharToInt(Str[1]);
	return std::to_string(N1*16+N2);
}
std::string LE::octToHex(std::string Str)
{
	int N = atoi(Str.c_str());
	if (N < 0)
		N = 0;
	else
	if (N > 255)
		N = 255;

	std::stringstream ss;
	ss << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << N;
	return ss.str();
}