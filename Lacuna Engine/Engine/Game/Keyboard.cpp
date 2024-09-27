#include "Keyboard.h"

LE::Keyboard::Keyboard()
{
}
LE::Keyboard::~Keyboard()
{
}
int LE::Keyboard::searchKey(int num)
{
    for_er(i, 0, i < keys.size(), i++, keys[i].num == num, i);
	return -1;
}
int LE::getKeyNum(std::string key)
{
	size_t keyCode = hashString(toLowerCase(key));
	auto it = keyCodeMap.find(keyCode);

	if (it != keyCodeMap.end()) {
		switch (it->second) {
            case 32: return 32; // "SPACE"
            case 39: return 39; // "APOSTROPHE"
            case 44: return 44; // "COMMA"
            case 45: return 45; // "MINUS"
            case 46: return 46; // "PERIOD"
            case 47: return 47; // "SLASH"
            case 48: return 48; // "0"
            case 49: return 49; // "1"
            case 50: return 50; // "2"
            case 51: return 51; // "3"
            case 52: return 52; // "4"
            case 53: return 53; // "5"
            case 54: return 54; // "6"
            case 55: return 55; // "7"
            case 56: return 56; // "8"
            case 57: return 57; // "9"
            case 59: return 59; // "SEMICOLON"
            case 61: return 61; // "EQUAL"
            case 65: return 65; // "A"
            case 66: return 66; // "B"
            case 67: return 67; // "C"
            case 68: return 68; // "D"
            case 69: return 69; // "E"
            case 70: return 70; // "F"
            case 71: return 71; // "G"
            case 72: return 72; // "H"
            case 73: return 73; // "I"
            case 74: return 74; // "J"
            case 75: return 75; // "K"
            case 76: return 76; // "L"
            case 77: return 77; // "M"
            case 78: return 78; // "N"
            case 79: return 79; // "O"
            case 80: return 80; // "P"
            case 81: return 81; // "Q"
            case 82: return 82; // "R"
            case 83: return 83; // "S"
            case 84: return 84; // "T"
            case 85: return 85; // "U"
            case 86: return 86; // "V"
            case 87: return 87; // "W"
            case 88: return 88; // "X"
            case 89: return 89; // "Y"
            case 90: return 90; // "Z"
            case 91: return 91; // "LEFT_BRACKET"
            case 92: return 92; // "BACKSLASH"
            case 93: return 93; // "RIGHT_BRACKET"
            case 96: return 96; // "GRAVE_ACCENT"
            case 161: return 161; // "WORLD_1"
            case 162: return 162; // "WORLD_2"
            case 256: return 256; // "ESCAPE"
            case 257: return 257; // "ENTER"
            case 258: return 258; // "TAB"
            case 259: return 259; // "BACKSPACE"
            case 260: return 260; // "INSERT"
            case 261: return 261; // "DELETE"
            case 262: return 262; // "RIGHT"
            case 263: return 263; // "LEFT"
            case 264: return 264; // "DOWN"
            case 265: return 265; // "UP"
            case 266: return 266; // "PAGE_UP"
            case 267: return 267; // "PAGE_DOWN"
            case 268: return 268; // "HOME"
            case 269: return 269; // "END"
            case 280: return 280; // "CAPS_LOCK"
            case 281: return 281; // "SCROLL_LOCK"
            case 282: return 282; // "NUM_LOCK"
            case 283: return 283; // "PRINT_SCREEN"
            case 284: return 284; // "PAUSE"
            case 290: return 290; // "F1"
            case 291: return 291; // "F2"
            case 292: return 292; // "F3"
            case 293: return 293; // "F4"
            case 294: return 294; // "F5"
            case 295: return 295; // "F6"
            case 296: return 296; // "F7"
            case 297: return 297; // "F8"
            case 298: return 298; // "F9"
            case 299: return 299; // "F10"
            case 300: return 300; // "F11"
            case 301: return 301; // "F12"
            case 302: return 302; // "F13"
            case 303: return 303; // "F14"
            case 304: return 304; // "F15"
            case 305: return 305; // "F16"
            case 306: return 306; // "F17"
            case 307: return 307; // "F18"
            case 308: return 308; // "F19"
            case 309: return 309; // "F20"
            case 310: return 310; // "F21"
            case 311: return 311; // "F22"
            case 312: return 312; // "F23"
            case 313: return 313; // "F24"
            case 314: return 314; // "F25"
            case 320: return 320; // "KP_0"
            case 321: return 321; // "KP_1"
            case 322: return 322; // "KP_2"
            case 323: return 323; // "KP_3"
            case 324: return 324; // "KP_4"
            case 325: return 325; // "KP_5"
            case 326: return 326; // "KP_6"
            case 327: return 327; // "KP_7"
            case 328: return 328; // "KP_8"
            case 329: return 329; // "KP_9"
            case 330: return 330; // "KP_DECIMAL"
            case 331: return 331; // "KP_DIVIDE"
            case 332: return 332; // "KP_MULTIPLY"
            case 333: return 333; // "KP_SUBTRACT"
            case 334: return 334; // "KP_ADD"
            case 335: return 335; // "KP_ENTER"
            case 336: return 336; // "KP_EQUAL"
            case 340: return 340; // "LEFT_SHIFT"
            case 341: return 341; // "LEFT_CONTROL"
            case 342: return 342; // "LEFT_ALT"
            case 343: return 343; // "LEFT_SUPER"
            case 344: return 344; // "RIGHT_SHIFT"
            case 345: return 345; // "RIGHT_CONTROL"
            case 346: return 346; // "RIGHT_ALT"
            case 347: return 347; // "RIGHT_SUPER"
            case 348: return 348; // "MENU"
            // TO:DO: more keys
            default: return -1; // ����������� ��� �������
		}
	}
	else // if no in unsorted map
    {
	}
	return -1;
}