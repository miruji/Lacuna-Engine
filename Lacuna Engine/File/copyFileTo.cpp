#include "copyFileTo.h"

bool LE::copyFileTo(std::string Src, std::string To)
{
	std::ifstream S(Src, std::ios::binary);
	std::ofstream T(To+getFileName(Src)[0], std::ios::binary);
	T << S.rdbuf();

	return S && T;
}