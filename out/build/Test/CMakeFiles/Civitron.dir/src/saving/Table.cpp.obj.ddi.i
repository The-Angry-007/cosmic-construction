# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/Table.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/Table.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/Table.hpp" 1
       

class Table
{
public:
 std::vector<std::string> headers;
 std::vector<std::vector<std::string>> records;

 Table();
 void FromString(std::string string);
 std::string GetValue(int column, int row);
 std::string GetValue(std::string header, int row);
 std::string ToString();
};
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/Table.cpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/Table.cpp" 2
Table::Table()
{
 headers = {};
 records = {};
}

void Table::FromString(std::string string)
{
 auto lines = Split(string, '\n');
 headers = Split(lines[0], '/');
 for (uint i = 1; i < lines.size(); i++)
 {
  records.push_back(Split(lines[i], '/'));
 }
}

std::string Table::GetValue(int column, int row)
{
 if (row > records.size() || column > headers.size())
 {
  return "out of bounds";
 }
 return records[row][column];
}

std::string Table::GetValue(std::string header, int row)
{
 for (uint i = 0; i < headers.size(); i++)
 {
  if (headers[i] == header)
  {
   return records[row][i];
  }
 }
 return "data not found";
}

std::string Table::ToString()
{
 std::string result = "";
 for (uint i = 0; i < headers.size(); i++)
 {
  result += headers[i];
  if (i != headers.size() - 1)
  {
   result += "/";
  }
 }
 result += "\n";
 for (uint i = 0; i < records.size(); i++)
 {
  for (uint j = 0; j < records[i].size(); j++)
  {
   result += records[i][j];
   if (j != records[i].size() - 1)
   {
    result += "/";
   }
  }
  if (i != records.size() - 1)
  {
   result += "\n";
  }
 }
 return result;
}
