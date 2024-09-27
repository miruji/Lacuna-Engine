#include "ConvertColor.h"

std::vector<std::string> LE::colorType(std::string c)
{
	c = noSpaces(c); // delete spaces
	std::vector<std::string> Result;

	// split and get type
	if (c != "")
		Result = splitString(c, ':');

	// type verif
	if (Result.size())
		Result[0] = toUpperCase(Result[0]);
	else
	{
		Result.emplace_back("");
		Result.emplace_back("");
	}

	return Result;
}
std::vector<float> LE::convertColor(std::string c)
{
	std::vector<std::string> ct = colorType(c);

	// if rgb || rgba ->> not hex color
	std::vector<float> Color;
	if (ct[0] == "RGB" || ct[0] == "RGB_F" ||
		ct[0] == "RGBA" || ct[0] == "RGBA_F")
	{
		std::vector<std::string> ColorStr = splitString(ct[1], ',');

		Color.emplace_back(atof(ColorStr[0].c_str()));
		Color.emplace_back(atof(ColorStr[1].c_str()));
		Color.emplace_back(atof(ColorStr[2].c_str()));
		// alpha
		if (ColorStr.size()>3)
			Color.emplace_back(atof(ColorStr[3].c_str()));
		else
		{
			if (ct[0] == "RGBA")
				Color.emplace_back(255.0f);
			else
				Color.emplace_back(1.0f);
		}
		//
	}

	// set end color
	std::vector<float> result;
	if (ct[0] == "RGBA" || ct[0] == "RGBA_F")
	{
		if (ct[0] != "RGBA_F")
		{
			Color[0] = cf(Color[0]);
			Color[1] = cf(Color[1]);
			Color[2] = cf(Color[2]);
			Color[3] = cf(Color[3]);
		}

		result.emplace_back(Color[0]);
		result.emplace_back(Color[1]);
		result.emplace_back(Color[2]);
		result.emplace_back(Color[3]);
	}
	else
	if (ct[0] == "RGB" || ct[0] == "RGB_F")
	{
		if (ct[0] != "RGB_F")
		{
			Color[0] = cf(Color[0]);
			Color[1] = cf(Color[1]);
			Color[2] = cf(Color[2]);
		}

		result.emplace_back(Color[0]);
		result.emplace_back(Color[1]);
		result.emplace_back(Color[2]);
		result.emplace_back(1.0f);
	}
	else
	if (ct[0] == "HEX")
	{
		if (ct[1][0] == '#')
		{
			ct[1][0] = ' ';
			ct[1] = noSpaces(ct[1]);
		}

		result.emplace_back(cf(atoi(hexToOct(ct[1].substr(0,2)).c_str() )));
		result.emplace_back(cf(atoi(hexToOct(ct[1].substr(2,4)).c_str() )));
		result.emplace_back(cf(atoi( hexToOct(ct[1].substr(4,6)).c_str() )));
		if (ct[1].length() == 8)
			result.emplace_back(cf(atoi( hexToOct(ct[1].substr(6,8)).c_str() )));
		else
			result.emplace_back(1.0f);
	}
	else
	{
		result.emplace_back(0.0f);
		result.emplace_back(0.0f);
		result.emplace_back(0.0f);
		result.emplace_back(1.0f);
	}

	return result;
}