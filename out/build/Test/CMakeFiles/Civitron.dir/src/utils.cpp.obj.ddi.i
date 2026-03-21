# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/utils.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/utils.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/utils.hpp" 1
       

extern bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2);
extern bool RectIntersectsRect(sf::IntRect rect1, sf::IntRect rect2);
extern bool RectIntersectsCircle(sf::Vector2f pos, float r, sf::FloatRect rect);
extern bool CircleIntersectsCircle(sf::Vector2f pos1, float r1, sf::Vector2f pos2, float r2);
float clamp(float val, float min, float max);
extern float Lerp(float a, float b, float t);
extern sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t);
extern std::vector<std::string> Split(std::string string, char chr);
extern std::string concat(std::vector<std::string> lines);
extern void Print(std::vector<std::string> arr);
extern void Print(std::vector<std::vector<std::string>> arr);
extern sf::Color Lerp(sf::Color a, sf::Color b, float t);
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/utils.cpp" 2

bool RectIntersectsRect(sf::FloatRect rect1, sf::FloatRect rect2)
{


 bool cond1 = (rect2.left > rect1.left + rect1.width);

 bool cond2 = (rect2.left + rect2.width < rect1.left);

 bool cond3 = (rect2.top > rect1.top + rect1.height);

 bool cond4 = (rect2.top + rect2.height < rect1.top);

 if (!(cond1 || cond2 || cond3 || cond4))
 {
  return true;
 }

 return false;
}

bool RectIntersectsRect(sf::IntRect rect1, sf::IntRect rect2)
{


 bool cond1 = (rect2.left >= rect1.left + rect1.width);

 bool cond2 = (rect2.left + rect2.width <= rect1.left);

 bool cond3 = (rect2.top >= rect1.top + rect1.height);

 bool cond4 = (rect2.top + rect2.height <= rect1.top);

 if (!(cond1 || cond2 || cond3 || cond4))
 {
  return true;
 }

 return false;
}

bool RectIntersectsCircle(sf::Vector2f pos, float r, sf::FloatRect rect)
{

 float closestX = clamp(pos.x, rect.left, rect.left + rect.width);
 float closestY = clamp(pos.y, rect.top, rect.top + rect.height);

 float dx = pos.x - closestX;
 float dy = pos.y - closestY;

 float mag = dx * dx + dy * dy;


 if (mag < r * r)
 {
  return true;
 }

 return false;
}

bool CircleIntersectsCircle(sf::Vector2f pos1, float r1, sf::Vector2f pos2, float r2)
{

 sf::Vector2f d = pos2 - pos1;

 float mag = d.x * d.x + d.y * d.y;

 float rmax = r1 + r2;

 if (mag < rmax * rmax)
 {

  return true;
 }

 return false;
}



float clamp(float val, float min, float max)
{
 if (val < min)
 {
  return min;
 }
 if (val > max)
 {
  return max;
 }
 return val;
}




float Lerp(float a, float b, float t)
{
 return a + (b - a) * t;
}

sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t)
{
 return a + (b - a) * t;
}

std::vector<std::string> Split(std::string string, char chr)
{

 std::vector<std::string> split = {};

 std::string current = "";
 int i = 0;

 while (i < string.length())
 {

  if (string[i] == chr)
  {
   split.push_back(current);
   current = "";
  }

  else
  {
   current += string[i];
  }
  i++;
 }

 split.push_back(current);
 return split;
}

std::string concat(std::vector<std::string> lines)
{
 std::string result = "";
 for (uint i = 0; i < lines.size(); i++)
 {
  result += lines[i];
  if (i != lines.size() - 1)
  {
   result += '\n';
  }
 }
 return result;
}

sf::Color Lerp(sf::Color a, sf::Color b, float t)
{
 return sf::Color(
  (uint8_t)Lerp(a.r, b.r, t),
  (uint8_t)Lerp(a.g, b.g, t),
  (uint8_t)Lerp(a.b, b.b, t),
  (uint8_t)Lerp(a.a, b.a, t));
}
