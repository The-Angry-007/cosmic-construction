# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/binds.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/binds.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/binds.hpp" 1
       


namespace binds
{
extern int Pause;
extern int Fullscreen;
extern int Pan;
extern int DragItem;
extern int UseTool;
extern int Tool1;
extern int Tool2;
extern int Tool3;
extern int RotateStructure;
extern int CloseInventory;
extern int FlipStructure;
int keyToCode(sf::Keyboard::Key key);
int buttonToCode(sf::Mouse::Button button);
std::string GetName(int code);
}
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/binds.cpp" 2





namespace binds
{

int Pause = sf::Keyboard::Key::Escape + 1;
int Fullscreen = sf::Keyboard::Key::F11 + 1;
int Pan = -(sf::Mouse::Button::Right + 1);
int UseTool = -(sf::Mouse::Button::Left + 1);
int Tool1 = sf::Keyboard::Key::Num1 + 1;
int Tool2 = sf::Keyboard::Key::Num2 + 1;
int Tool3 = sf::Keyboard::Key::Num3 + 1;
int RotateStructure = sf::Keyboard::Key::R + 1;
int CloseInventory = sf::Keyboard::Key::E + 1;
int FlipStructure = sf::Keyboard::Key::F + 1;
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
  case 1: ret = "A"; break;
  case 2: ret = "B"; break;
  case 3: ret = "C"; break;
  case 4: ret = "D"; break;
  case 5: ret = "E"; break;
  case 6: ret = "F"; break;
  case 7: ret = "G"; break;
  case 8: ret = "H"; break;
  case 9: ret = "I"; break;
  case 10: ret = "J"; break;
  case 11: ret = "K"; break;
  case 12: ret = "L"; break;
  case 13: ret = "M"; break;
  case 14: ret = "N"; break;
  case 15: ret = "O"; break;
  case 16: ret = "P"; break;
  case 17: ret = "Q"; break;
  case 18: ret = "R"; break;
  case 19: ret = "S"; break;
  case 20: ret = "T"; break;
  case 21: ret = "U"; break;
  case 22: ret = "V"; break;
  case 23: ret = "W"; break;
  case 24: ret = "X"; break;
  case 25: ret = "Y"; break;
  case 26: ret = "Z"; break;
  case 27: ret = "0"; break;
  case 28: ret = "1"; break;
  case 29: ret = "2"; break;
  case 30: ret = "3"; break;
  case 31: ret = "4"; break;
  case 32: ret = "5"; break;
  case 33: ret = "6"; break;
  case 34: ret = "7"; break;
  case 35: ret = "8"; break;
  case 36: ret = "9"; break;
  case 37: ret = "Escape"; break;
  case 38: ret = "Left Control"; break;
  case 39: ret = "Left Shift"; break;
  case 40: ret = "Left Alt"; break;
  case 41: ret = "Left System"; break;
  case 42: ret = "Right Control"; break;
  case 43: ret = "Right Shift"; break;
  case 44: ret = "Right Alt"; break;
  case 45: ret = "Right System"; break;
  case 46: ret = "Menu"; break;
  case 47: ret = "["; break;
  case 48: ret = "]"; break;
  case 49: ret = ";"; break;
  case 50: ret = ","; break;
  case 51: ret = "."; break;
  case 52: ret = "'"; break;
  case 53: ret = "/"; break;
  case 54: ret = "\\"; break;
  case 55: ret = "~"; break;
  case 56: ret = "="; break;
  case 57: ret = "-"; break;
  case 58: ret = "Space"; break;
  case 59: ret = "Enter"; break;
  case 60: ret = "Backspace"; break;
  case 61: ret = "Tab"; break;
  case 62: ret = "Page Up"; break;
  case 63: ret = "Page Down"; break;
  case 64: ret = "End"; break;
  case 65: ret = "Home"; break;
  case 66: ret = "Insert"; break;
  case 67: ret = "Delete"; break;
  case 68: ret = "+"; break;
  case 69: ret = "-"; break;
  case 70: ret = "*"; break;
  case 71: ret = "/"; break;
  case 72: ret = "Left Arrow"; break;
  case 73: ret = "Right Arrow"; break;
  case 74: ret = "Up Arrow"; break;
  case 75: ret = "Down Arrow"; break;
  case 76: ret = "Numpad 0"; break;
  case 77: ret = "Numpad 1"; break;
  case 78: ret = "Numpad 2"; break;
  case 79: ret = "Numpad 3"; break;
  case 80: ret = "Numpad 4"; break;
  case 81: ret = "Numpad 5"; break;
  case 82: ret = "Numpad 6"; break;
  case 83: ret = "Numpad 7"; break;
  case 84: ret = "Numpad 8"; break;
  case 85: ret = "Numpad 9"; break;
  case 86: ret = "F1"; break;
  case 87: ret = "F2"; break;
  case 88: ret = "F3"; break;
  case 89: ret = "F4"; break;
  case 90: ret = "F5"; break;
  case 91: ret = "F6"; break;
  case 92: ret = "F7"; break;
  case 93: ret = "F8"; break;
  case 94: ret = "F9"; break;
  case 95: ret = "F10"; break;
  case 96: ret = "F11"; break;
  case 97: ret = "F12"; break;
  case 98: ret = "F13"; break;
  case 99: ret = "F14"; break;
  case 100: ret = "F15"; break;
  case 101: ret = "Pause"; break;
  case -1: ret = "Left Mouse Button"; break;
  case -2: ret = "Right Mouse Button"; break;
  case -3: ret = "Middle Mouse Button"; break;
 }
 return ret;
}
