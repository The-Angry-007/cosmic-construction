# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/ClickFuncs.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIObject.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIObject.hpp" 2
class GUIObject
{
public:
 sf::Vector2f position;
 sf::Vector2f size;
 Hitbox* hitbox;
 bool blocksMouseInput;

 virtual bool isBlockingMouse();
 virtual bool isClicked();
 virtual void Update(float dt);
 virtual void Render();
 virtual void RenderToTexture(sf::RenderTexture* texture);
 GUIObject();
 virtual ~GUIObject();
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.hpp" 2
class GUIButton : public GUIObject
{
public:
 GUIObject* bgObj;
 GUIObject* labelObj;
 GUIObject* dimObj;

 std::function<void()> clickFunc;

 GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj);
 ~GUIButton();
 void Render();
 void Update(float dt);
 bool isClicked();
 bool isBlockingMouse();
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/ClickFuncs.hpp" 2
namespace ClickFuncs
{
void blankFunc();
void OpenNewGame();
void OpenLoadGame();
void OpenSettings();
void OpenHelp();
void CreateSave();
void ResumeGame();
void OpenSettingsInGame();
void SaveAndQuit();
void ResetCamPos();
}
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.hpp" 1
       

class GUI
{
public:
 std::vector<GUIObject*> GUIObjects;

 virtual void Render();
 virtual void Update(float dt);
 void AddObject(GUIObject* object);
 void InsertObject(GUIObject* object, int index);
 int GetIndex(GUIObject* object);
 void RemoveObject(int index);
 void RenderToTexture(sf::RenderTexture* text);
 GUI();
 ~GUI();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUICheckbox.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIImage.hpp" 1
       


class GUIImage : public GUIObject
{
public:
 sf::Texture texture;
 sf::Sprite sprite;
 bool keepAspectRatio;
 sf::Vector2f origin;
 GUIImage(sf::Vector2f position, sf::Vector2f size, std::string path);
 ~GUIImage();
 void Render();
 void RenderToTexture(sf::RenderTexture* texture);
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUICheckbox.hpp" 2

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIPanel.hpp" 1
       

class GUIPanel : public GUIObject
{
public:
 sf::Color color;
 sf::RectangleShape rect;
 bool keepAspectRatio;
 float ratio;

 void SetColor(sf::Color color);
 void Render();
 void RenderToTexture(sf::RenderTexture* texture);
 void Update(float dt);
 GUIPanel(sf::Vector2f position, sf::Vector2f size, sf::Color color);
 ~GUIPanel();
};
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUICheckbox.hpp" 2

class GUICheckbox : public GUIObject
{
public:
 bool checked;
 GUIImage* checkImage;
 GUIPanel* bgObj;
 std::vector<GUICheckbox*> exclusives;

 GUICheckbox(sf::Vector2f position, sf::Vector2f size, sf::Color col);
 void Update(float dt);
 void Render();
};
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIGalaxy.hpp" 1
       



class GUIGalaxy : public GUIObject
{
public:
 sf::Texture texture;
 sf::Sprite sprite;
 float speed;
 sf::Vector2f vel;

 void Update(float dt);
 void Render();
 GUIGalaxy();
};
# 7 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIHandler.hpp" 1
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUILabel.hpp" 1
       

class GUILabel : public GUIObject
{
public:
 sf::Font font;
 std::string value;
 sf::Color color;
 sf::Vector2f origin;
 sf::Text text;
 bool altCharSize;
 ~GUILabel();
 GUILabel(sf::Vector2f position, sf::Vector2f size, std::string text);
 void SetColor(sf::Color color);
 void Render();
 void RenderToTexture(sf::RenderTexture* texture);
 void DoWrapping(int charsPerLine);
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIHandler.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.hpp" 1
       



class Settings : public GUI
{
public:

 GUI* behindGUI;

 GUI* bgGUI;
 std::string saveDir;
 std::vector<GUI*> pageGuis;
 int currentGUI;
 float masterVolume;
 float musicVolume;
 float effectsVolume;

 int framerate;
 int saveInterval;


 Settings();
 ~Settings();
 void Update(float dt);
 void SaveSettings();
 void LoadSettings();
 void Render();
 int selectedBind;
 std::vector<int*> bindCodes;
 std::vector<GUI*> bindGUIs;
 void AddBind(std::string label, int* value);
 void ExitSettings();
};
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIHandler.hpp" 2
class GUIHandler
{
public:
 std::vector<GUI*> guis;
 int activeGui;
 std::vector<int> openedGuis;

 Settings* settings;
 GUILabel* fpsLabel;
 GUIPanel* itemNameBG;
 GUILabel* itemName;
 int fps;
 std::vector<sf::Vector2f> toolPoses;
 int numTools;
 int numGUIs;
 sf::Font guifont;

 GUIHandler();


 void OpenGUI(int GUI);
 void GoBack();
 void AddGUI(GUI* gui);
 void Update(float dt);
 void Render();

 void InitGUIS();
 GUI* GetOpenGUI();
};
# 8 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.hpp" 1
       



class GUIInputField : public GUIObject
{
public:
 std::string value;
 std::string displayValue;
 bool changed;
 int cursorPos;
 bool focused;
 GUILabel* label;

 void SetTextCol(sf::Color color);
 GUIInputField(sf::Vector2f position, sf::Vector2f size);
 ~GUIInputField();
 void Update(float dt);
 void Render();
};
# 10 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2



# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUISaveSlot.hpp" 1
       





class GUISaveSlot : public GUIObject
{
public:
 GUIPanel* bgObj;
 GUILabel* nameLabel;
 GUILabel* playtimeLabel;
 GUILabel* modifiedLabel;
 GUIImage* deleteBG;
 GUIImage* deleteIcon;
 std::string path;
 GUISaveSlot(sf::Vector2f position, std::string path);
 void Update(float dt);
 void Move(float amt);
 void RenderToTexture(sf::RenderTexture* texture);
 ~GUISaveSlot();
};
# 14 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUISlider.hpp" 1
       


class GUISlider : public GUIObject
{
public:

 GUIObject* knob;

 GUIObject* background;

 GUIObject* completion;

 float value;
 bool selected;
 int numSteps;
 float minVal;
 float maxVal;

 float pValue;

 void Update(float dt);
 void Render();
 void AdjustFromVal();
 GUISlider(sf::Vector2f position, sf::Vector2f size, GUIObject* knob, GUIObject* background, GUIObject* completion);
 ~GUISlider();
};
# 15 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/LoadGame.hpp" 1
       


class LoadGame : public GUI
{
public:
 std::vector<GUISaveSlot*> saveSlots;
 LoadGame(GUIGalaxy* galaxy, GUIPanel* dimpanel);
 void Update(float dt);
 void Reload();
 void Render();
};
# 16 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/SiloMenu.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/StorageSilo.hpp" 1
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Structure.hpp" 1
       

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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/StorageSilo.hpp" 2
class StorageSilo : public Structure
{
public:
 std::vector<int> itemIDs;
 std::vector<int> itemQuantities;
 std::vector<int> inputNeighbours;
 std::vector<int> outputNeighbours;
 std::vector<int> previousOutputs;
 std::vector<sf::Sprite> sprites;
 StorageSilo(int id, int planetID, int direction = 0);
 ~StorageSilo();
 void SetPosition(sf::Vector2i pos);
 void SetVisualPosition(sf::Vector2i pos);
 void TryAddGroundItem(int index);
 bool TryAddItem(int index);
 void UpdateNeighbours();
 void Update(float dt);
 void Render();
 JSON ToJSON();
 void FromJSON(JSON j);
 void RenderPreview();
 void Interact();
 void Destroy();
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/SiloMenu.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIItem.hpp" 1
       




class GUIItem : public GUIObject
{
public:
 int typeID;
 sf::Vector2f actualSize;
 int amount;
 GUIImage* image;
 GUILabel* label;
 GUILabel* nameLabel;
 GUIPanel* nameBG;
 GUIItem(sf::Vector2f position, sf::Vector2f size, int typeID, int amount);
 ~GUIItem();
 void Update(float dt);
 void RenderToTexture(sf::RenderTexture* texture);
 void Render();
 void SetAmount(int amount);
 bool isClicked();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/SiloMenu.hpp" 2

class StorageSilo;
class SiloMenu : public GUI
{
public:
 StorageSilo* silo;
 SiloMenu(StorageSilo* s);
 ~SiloMenu();
 std::vector<GUIItem*> items;
 void Update(float dt);
 void Render();
};
# 18 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 2
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.hpp" 2

struct RecipeData
{
 std::vector<int> inputTypes;
 std::vector<int> inputAmounts;
 std::vector<bool> isFuels;
 std::vector<float> fuelLengths;
 std::vector<int> outputTypes;
 std::vector<int> outputAmounts;
 float craftTime;
 int id;
};
namespace RecipeHandler
{

extern std::vector<std::vector<RecipeData>> recipes;
extern GUI* gui;
extern int guiStructure;
extern int numBgObjs;
void Update(float dt);
void InitGUI(int structure);
void LoadRecipes(std::vector<JSON> jsons);
RecipeData* GetRecipe(int id);

};
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Main.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Atlas.hpp" 1
       


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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Camera.hpp" 1
       


class Camera
{
public:
 sf::Vector2f position;
 sf::Vector2f mouseStartPos;
 sf::Vector2f cameraStartPos;
 float zoom;
 float targetZoom;
 float zoomRate;
 float zoomSpeed;
 float moveSpeed;
 sf::Vector2f prevMousePos;
 Hitbox* hitbox;
 ~Camera();
 Camera();
 Camera(sf::Vector2f position, float zoom);
 void Update(float dt);
 void SetView();
 sf::Vector2f WorldMousePos();
 sf::Vector2f tileToGUIPos(sf::Vector2f tilePos);
 sf::FloatRect toFloatRect();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Chunk.hpp" 1
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Item.hpp" 1
       



# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ResourceHandler.hpp" 1
       



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
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Item.hpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Chunk.hpp" 2


const int CHUNK_SIZE = 32;
const sf::Vector2i TILE_SIZE(32, 32);
const sf::Vector2i CHUNK_SIZE_PIXELS = CHUNK_SIZE * TILE_SIZE;
class Chunk
{
public:
 sf::Vector2i position;
 int id;
 int planetID;
 std::vector<int> structures;
 std::vector<int> items;
 bool isAltered = false;
 bool isDeleted = false;
 Chunk(sf::Vector2i position, int id, int planetID);
 Chunk();
 void Update(float dt);
 bool isVisible();
 void Render();
 Hitbox* hitbox;

 sf::Vector2f GetWorldPos(sf::Vector2f position);
};
extern int CurrentChunkID;
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Game.hpp" 1
       


# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 1
       




# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RenderObject.hpp" 1
       

struct RenderObject
{
 sf::Sprite* sprite;
 int zindex;
};
bool operator<(const RenderObject& lhs, const RenderObject& rhs);
# 7 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Boulder.hpp" 1
       

class Boulder : public Structure
{
public:
 int health;
 Boulder(int id, int planetID);
 ~Boulder();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void Render();
 void Destroy();
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Conveyor.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ConveyorType.hpp" 1
       

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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Conveyor.hpp" 2
extern std::vector<sf::Vector2i> CONVEYOR_OFFSETS;
class Conveyor : public ConveyorType
{
public:
 int currentNeighbourIndex;
 int neighbour;
 std::vector<std::vector<int>> items;
 std::vector<std::vector<float>> progress;

 float gap;
 Conveyor(int id, int planetID, int direction);
 ~Conveyor();
 void FromJSON(JSON j);
 void Update(float dt);
 void Render();
 void Progress(float dt);
 void TryAdd();
 void KeepDistance();
 void TryAddGroundItem(int index);

 void SetDirection(int direction);

 bool TryAddItem(int index, int direction, float progress);
 bool CanAddItem(int direction, float progress);
 bool AcceptsItems(int direction);
 float Distance(int direction);

 void UpdateNeighbours();
 JSON ToJSON();
 void RenderPreview();
 void Destroy();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Distributor.hpp" 1
       

class Distributor : public ConveyorType
{
public:
 int currentInputIndex;
 int currentOutputIndex;
 std::vector<std::vector<int>> items;
 std::vector<std::vector<float>> progress;
 std::vector<int> neighbours;

 float gap;
 Distributor(int id, int planetID, int direction);
 ~Distributor();
 void Progress(float dt);
 void TryAdd();
 void KeepDistance();
 void FromJSON(JSON j);
 void Update(float dt);
 void Render();
 bool ProgressLane(int lane, float dt, bool moveToMain);
 void TryAddGroundItem(int index);

 void SetDirection(int direction);

 int StructureInFront();
 bool TryAddItem(int index, int direction, float progress);
 bool CanAddItem(int direction, float progress);
 bool AcceptsItems(int direction);
 float Distance(int direction);

 void
 UpdateNeighbours();
 JSON ToJSON();
 void RenderPreview();
 void Destroy();
};
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Drill.hpp" 1
       

class Drill : public Structure
{
public:

 std::vector<int> neighbours;
 int numStone;
 float timeSinceOutput;
 float animProgress;
 float timePerFrame;
 int currentFrame;
 int outputItem;
 int lastOutputDir;
 sf::Sprite groundSprite;
 Drill(int id, int planetID, int direction);
 ~Drill();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void Render();
 void RenderPreview();
 void UpdateNeighbours();
 void SetPosition(sf::Vector2i position);
 void SetVisualPosition(sf::Vector2i position);
 void Interact();
 bool TryAddItem(int index);
 void Destroy();
};
# 7 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.hpp" 1
       

class FilterConveyor : public ConveyorType
{
public:
 float gap;
 int filterItem;
 std::vector<int> neighbours;
 sf::Sprite overlaySprite;
 std::vector<std::vector<int>> items;
 std::vector<std::vector<float>> progress;
 FilterConveyor(int id, int planetID, int direction);
 ~FilterConveyor();
 void SetFlipped(bool flipped);
 void FromJSON(JSON j);
 void Update(float dt);
 void Render();
 void Progress(float dt);
 void TryAdd();
 void KeepDistance();
 void TryAddGroundItem(int index);
 void SetDirection(int direction);
 bool TryAddItem(int index, int direction, float progress);
 bool CanAddItem(int direction, float progress);
 bool AcceptsItems(int direction);
 float Distance(int direction);
 void SetPosition(sf::Vector2i pos);
 void UpdateNeighbours();
 JSON ToJSON();
 void RenderPreview();
 void Destroy();
};
# 8 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeStructure.hpp" 1
       

class RecipeStructure : public Structure
{
public:

 std::vector<int> neighbours;
 int numStone;
 int outputItem;
 int lastOutputDir;
 RecipeStructure(int id, int planetID, int direction, int typeID);
 ~RecipeStructure();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void Render();
 void RenderPreview();
 void UpdateNeighbours();
 void SetPosition(sf::Vector2i position);
 void SetVisualPosition(sf::Vector2i position);
 void Interact();
 bool TryAddItem(int index);
 void Destroy();
};
# 9 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RefinedDrill.hpp" 1
       

class RefinedDrill : public Structure
{
public:

 std::vector<int> neighbours;
 int numStone;
 float timeSinceOutput;
 float animProgress;
 float timePerFrame;
 int currentFrame;
 int outputItem;
 int lastOutputDir;
 sf::Sprite groundSprite;
 RefinedDrill(int id, int planetID, int direction);
 ~RefinedDrill();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void Render();
 void RenderPreview();
 void UpdateNeighbours();
 void SetPosition(sf::Vector2i position);
 void SetVisualPosition(sf::Vector2i position);
 void Interact();
 bool TryAddItem(int index);
 void Destroy();
};
# 10 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RocketSilo.hpp" 1
       

class RocketSilo : public Structure
{
public:
 int launchType;
 float launchTimer;
 int targetPlanetID;
 sf::Sprite rocketSprite;
 RocketSilo(int id, int planetID, int direction, int typeID);
 ~RocketSilo();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void LaunchRocket();
 void Render();
 void RenderPreview();
 void UpdateNeighbours();
 void SetPosition(sf::Vector2i position);
 void SetVisualPosition(sf::Vector2i position);
 void Interact();
 bool TryAddItem(int index);
 void Destroy();
};
# 11 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/SaplingPlanter.hpp" 1
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tree.hpp" 1
       

class Tree : public Structure
{
public:
 int health;
 int parent;
 Tree(int id, int planetID);
 ~Tree();
 void FromJSON(JSON j);
 JSON ToJSON();
 void Update(float dt);
 void Render();
 void Destroy();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/SaplingPlanter.hpp" 2
class SaplingPlanter : public Structure
{
public:
 int tree;
 float timeSinceTree;
 sf::Sprite topSprite;
 SaplingPlanter(int id, int planetID, int direction = 0);
 void Update(float dt);
 void Render();
 void RenderPreview();
 void FromJSON(JSON j);
 JSON ToJSON();
 void SetPosition(sf::Vector2i pos);
};
# 12 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2



# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/TreeChopper.hpp" 1
       

class TreeChopper : public Structure
{
public:
 float timeSinceAction;
 int phase;
 TreeChopper(int id, int planetID, int direction);
 ~TreeChopper();
 void Update(float dt);
 void Render();
 void RenderPreview();
 JSON ToJSON();
 void FromJSON(JSON j);
 void SetDirection(int direction);
};
# 16 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Underground.hpp" 1
       

class Underground : public ConveyorType
{
public:
 std::vector<int> items;
 std::vector<float> progress;
 int length;
 int endBelt;
 int neighbour;
 sf::Vector2i endBeltPos;
 int maxLength;

 float gap;
 Underground(int id, int planetID, int direction);
 ~Underground();
 void Progress(float dt);
 void TryAdd();
 void KeepDistance();
 void FromJSON(JSON j);
 void Update(float dt);
 void Render();
 void SetFlipped(bool flipped);

 void SetDirection(int direction);

 int StructureInFront();
 bool TryAddItem(int index, int direction, float progress);
 bool CanAddItem(int direction, float progress);
 bool AcceptsItems(int direction);
 float Distance(int direction);

 void
 UpdateNeighbours();
 JSON ToJSON();
 void RenderPreview();
 void Destroy();
};
# 17 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/structures.hpp" 2
# 8 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 2
extern void buildVertexArray(const std::vector<RenderObject>& renderObjects);

class Planet
{
public:

 int id;
 std::vector<Item> items;
 std::vector<Chunk> chunks;
 std::vector<int> structuresToUpdate;
 std::vector<Structure*> structures;
 std::vector<int> emptyStructureSlots;
 std::vector<int> emptyChunkSlots;
 std::vector<int> emptyItemSlots;
 Camera camera;
 sf::Color backgroundColor;
 int draggingItem;
 int hoveringItem;
 bool updateNeighbours;
 std::string savePath;
 sf::VertexArray vertexArray;

 std::vector<RenderObject> renderObjects;
 void MoveItem(int index);
 Planet(int id);
 void UpdateNeighbours();
 void Init(bool load);
 void GenerateChunk(sf::Vector2i position);
 void GenerateChunksInView();
 void Update(float dt);
 void Render();
 void Save();
 int StructureInPos(sf::Vector2i position);
 bool StructureInArea(sf::Vector2i position, sf::Vector2i size);
 std::vector<int> StructuresInArea(sf::Vector2i position, sf::Vector2i size);
 Chunk* GetChunk(int chunkID);
 int ChunkAtPos(sf::Vector2f position);
 int ChunkAtPos(sf::Vector2i position);
 sf::Vector2i tilePos(sf::Vector2f position);
 sf::Vector2f worldPos(sf::Vector2f tilePos, int chunkID);
 void WorldUpdate(float dt);
 void AddStructure(Structure* s, bool preserveID = false);
 void AddItem(Item& item);
 void RemoveItem(int item);
 void RemoveStructure(int index);
 bool DeductResources(int typeID, sf::Vector2i position);
 void RemoveStructuresInArea(sf::Vector2i position, sf::Vector2i size);
 std::vector<int> TallyResources(sf::Vector2i position, std::vector<int> types);
};
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Game.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/InputHandler.hpp" 1
       
namespace InputHandler
{



extern std::vector<sf::Keyboard::Key> keysPressed;
extern std::vector<sf::Keyboard::Key> keysDown;
extern std::vector<sf::Keyboard::Key> keysReleased;

extern std::vector<sf::Mouse::Button> mouseButtonsPressed;
extern std::vector<sf::Mouse::Button> mouseButtonsDown;
extern std::vector<sf::Mouse::Button> mouseButtonsReleased;

extern int oldWidth;
extern int oldHeight;
extern bool isFullscreen;


extern sf::Vector2f mousePos;
extern sf::Vector2f guiMP;
extern sf::Vector2f scroll;
extern std::string typedText;
extern bool mouseIsBlocked;

void ProcessEvents();

int getIndex(std::vector<sf::Keyboard::Key> keys, sf::Keyboard::Key key);
int getIndex(std::vector<sf::Mouse::Button> buttons, sf::Mouse::Button button);

bool keyDown(sf::Keyboard::Key key);
bool keyPressed(sf::Keyboard::Key key);
bool keyReleased(sf::Keyboard::Key key);

bool mbDown(sf::Mouse::Button button);
bool mbPressed(sf::Mouse::Button button);
bool mbReleased(sf::Mouse::Button button);

void RemoveKeyDown(sf::Keyboard::Key key);
void RemoveKeyPressed(sf::Keyboard::Key key);
void RemoveKeyReleased(sf::Keyboard::Key key);

void RemoveMbDown(sf::Mouse::Button button);
void RemoveMbPressed(sf::Mouse::Button button);
void RemoveMbReleased(sf::Mouse::Button button);

bool pressed(int code);
bool down(int code);
bool released(int code);

void RemovePressed(int code);
void RemoveDown(int code);
void RemoveReleased(int code);
};
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.hpp" 2


class ToolHandler
{
public:
 int selectedTool;
 int lastPlacedStructure;
 int placeType;
 sf::Vector2i prevTilePos;
 GUIObject* selectedObj;
 std::vector<GUIPanel*> bgObjs;
 std::vector<int> draggingItems;
 Item* hoveringItem;
 sf::Vector2f mouseStartDraggingPos;
 sf::Vector2f itemStartDraggingPos;
 sf::Vector2f structureStartDraggingPos;
 int draggingStructure;
 int placeDir;
 int upgradeLevel = -1;
 bool placingFlipped;
 sf::Vector2f prevmousepos;
 Structure* previewStructure;
 GUILabel* insufficientLabel;
 sf::Clock insufficientTimer;
 std::vector<GUIObject*> tallyObjs;
 std::vector<GUIImage*> selectedImages;
 void ShowSelectArea(sf::Vector2i pos, int width, int height, sf::Color col);
 void ShowInsufficient();
 void ReloadTally(sf::Vector2i tilePos);
 void ClearTally();
 void Update(float dt, Planet* p);
 void Render();
 Structure* CreateStructure(int type);
 ToolHandler();
 ~ToolHandler();
};
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Game.hpp" 2
class Game
{
public:
 bool paused;
 bool inMenu;
 std::vector<Planet> planets;
 int activePlanet;
 int loadedTimer;
 ToolHandler* toolHandler;

 Game();
 ~Game();
 Planet* ActivePlanet();
 void TogglePaused();
 void NewGame();
 void LoadGame();
 void Update(float dt);
 void WorldUpdate(float dt);
 void Render();
};
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 2
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Main.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.hpp" 1
       

class Tutorial
{
public:
 int currentPhase;
 std::vector<std::vector<int>> validCodes;
 std::vector<std::string> script;
 std::vector<bool> skippables;
 GUI* gui;
 ~Tutorial();
 Tutorial();
 void Update(float dt);
 void Render();
 void SwitchPhase(int phase);
 void LimitInputs();
 void EndTutorial();
};
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Main.hpp" 2

extern std::unique_ptr<sf::RenderWindow> window;
extern int width, height;
extern GUIHandler guihandler;
extern Game* game;
extern sf::Clock updateClock;
extern int numUpdates;
extern int currentBuild;
extern Tutorial* tutorial;
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp" 2
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
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Recipe.hpp" 1
       



class Structure;
class Recipe
{
public:
 RecipeData* data;
 int planetID;
 std::vector<float> fuelsLeft;
 std::vector<int> numInputs;
 std::vector<int> numOutputs;
 float craftTimer;
 Recipe(int planetID, RecipeData* data);
 void Update(float dt);
 bool TryAddItem(int index);
 int TryTakeItem();
 void Destroy(Structure* parent);
 JSON ToJSON();
 void FromJSON(JSON j);
 ~Recipe();
};
# 6 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RecipeHandler.cpp" 2

namespace RecipeHandler
{
std::vector<std::vector<RecipeData>> recipes;
GUI* gui = nullptr;
int guiStructure = -1;
int numBgObjs = 0;
}

void RecipeHandler::LoadRecipes(std::vector<JSON> jsons)
{
 recipes = {};
 for (int i = 0; i < ResourceHandler::numStructures; i++)
 {
  recipes.push_back({});
 }

 for (int i = 0; i < jsons.size(); i++)
 {
  JSON& j = jsons[i];
  RecipeData r;
  r.inputTypes = j.GetIntArr("inputTypes");
  r.inputAmounts = j.GetIntArr("inputAmounts");
  r.isFuels = j.GetBoolArr("isFuels");
  r.fuelLengths = j.GetFloatArr("fuelLengths");
  r.outputTypes = j.GetIntArr("outputTypes");
  r.outputAmounts = j.GetIntArr("outputAmounts");
  r.craftTime = j.GetFloat("craftTime");
  r.id = i;
  std::vector<int> structures = j.GetIntArr("StructureIDs");
  for (int j = 0; j < structures.size(); j++)
  {
   recipes[structures[j]].push_back(r);
  }
 }
}
void RecipeHandler::InitGUI(int structure)
{
 guiStructure = structure;
 gui = new GUI();
 GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));
 gui->AddObject(p);
 GUIPanel* topPanel = new GUIPanel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.4f, 0.03f), sf::Color(125, 125, 125));
 gui->AddObject(topPanel);
 Structure* s = game->ActivePlanet()->structures[structure];
 std::string name = "Select Recipe: " + ResourceHandler::structureTable->GetValue("Name", s->typeID);
 GUILabel* topLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), name);
 topLabel->SetColor(sf::Color::Black);
 gui->AddObject(topLabel);
 numBgObjs = gui->GUIObjects.size();

 if (s->typeID == 22)
 {
  RocketSilo* r = dynamic_cast<RocketSilo*>(s);

  if (r->launchType == -1)
  {
   topLabel->value = "Select Launch Type";
   GUILabel* option1 = new GUILabel(sf::Vector2f(.3f, .5f), sf::Vector2f(0.195f, 0.2f), "Option 1: send a probe that places a rocket silo on the target planet for future rockets to land on.");
   GUILabel* option2 = new GUILabel(sf::Vector2f(.7f, .5f), sf::Vector2f(0.195f, 0.2f), "Option 2: send a payload rocket that delivers items to the target planet.");
   option1->origin = sf::Vector2f(0.5f, 0.f);
   option2->origin = sf::Vector2f(0.5f, 0.f);
   option1->SetColor(sf::Color::Black);
   option2->SetColor(sf::Color::Black);
   option1->DoWrapping(20);
   option2->DoWrapping(20);
   {
    GUIImage* bg = new GUIImage(sf::Vector2f(.3f, .75f), sf::Vector2f(.1f, .03f), "content\\resources\\images\\buttonBezels.png");
    GUILabel* text = new GUILabel(sf::Vector2f(.3f, .75f), sf::Vector2f(.1f, .025f), "Option 1");
    text->SetColor(sf::Color::Black);
    GUIButton* b = new GUIButton(sf::Vector2f(.3f, .75f), sf::Vector2f(.1f, .03f), bg, text);
    gui->AddObject(b);
   }
   {
    GUIImage* bg = new GUIImage(sf::Vector2f(.7f, .75f), sf::Vector2f(.1f, .03f), "content\\resources\\images\\buttonBezels.png");
    GUILabel* text = new GUILabel(sf::Vector2f(.7f, .75f), sf::Vector2f(.1f, .025f), "Option 2");
    text->SetColor(sf::Color::Black);
    GUIButton* b = new GUIButton(sf::Vector2f(.7f, .75f), sf::Vector2f(.1f, .03f), bg, text);
    gui->AddObject(b);
   }
   gui->AddObject(option1);
   gui->AddObject(option2);
  }

  else
  {

   topLabel->value = ResourceHandler::structureTable->GetValue("Name", s->typeID);

   float inputEnd = 0.65f;
   float size = 0.05f;
   float gap = 0.1f;
   sf::Vector2f pos(inputEnd, 0.5f);
   Recipe* r = s->recipe;
   std::vector<GUIObject*> fuelBars = {};
   float fuelSize = 0.1f;
   float fuelOffset = 0.2f;
   float fuelWidth = 0.01f;
   for (int i = 0; i < r->numInputs.size(); i++)
   {
    GUIItem* item = new GUIItem(pos, sf::Vector2f(size, size), r->data->inputTypes[i], r->numInputs[i]);
    gui->GUIObjects.push_back(item);
    if (r->data->isFuels[i])
    {
     GUIPanel* bgPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
     GUIPanel* colorPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
     fuelBars.push_back(bgPanel);
     fuelBars.push_back(colorPanel);
    }

    pos.x -= gap;
   }

   GUIImage* im = new GUIImage(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.1f, 0.03f), "content\\resources\\images\\buttonBezels.png");
   GUILabel* label = new GUILabel(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.1f, 0.027f), "Launch");
   label->SetColor(sf::Color::Black);
   GUIButton* b = new GUIButton(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.1f, 0.03f), im, label);
   b->dimObj = nullptr;
   gui->AddObject(b);
   GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.6f), sf::Vector2f(0.1f, 0.03f), sf::Color(0, 0, 0, 100));
   gui->AddObject(p);
  }
 }

 else
 {
  if (s->recipe == nullptr)
  {

   std::vector<RecipeData> recs = recipes[s->typeID];
   float size = 0.05f;
   for (int i = 0; i < recs.size(); i++)
   {
    GUIItem* inpItem = new GUIItem(sf::Vector2f(0.f, 0.f), sf::Vector2f(size, size), recs[i].inputTypes[0], 0);
    GUIItem* outItem = new GUIItem(sf::Vector2f(0.f, 0.f), sf::Vector2f(size, size), recs[i].outputTypes[0], 0);
    inpItem->blocksMouseInput = true;
    outItem->blocksMouseInput = true;
    gui->AddObject(inpItem);
    gui->AddObject(outItem);
   }
  }
  else
  {

   topLabel->value = ResourceHandler::structureTable->GetValue("Name", s->typeID);
   numBgObjs += 2;
   GUIImage* arrow = new GUIImage(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.15f, 0.3f), "content\\resources\\images\\arrow.png");
   arrow->sprite.setColor(sf::Color(75, 75, 75));
   GUIImage* arrow2 = new GUIImage(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.15f, 0.3f), "content\\resources\\images\\arrow.png");
   arrow->keepAspectRatio = true;
   arrow2->keepAspectRatio = true;
   gui->AddObject(arrow);
   gui->AddObject(arrow2);

   float inputEnd = 0.3f;
   float outputStart = 0.7f;
   float size = 0.025f;
   float gap = 0.05f;
   sf::Vector2f pos(inputEnd, 0.5f);
   Recipe* r = s->recipe;
   std::vector<GUIObject*> fuelBars = {};
   float fuelSize = 0.1f;
   float fuelOffset = 0.2f;
   float fuelWidth = 0.01f;
   for (int i = 0; i < r->numInputs.size(); i++)
   {
    GUIItem* item = new GUIItem(pos, sf::Vector2f(size, size), r->data->inputTypes[i], r->numInputs[i]);
    gui->GUIObjects.push_back(item);
    if (r->data->isFuels[i])
    {
     GUIPanel* bgPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
     GUIPanel* colorPanel = new GUIPanel(pos + sf::Vector2f(0, fuelOffset), sf::Vector2f(fuelWidth, fuelSize), sf::Color(50, 50, 50));
     fuelBars.push_back(bgPanel);
     fuelBars.push_back(colorPanel);
    }

    pos.x -= gap;
   }
   pos = sf::Vector2f(outputStart, pos.y);
   for (int i = 0; i < r->numOutputs.size(); i++)
   {
    GUIItem* item = new GUIItem(pos, sf::Vector2f(size, size), r->data->outputTypes[i], r->numOutputs[i]);
    gui->GUIObjects.push_back(item);
    pos.x += gap;
   }
   for (int i = 0; i < fuelBars.size(); i++)
   {
    gui->GUIObjects.push_back(fuelBars[i]);
   }
  }
 }

 game->inMenu = true;
 guihandler.guis.push_back(gui);
}
void RecipeHandler::Update(float dt)
{
 if (gui != nullptr)
 {
  gui->Update(dt);
  Structure* s = game->ActivePlanet()->structures[guiStructure];

  if (s->typeID == 22)
  {
   RocketSilo* r = dynamic_cast<RocketSilo*>(s);
   if (r->launchType == -1)
   {
    GUIObject* b1 = gui->GUIObjects[numBgObjs];
    GUIObject* b2 = gui->GUIObjects[numBgObjs + 1];

    if (b1->isClicked())
    {
     InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
     InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
     r->SetRecipe(&recipes[22][0]);
     r->launchType = 0;
     guihandler.guis.pop_back();
     delete gui;
     gui = nullptr;
     game->inMenu = false;
    }
    else if (b2->isClicked())
    {
     InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
     InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
     r->launchType = 1;
     guihandler.guis.pop_back();
     delete gui;
     gui = nullptr;
     game->inMenu = false;
    }
   }
   else
   {
    int index = numBgObjs;

    for (int i = 0; i < s->recipe->numInputs.size(); i++)
    {
     dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->SetAmount(s->recipe->numInputs[i]);
     if (s->recipe->numInputs[i] == 0)
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color(255, 255, 255, 100));
     }
     else
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color::White);
     }
    }
    GUIPanel* p = dynamic_cast<GUIPanel*>(gui->GUIObjects.back());

    if (s->recipe->numOutputs[0] > 0)
    {
     p->SetColor(sf::Color(0, 0, 0, 0));
     if (gui->GUIObjects[gui->GUIObjects.size() - 2]->isClicked())
     {
      r->LaunchRocket();
      guihandler.guis.pop_back();
      delete gui;
      gui = nullptr;
      game->inMenu = false;
     }
    }
    else
    {
     p->SetColor(sf::Color(0, 0, 0, 150));
    }
   }
  }
  else
  {
   if (s->recipe == nullptr)
   {

    float inoutgap = 0.015f;
    sf::Vector2f gap(0.1f + inoutgap, 0.1f);
    float size = 0.05f;
    sf::Vector2f spos(0.1f + size, 0.16f + size);
    sf::Vector2f pos = spos;
    for (int i = numBgObjs; i < gui->GUIObjects.size(); i += 2)
    {
     gui->GUIObjects[i]->position = pos;
     gui->GUIObjects[i + 1]->position = pos + sf::Vector2f(inoutgap, 0.f);

     if (gui->GUIObjects[i]->isClicked() || gui->GUIObjects[i + 1]->isClicked())
     {
      InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
      InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
      s->SetRecipe(&recipes[s->typeID][(i - numBgObjs) / 2]);
      guihandler.guis.pop_back();
      delete gui;
      gui = nullptr;
      game->inMenu = false;
      break;
     }
     pos.x += gap.x;
     if (pos.x > 1 - spos.x)
     {
      pos.x = spos.x;
      pos.y += gap.y;
     }
    }
   }
   else
   {

    int index = numBgObjs;
    GUIImage* arrow = dynamic_cast<GUIImage*>(gui->GUIObjects[index - 1]);
    float prog = s->recipe->craftTimer / s->recipe->data->craftTime;
    if (prog < 0)
    {
     prog = 0;
    }
    if (prog > 1)
    {
     prog = 1;
    }
    prog = 1 - prog;
    sf::Vector2f arrowSize(0.15f, 0.3f);
    arrow->size.x = arrowSize.x;
    sf::IntRect size = sf::IntRect(0, 0, Lerp(0, arrow->sprite.getTexture()->getSize().x, prog), arrow->sprite.getTexture()->getSize().y);
    arrow->sprite.setTextureRect(size);
    arrow->position.x = (0.5f - arrow->size.x) + (arrow->size.x * ((float)size.width / (float)arrow->sprite.getTexture()->getSize().x));
    arrow->size.x = ((float)size.width / (float)arrow->sprite.getTexture()->getSize().x) * arrowSize.x;

    for (int i = 0; i < s->recipe->numInputs.size(); i++)
    {
     dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->SetAmount(s->recipe->numInputs[i]);
     if (s->recipe->numInputs[i] == 0)
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color(255, 255, 255, 100));
     }
     else
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color::White);
     }
    }
    index += s->recipe->numInputs.size();
    for (int i = 0; i < s->recipe->numOutputs.size(); i++)
    {
     dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->SetAmount(s->recipe->numOutputs[i]);
     if (s->recipe->numOutputs[i] == 0)
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color(255, 255, 255, 100));
     }
     else
     {
      dynamic_cast<GUIItem*>(gui->GUIObjects[i + index])->image->sprite.setColor(sf::Color::White);
     }
    }

    index += s->recipe->numOutputs.size();
    float fuelSize = 0.1f;
    float fuelOffset = 0.2f;
    float fuelWidth = 0.01f;
    int fuelIndex = 0;
    for (int i = index; i < gui->GUIObjects.size(); i++)
    {
     while (!s->recipe->data->isFuels[fuelIndex])
     {
      fuelIndex++;
     }
     float currLength = s->recipe->craftTimer;
     if (currLength < 0.f)
     {
      currLength = 0.f;
     }
     currLength += s->recipe->fuelsLeft[fuelIndex];
     currLength /= s->recipe->data->fuelLengths[fuelIndex];
     float height = currLength * fuelSize;
     float pos = 0.5f + fuelOffset;
     pos += height;
     pos -= fuelSize;
     dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->SetColor(Lerp(sf::Color::Green, sf::Color::Red, 1.f - currLength));
     dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->position.y = pos;
     dynamic_cast<GUIPanel*>(gui->GUIObjects[i + 1])->size.y = height;
     i++;
    }
   }
  }

  if (InputHandler::pressed(binds::CloseInventory))
  {
   InputHandler::RemovePressed(binds::CloseInventory);
   InputHandler::RemoveDown(binds::CloseInventory);
   guihandler.guis.pop_back();
   delete gui;
   gui = nullptr;
   game->inMenu = false;
  }
 }
}

RecipeData* RecipeHandler::GetRecipe(int id)
{
 for (int i = 0; i < recipes.size(); i++)
 {
  for (int j = 0; j < recipes[i].size(); j++)
  {
   if (recipes[i][j].id == id)
   {
    return &recipes[i][j];
   }
  }
 }
 return nullptr;
}
