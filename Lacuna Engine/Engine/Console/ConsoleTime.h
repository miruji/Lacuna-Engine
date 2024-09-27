#pragma once
#include <iostream>

// -- ctime
#pragma warning (disable: 4996)
#include <chrono> // ms time
#include <ctime> // time
#include <iomanip>
#include <sstream>

namespace LE
{
	std::string GetTime(std::string DEL); // HH:MM:SS
	std::string GetDate();                // YYYY-MM-DD
}