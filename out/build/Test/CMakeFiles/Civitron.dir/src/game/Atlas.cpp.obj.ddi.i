# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving/SaveHandler.hpp" 1
       


namespace SaveHandler
{
extern std::string workingDir;
extern int startTime;
extern sf::Clock saveTimer;

void Init();
void CreateSave(std::string name, int difficulty, std::string seed);
void LoadGame(int index);
void SaveGame();
bool DirExists(std::string path);
bool CreateDirectory(std::string path);
void UpdateTimePlayed();
void UpdateLastModified();
std::string ReadData(std::string path);
void WriteData(std::string path, std::string string);
std::vector<std::string> ListFiles(std::string path);
std::vector<std::string> ListDirectories(std::string path);
std::string RelToAbsolute(std::string path);
int GetTime();
void ResetWorkingDir();
bool DeleteDirectory(std::string& path);
uint64_t HashFromString(std::string& str);

std::string JSONsToString(std::vector<JSON> jsons);
std::vector<JSON> StringToJSONs(std::string string);
}
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving.hpp" 2
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
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/saving.hpp" 2
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.hpp" 2

class Atlas
{
public:
 sf::Texture texture;
 std::vector<sf::Texture> textures;
 std::vector<sf::Vector2i> positions;
 std::vector<int> idPoses;
 Atlas(std::vector<sf::Texture>& textures);
 Atlas(std::vector<sf::Texture>& textures, std::vector<int> ids);
 void SetSprite(sf::Sprite& sprite, int id);
 void SetSprite(sf::Sprite& sprite, int id, int frameNum);
};
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ResourceHandler.hpp" 1
       


# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Item.hpp" 1
       


# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Hitboxes.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/Hitbox.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxShape.hpp" 1
       
class HitboxShape
{
public:
 sf::Vector2f position;
 sf::Vector2f size;
 sf::Vector2f currentPos;
 sf::Vector2f currentSize;
 int index;

 ~HitboxShape();
 HitboxShape();
 void SetTransform(sf::Vector2f position, sf::Vector2f size);
 void ResetTransform();
 virtual bool intersects(HitboxShape* other);
 virtual void Display(bool colliding);
 virtual bool intersectsPoint(sf::Vector2f point);
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/Hitbox.hpp" 2
class Hitbox
{
public:
 std::vector<HitboxShape*> shapes;
 sf::Vector2f position;
 sf::Vector2f size;
 sf::Vector2f currentPos;
 sf::Vector2f currentSize;

 Hitbox(sf::Vector2f position, sf::Vector2f size);
 virtual ~Hitbox();
 void AddShape(HitboxShape* shape);
 void SetTransform(sf::Vector2f position, sf::Vector2f size);
 void ResetTransform();
 bool intersects(Hitbox* other);
 virtual bool intersectsPoint(sf::Vector2f point);


 void Display(std::vector<Hitbox*> hitboxes);
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Hitboxes.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxCircle.hpp" 1
       


class HitboxCircle : public HitboxShape
{
public:
 HitboxCircle(sf::Vector2f position, float radius);
 ~HitboxCircle();
 bool intersects(HitboxShape* other);
 bool intersectsPoint(sf::Vector2f point);

 void Display(bool colliding);
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Hitboxes.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxRect.hpp" 1
       


class HitboxRect : public HitboxShape
{
public:
 HitboxRect(sf::Vector2f position, sf::Vector2f size);
 ~HitboxRect();
 bool intersects(HitboxShape* other);
 bool intersectsPoint(sf::Vector2f point);


 void Display(bool colliding);
};
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Hitboxes.hpp" 2
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Item.hpp" 2

class Planet;
class Item
{
public:
 sf::Vector2f position;
 int typeId;
 int id;
 int chunkID;
 sf::Sprite sprite;
 sf::Vector2f moveDir;
 Hitbox* hitbox;
 Hitbox* accurateHitbox;
 int parent;
 int zindex;
 bool isDeleted = false;

 Item(sf::Vector2f position, int id, int typeID);

 Item();
 void SetType(int typeID);
 void SetParent(int index);
 void Update(float dt, Planet* planet);
 void Render(Planet* planet);
 sf::Vector2i GetTilePos();
};
extern int CurrentItemID;
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ResourceHandler.hpp" 2
namespace ResourceHandler
{
extern std::vector<sf::Texture> itemTextures;
extern std::vector<sf::Texture> itemOutlines;
extern std::vector<sf::Texture> structureTextures;
extern std::vector<sf::Vector2i> structureSizes;
extern std::vector<sf::Texture> structureOutlines;
extern std::vector<std::vector<int>> structureCosts;
extern Atlas* completeAtlas;
extern Atlas* itemAtlas;
extern Atlas* structureAtlas;
extern Table* itemTable;
extern Table* structureTable;
extern int numItems;
extern int numStructures;
extern int numStructureTextures;
void Init();
std::vector<int> GetCost(int structureID);
sf::Texture GenerateOutline(sf::Texture& texture);
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.cpp" 2

Atlas::Atlas(std::vector<sf::Texture>& textures)
{
 positions = {};
 int rowHeight = 0;
 int rowWidth = 0;
 int totalWidth = 0;
 int totalHeight = 0;
 int maxSize = sf::Texture::getMaximumSize();

 for (uint i = 0; i < textures.size(); i++)
 {

  int newWidth = rowWidth + textures[i].getSize().x;

  if (newWidth > maxSize)
  {
   totalHeight += rowHeight;
   rowHeight = 0;
   rowWidth = 0;
  }

  if (newWidth > totalWidth)
  {
   totalWidth = newWidth;
  }

  if (textures[i].getSize().y > rowHeight)
  {
   rowHeight = textures[i].getSize().y;
  }

  positions.push_back(sf::Vector2i(rowWidth, totalHeight));
  rowWidth += textures[i].getSize().x;
 }

 totalHeight += rowHeight;
 sf::Image im;

 im.create(totalWidth, totalHeight);
 for (uint i = 0; i < textures.size(); i++)
 {
  auto i2 = textures[i].copyToImage();
  im.copy(i2, positions[i].x, positions[i].y);
 }

 texture.loadFromImage(im);
 this->textures = textures;
}

Atlas::Atlas(std::vector<sf::Texture>& textures, std::vector<int> ids)
{
 positions = {};
 idPoses = {};
 int currentID = -1;

 for (int i = 0; i < ids.size(); i++)
 {
  if (ids[i] != currentID)
  {
   currentID = ids[i];
   idPoses.push_back(i);
  }
 }

 int rowHeight = 0;
 int rowWidth = 0;
 int totalWidth = 0;
 int totalHeight = 0;
 int maxSize = sf::Texture::getMaximumSize();

 for (uint i = 0; i < textures.size(); i++)
 {

  int newWidth = rowWidth + textures[i].getSize().x;

  if (newWidth > maxSize)
  {
   totalHeight += rowHeight;
   rowHeight = 0;
   rowWidth = 0;
  }

  if (newWidth > totalWidth)
  {
   totalWidth = newWidth;
  }

  if (textures[i].getSize().y > rowHeight)
  {
   rowHeight = textures[i].getSize().y;
  }

  positions.push_back(sf::Vector2i(rowWidth, totalHeight));
  rowWidth += textures[i].getSize().x;
 }

 totalHeight += rowHeight;
 sf::Image im;

 im.create(totalWidth, totalHeight);
 for (uint i = 0; i < textures.size(); i++)
 {
  auto i2 = textures[i].copyToImage();
  im.copy(i2, positions[i].x, positions[i].y);
 }

 texture.loadFromImage(im);
 this->textures = textures;
}

void Atlas::SetSprite(sf::Sprite& sprite, int id, int frameNum)
{

 if (ResourceHandler::structureAtlas == this)
 {
  ResourceHandler::completeAtlas->SetSprite(sprite, id + 2 * ResourceHandler::numItems, frameNum);
  return;
 }

 int index = idPoses[id] + frameNum;
 sprite.setTexture(texture);
 sprite.setTextureRect(sf::IntRect(positions[index], (sf::Vector2i)textures[index].getSize()));
 sprite.setOrigin((sf::Vector2f)(textures[index].getSize()) / 2.f);
}

void Atlas::SetSprite(sf::Sprite& sprite, int id)
{

 ResourceHandler::completeAtlas->SetSprite(sprite, id, 0);
}
