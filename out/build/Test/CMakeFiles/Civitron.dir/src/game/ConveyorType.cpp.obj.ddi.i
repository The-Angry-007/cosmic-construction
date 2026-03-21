# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Structure.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Structure.hpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Structure.hpp" 2
class Recipe;
struct RecipeData;
class Structure
{
public:
 int typeID;
 int id;
 int chunkID = -1;
 int planetID;
 int zindex;
 bool blocksItems;
 Recipe* recipe = nullptr;
 bool placedByPlayer;
 bool isConveyor = false;
 bool isTerrain = false;
 bool isFlipped = false;
 sf::Vector2i bottomRightPos;
 sf::Vector2i position;
 sf::Vector2i tileSize;
 sf::Sprite sprite;
 int direction = 0;
 Hitbox* hitbox;
 Structure();
 virtual void Update(float dt);
 virtual void UpdateNeighbours();
 virtual void Render();
 virtual void SetPosition(sf::Vector2i position);
 void SetID(int id);
 virtual JSON ToJSON();
 virtual void SetVisualPosition(sf::Vector2i pos);
 virtual void FromJSON();
 virtual void RenderPreview();
 virtual void Interact();
 virtual void TryAddGroundItem(int index);
 virtual bool TryAddItem(int index);
 virtual void Destroy();
 virtual void SetDirection(int direction);
 virtual void SetRecipe(RecipeData* data);
 virtual void SetFlipped(bool flipped);

 bool CanBePlaced();
 virtual ~Structure();
};

extern int CurrentStructureID;
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.hpp" 2
class ConveyorType : public Structure
{
public:
 float gap;
 float speed;
 int upgradeLevel = 0;
 ConveyorType();
 ~ConveyorType();
 virtual void Progress(float dt);
 virtual void TryAdd();
 virtual void KeepDistance();
 virtual bool TryAddItem(int index, int direction, float progress);
 virtual float Distance(int direction);
 virtual bool CanAddItem(int direction, float progress);
 virtual bool AcceptsItems(int direction);
 virtual void SetUpgradeLevel(int level);
};
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.cpp" 2



ConveyorType::ConveyorType()
{}
ConveyorType::~ConveyorType()
{}
bool ConveyorType::TryAddItem(int index, int direction, float progress)
{
 return false;
}
bool ConveyorType::CanAddItem(int direction, float progress)
{
 return false;
}
float ConveyorType::Distance(int direction)
{
 return 0.f;
}

bool ConveyorType::AcceptsItems(int direction)
{
 return false;
}


void ConveyorType::SetUpgradeLevel(int level)
{
 upgradeLevel = level;
 if (upgradeLevel == 0)
 {
  speed = 3.f;
 }
 else if (upgradeLevel == 1)
 {
  speed = 6.f;
 }
}

void ConveyorType::Progress(float dt)
{}
void ConveyorType::TryAdd()
{}
void ConveyorType::KeepDistance()
{}
