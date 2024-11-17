#include "binds.hpp"
//a macro that is used later to convert an input code to a string representing the name of that code
#define CODE(a, b) \
	case a: ret = b; break;

namespace binds
{
int Pause = sf::Keyboard::Key::Escape + 1;
}

int binds::keyToCode(sf::Keyboard::Key key)
{
	return key + 1;
}
int binds::buttonToCode(sf::Mouse::Button button)
{
	return -button - 1;
}

std::string binds::GetName(int code)
{
	std::string ret = "";
	switch (code)
	{
		CODE(1, "A")
		CODE(2, "B")
		CODE(3, "C")
		CODE(4, "D")
		CODE(5, "E")
		CODE(6, "F")
		CODE(7, "G")
		CODE(8, "H")
		CODE(9, "I")
		CODE(10, "J")
		CODE(11, "K")
		CODE(12, "L")
		CODE(13, "M")
		CODE(14, "N")
		CODE(15, "O")
		CODE(16, "P")
		CODE(17, "Q")
		CODE(18, "R")
		CODE(19, "S")
		CODE(20, "T")
		CODE(21, "U")
		CODE(22, "V")
		CODE(23, "W")
		CODE(24, "X")
		CODE(25, "Y")
		CODE(26, "Z")
		CODE(, "Num Pad 0")
		CODE(, "Num Pad 1")
		CODE(, "Num Pad 2")
		CODE(, "Num Pad 3")
		CODE(, "Num Pad 4")
		CODE(, "Num Pad 5")
		CODE(, "Num Pad 6")
		CODE(, "Num Pad 7")
		CODE(, "Num Pad 8")
		CODE(, "Num Pad 9")
		CODE(, "Num Pad ")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
		CODE(, "")
	}
	return ret;
}