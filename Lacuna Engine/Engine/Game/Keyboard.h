#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

#include "../Func/toLowerCase.h"
#include "../Type/mi.h"

#define hashString(keyName) (std::hash<std::string>{}(keyName))
//#define keyCode_hashArray(keyNames) \
//	for (int i = 0; i < keyNames.size(); i++) { \
//		constexpr unsigned int keyCode##i = hashString(keyNames[i]); \
//	}

namespace LE
{
	class Keyboard
	{
	private:

	public:
		struct Key
		{
			int num = -1;
			bool pressed = false;
			Key(int num) : num(num) {}
			Key() {}
			~Key() {}
		};

		std::vector<Key> keys;
		// -1 = search error
		int searchKey(int num);

		Keyboard();
		~Keyboard();


	};

	inline std::unordered_map<size_t, int> keyCodeMap = {
		{hashString("space"), 32},
		{hashString("apostrophe"), 39}, // '
		{hashString("comma"), 44}, // ,
		{hashString("minus"), 45}, // -
		{hashString("period"), 46}, // .
		{hashString("slash"), 47}, // /
		{hashString("0"), 48},
		{hashString("1"), 49},
		{hashString("2"), 50},
		{hashString("3"), 51},
		{hashString("4"), 52},
		{hashString("5"), 53},
		{hashString("6"), 54},
		{hashString("7"), 55},
		{hashString("8"), 56},
		{hashString("9"), 57},
		{hashString("semicolon"), 59}, // ;
		{hashString("equal"), 61}, // =
		{hashString("a"), 65},
		{hashString("b"), 66},
		{hashString("c"), 67},
		{hashString("d"), 68},
		{hashString("e"), 69},
		{hashString("f"), 70},
		{hashString("g"), 71},
		{hashString("h"), 72},
		{hashString("i"), 73},
		{hashString("j"), 74},
		{hashString("k"), 75},
		{hashString("l"), 76},
		{hashString("m"), 77},
		{hashString("n"), 78},
		{hashString("o"), 79},
		{hashString("p"), 80},
		{hashString("q"), 81},
		{hashString("r"), 82},
		{hashString("s"), 83},
		{hashString("t"), 84},
		{hashString("u"), 85},
		{hashString("v"), 86},
		{hashString("w"), 87},
		{hashString("x"), 88},
		{hashString("y"), 89},
		{hashString("z"), 90},
		{hashString("left_bracket"), 91}, // [
		{hashString("backslash"), 92}, /* \ */
		{hashString("right_bracket"), 93}, // ]
		{hashString("grave_accent"), 96}, // `
		{hashString("world_1"), 161}, // non-US #1
		{hashString("world_2"), 162}, // non-US #2
		{hashString("escape"), 256},
		{hashString("enter"), 257},
		{hashString("tab"), 258},
		{hashString("backspace"), 259},
		{hashString("insert"), 260},
		{hashString("delete"), 261},
		{hashString("right"), 262},
		{hashString("left"), 263},
		{hashString("down"), 264},
		{hashString("up"), 265},
		{hashString("page_up"), 266},
		{hashString("page_down"), 267},
		{hashString("home"), 268},
		{hashString("end"), 269},
		{hashString("caps_lock"), 280},
		{hashString("scroll_lock"), 281},
		{hashString("num_lock"), 282},
		{hashString("print_screen"), 283},
		{hashString("pause"), 284},
		{hashString("f1"), 290},
		{hashString("f2"), 291},
		{hashString("f3"), 292},
		{hashString("f4"), 293},
		{hashString("f5"), 294},
		{hashString("f6"), 295},
		{hashString("f7"), 296},
		{hashString("f8"), 297},
		{hashString("f9"), 298},
		{hashString("f10"), 299},
		{hashString("f11"), 300},
		{hashString("f12"), 301},
		{hashString("f13"), 302},
		{hashString("f14"), 303},
		{hashString("f15"), 304},
		{hashString("f16"), 305},
		{hashString("f17"), 306},
		{hashString("f18"), 307},
		{hashString("f19"), 308},
		{hashString("f20"), 309},
		{hashString("f21"), 310},
		{hashString("f22"), 311},
		{hashString("f23"), 312},
		{hashString("f24"), 313},
		{hashString("f25"), 314},
		{hashString("kp_0"), 320},
		{hashString("kp_1"), 321},
		{hashString("kp_2"), 322},
		{hashString("kp_3"), 323},
		{hashString("kp_4"), 324},
		{hashString("kp_5"), 325},
		{hashString("kp_6"), 326},
		{hashString("kp_7"), 327},
		{hashString("kp_8"), 328},
		{hashString("kp_9"), 329},
		{hashString("kp_decimal"), 330},
		{hashString("kp_divide"), 331},
		{hashString("kp_multiply"), 332},
		{hashString("kp_subtract"), 333},
		{hashString("kp_add"), 334},
		{hashString("kp_enter"), 335},
		{hashString("kp_equal"), 336},
		{hashString("left_shift"), 340},
		{hashString("left_control"), 341},
		{hashString("left_alt"), 342},
		{hashString("left_super"), 343},
		{hashString("right_shift"), 344},
		{hashString("right_control"), 345},
		{hashString("right_alt"), 346},
		{hashString("right_super"), 347},
		{hashString("menu"), 348}
        // TO:DO: more keys
	};
	int getKeyNum(std::string key);
}