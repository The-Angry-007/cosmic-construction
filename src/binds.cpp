#include "binds.hpp"
//a macro that is used later to convert an input code to a string representing the name of that code
//this was to make the code more legible
#define CODE(a, b) \
	case a: ret = b; break;

namespace binds
{
//here is where each keybind is defined and its default value.
int Pause = sf::Keyboard::Key::Escape + 1;
int Fullscreen = sf::Keyboard::Key::F11 + 1;
}
//the code version of keycodes adds 1, since keyboard keys has a code assigned to the value 0 as well as mouse buttons.
int binds::keyToCode(sf::Keyboard::Key key)
{
	return key + 1;
}
//mouse buttons are stored as negative numbers.
int binds::buttonToCode(sf::Mouse::Button button)
{
	return -button - 1;
}

/*uses the SFML enums for keyboard keys and mouse buttons to assign a string name to each code.
this is so that the controls menu can display the name of the code assigned to each keybind.*/
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
		CODE(27, "0")
		CODE(28, "1")
		CODE(29, "2")
		CODE(30, "3")
		CODE(31, "4")
		CODE(32, "5")
		CODE(33, "6")
		CODE(34, "7")
		CODE(35, "8")
		CODE(36, "9")
		CODE(37, "Escape")
		CODE(38, "Left Control")
		CODE(39, "Left Shift")
		CODE(40, "Left Alt")
		CODE(41, "Left System")
		CODE(42, "Right Control")
		CODE(43, "Right Shift")
		CODE(44, "Right Alt")
		CODE(45, "Right System")
		CODE(46, "Menu")
		CODE(47, "[")
		CODE(48, "]")
		CODE(49, ";")
		CODE(50, ",")
		CODE(51, ".")
		CODE(52, "'")
		CODE(53, "/")
		CODE(54, "\\")
		CODE(55, "~")
		CODE(56, "=")
		CODE(57, "-")
		CODE(58, "Space")
		CODE(59, "Enter")
		CODE(60, "Backspace")
		CODE(61, "Tab")
		CODE(62, "Page Up")
		CODE(63, "Page Down")
		CODE(64, "End")
		CODE(65, "Home")
		CODE(66, "Insert")
		CODE(67, "Delete")
		CODE(68, "+")
		CODE(69, "-")
		CODE(70, "*")
		CODE(71, "/")
		CODE(72, "Left Arrow")
		CODE(73, "Right Arrow")
		CODE(74, "Up Arrow")
		CODE(75, "Down Arrow")
		CODE(76, "Numpad 0")
		CODE(77, "Numpad 1")
		CODE(78, "Numpad 2")
		CODE(79, "Numpad 3")
		CODE(80, "Numpad 4")
		CODE(81, "Numpad 5")
		CODE(82, "Numpad 6")
		CODE(83, "Numpad 7")
		CODE(84, "Numpad 8")
		CODE(85, "Numpad 9")
		CODE(86, "F1")
		CODE(87, "F2")
		CODE(88, "F3")
		CODE(89, "F4")
		CODE(90, "F5")
		CODE(91, "F6")
		CODE(92, "F7")
		CODE(93, "F8")
		CODE(94, "F9")
		CODE(95, "F10")
		CODE(96, "F11")
		CODE(97, "F12")
		CODE(98, "F13")
		CODE(99, "F14")
		CODE(100, "F15")
		CODE(101, "Pause")
		CODE(-1, "Left Mouse Button")
		CODE(-2, "Right Mouse Button")
		CODE(-3, "Middle Mouse Button")
	}
	return ret;
}