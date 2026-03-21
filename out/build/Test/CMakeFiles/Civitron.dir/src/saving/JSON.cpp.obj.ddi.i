# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/JSON.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/JSON.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/JSON.hpp" 1
       

class JSON
{
public:
 std::vector<std::string> keywords;
 std::vector<std::string> values;

 JSON();
 std::string GetValue(std::string keyword);
 void AddAttribute(std::string keyword, int value);
 void AddAttribute(std::string keyword, std::vector<int> values);
 void AddAttribute(std::string keyword, std::vector<float> values);
 void AddAttribute(std::string keyword, float value);
 void AddAttribute(std::string keyword, sf::Vector2f value);
 void AddAttribute(std::string keyword, sf::Vector2i value);
 int GetInt(std::string keyword);
 float GetFloat(std::string keyword);
 sf::Vector2f GetV2f(std::string keyword);
 sf::Vector2i GetV2i(std::string keyword);
 std::vector<int> GetIntArr(std::string keyword);
 std::vector<float> GetFloatArr(std::string keyword);
 std::vector<bool> GetBoolArr(std::string keyword);
 void AddAttribute(std::string keyword, std::string value);
 void AddJSON(JSON j);






 void FromString(std::string data);
 std::string ToString();

 void Print();
};
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/JSON.cpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/JSON.cpp" 2

JSON::JSON()
{
 keywords = {};
 values = {};
}

std::string JSON::GetValue(std::string keyword)
{
 for (uint i = 0; i < keywords.size(); i++)
 {
  if (keywords[i] == keyword)
  {
   return values[i];
  }
 }
 std::cout << "could not find " << keyword << std::endl;
 return "not in list";
}

void JSON::AddAttribute(std::string keyword, std::string value)
{
 keywords.push_back(keyword);
 values.push_back(value);
}
void JSON::AddAttribute(std::string keyword, int value)
{
 keywords.push_back(keyword);
 values.push_back(std::to_string(value));
}
void JSON::AddAttribute(std::string keyword, float value)
{
 keywords.push_back(keyword);
 values.push_back(std::to_string(value));
}
void JSON::AddAttribute(std::string keyword, sf::Vector2f value)
{
 AddAttribute(keyword + "X", value.x);
 AddAttribute(keyword + "Y", value.y);
}
void JSON::AddAttribute(std::string keyword, sf::Vector2i value)
{
 AddAttribute(keyword + "X", value.x);
 AddAttribute(keyword + "Y", value.y);
}
int JSON::GetInt(std::string keyword)
{
 return std::stoi(GetValue(keyword));
}
float JSON::GetFloat(std::string keyword)
{
 return std::stof(GetValue(keyword));
}
sf::Vector2f JSON::GetV2f(std::string keyword)
{
 return sf::Vector2f(
  GetFloat(keyword + "X"),
  GetFloat(keyword + "Y"));
}
sf::Vector2i JSON::GetV2i(std::string keyword)
{
 return sf::Vector2i(
  GetInt(keyword + "X"),
  GetInt(keyword + "Y"));
}
void JSON::FromString(std::string data)
{

 int index = 2;
 while (data[index] != '}')
 {
  std::string keyword = "";
  while (data[index] != ':')
  {
   keyword += data[index];
   index++;
  }
  index++;
  std::string value = "";
  while (data[index] != '\n')
  {
   value += data[index];
   index++;
  }
  AddAttribute(keyword, value);
  index++;
 }
}

std::string JSON::ToString()
{
 std::string s = "{\n";
 for (uint i = 0; i < keywords.size(); i++)
 {
  s += keywords[i] + ":" + values[i] + "\n";
 }
 s += "}";
 return s;
}

void JSON::Print()
{
 std::cout << "Keywords: [";
 for (uint i = 0; i < keywords.size(); i++)
 {
  std::cout << keywords[i];
  if (i != keywords.size() - 1)
  {
   std::cout << ",";
  }
 }
 std::cout << "]\nValues: [";
 for (uint i = 0; i < values.size(); i++)
 {
  std::cout << values[i];
  if (i != values.size() - 1)
  {
   std::cout << ",";
  }
 }
 std::cout << "]";
}

std::vector<int> JSON::GetIntArr(std::string keyword)
{
 std::string val = GetValue(keyword);
 if (val.size() == 0)
 {
  return {};
 }
 std::vector<std::string> vals = Split(val, ',');
 std::vector<int> intVals = {};
 for (int i = 0; i < vals.size(); i++)
 {
  intVals.push_back(std::stoi(vals[i]));
 }
 return intVals;
}

std::vector<float> JSON::GetFloatArr(std::string keyword)
{
 std::string val = GetValue(keyword);
 if (val.size() == 0)
 {
  return {};
 }
 std::vector<std::string> vals = Split(val, ',');
 std::vector<float> floatVals = {};
 for (int i = 0; i < vals.size(); i++)
 {
  floatVals.push_back(std::stof(vals[i]));
 }
 return floatVals;
}

std::vector<bool> JSON::GetBoolArr(std::string keyword)
{
 std::string val = GetValue(keyword);
 if (val.size() == 0)
 {
  return {};
 }
 std::vector<std::string> vals = Split(val, ',');
 std::vector<bool> boolVals = {};
 for (int i = 0; i < vals.size(); i++)
 {
  boolVals.push_back(std::stoi(vals[i]));
 }
 return boolVals;
}

void JSON::AddAttribute(std::string keyword, std::vector<int> values)
{
 std::string val = "";
 for (int i = 0; i < values.size(); i++)
 {
  val += std::to_string(values[i]);
  if (i != values.size() - 1)
  {
   val += ",";
  }
 }
 AddAttribute(keyword, val);
}
void JSON::AddAttribute(std::string keyword, std::vector<float> values)
{
 std::string val = "";
 for (int i = 0; i < values.size(); i++)
 {
  val += std::to_string(values[i]);
  if (i != values.size() - 1)
  {
   val += ",";
  }
 }
 AddAttribute(keyword, val);
}

void JSON::AddJSON(JSON j)
{
 for (int i = 0; i < j.keywords.size(); i++)
 {
  AddAttribute(j.keywords[i], j.values[i]);
 }
}
