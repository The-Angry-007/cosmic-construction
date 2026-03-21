# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.hpp" 2
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp" 2
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


extern std::unique_ptr<sf::RenderWindow> window;
extern int width, height;
extern GUIHandler guihandler;
extern Game* game;
extern sf::Clock updateClock;
extern int numUpdates;
extern int currentBuild;
extern Tutorial* tutorial;
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/BuildMenu.hpp" 1
       




class BuildMenu : public GUI
{
public:
 std::vector<GUIButton*> tabs;
 int currentTab;
 GUIPanel* bg;
 GUILabel* infoText;
 GUILabel* infoLabel;
 GUILabel* costText;
 GUILabel* costLabel;
 GUIPanel* infoBG;
 std::vector<std::vector<GUIObject*>> menus;
 std::vector<std::vector<int>> typeIDs;
 BuildMenu();
 void Update(float dt);
 void Render();
 void SetTab(int tab);
};
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp" 2

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
# 7 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Tutorial.cpp" 2
Tutorial::Tutorial()
{
 gui = nullptr;
 std::string scriptString = SaveHandler::ReadData("content\\resources\\text files\\tutorial.txt");
 script = Split(scriptString, '\n');
 int numPhases = script.size();
 validCodes = {};
 for (int i = 0; i < numPhases; i++)
 {
  validCodes.push_back({ binds::Pause });
 }

 validCodes[3].push_back(binds::UseTool);
 validCodes[5].push_back(binds::UseTool);
 validCodes[6].push_back(binds::UseTool);
 validCodes[6].push_back(sf::Keyboard::Key::LShift + 1);
 validCodes[8].push_back(binds::CloseInventory);
 validCodes[9].push_back(binds::CloseInventory);
 validCodes[9].push_back(binds::UseTool);
 validCodes[10].push_back(binds::UseTool);
 validCodes[12].push_back(binds::CloseInventory);
 validCodes[13].push_back(binds::CloseInventory);
 validCodes[13].push_back(binds::UseTool);
 validCodes[14].push_back(binds::UseTool);
 validCodes[15].push_back(binds::RotateStructure);
 validCodes[19].push_back(binds::CloseInventory);
 validCodes[20].push_back(binds::CloseInventory);
 validCodes[20].push_back(binds::UseTool);
 validCodes[22].push_back(binds::UseTool);
 validCodes[22].push_back(binds::CloseInventory);
 validCodes[22].push_back(binds::RotateStructure);
 validCodes[22].push_back(sf::Keyboard::Key::LShift + 1);
 validCodes[22].push_back(binds::Tool2);
 validCodes[22].push_back(binds::Tool3);
 validCodes[29].push_back(binds::Tool3);
 validCodes[29].push_back(binds::Tool2);
 validCodes[29].push_back(binds::CloseInventory);
 validCodes[29].push_back(binds::RotateStructure);
 validCodes[29].push_back(sf::Keyboard::Key::LShift + 1);
 validCodes[29].push_back(binds::UseTool);
 SwitchPhase(0);
 skippables = {};
 for (int i = 0; i < numPhases; i++)
 {
  if (script[i].back() == '>')
  {
   skippables.push_back(true);
  }
  else
  {
   skippables.push_back(false);
  }
 }
 game->ActivePlanet()->camera.targetZoom = 0.4f;
}

void Tutorial::SwitchPhase(int phase)
{

 if (gui != nullptr)
 {
  delete gui;
 }
 currentPhase = phase;

 gui = new GUI();
 float ypos = 0.12f;
 GUIPanel* outlineBG = new GUIPanel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.33f, 0.1f), sf::Color(50, 50, 50));
 GUIPanel* bg = new GUIPanel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.32f, 0.09f), sf::Color(150, 150, 150));
 GUILabel* label = new GUILabel(sf::Vector2f(0.5f, ypos), sf::Vector2f(0.3f, 0.08f), script[currentPhase]);
 label->SetColor(sf::Color::Black);
 label->DoWrapping(70);
 gui->AddObject(outlineBG);
 gui->AddObject(bg);
 gui->AddObject(label);
 if (phase == 3)
 {
  game->toolHandler->selectedTool = 2;
 }
 else if (phase == 5)
 {
  game->toolHandler->selectedTool = 1;
 }
 GUIImage* skipImage = new GUIImage(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.08f, 0.04f), "content/resources/images/buttonBezels.png");
 GUILabel* skipLabel = new GUILabel(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.075f, 0.035f), "skip tutorial");
 GUIButton* skipButton = new GUIButton(sf::Vector2f(0.92f, 0.9f), sf::Vector2f(0.08f, 0.04f), skipImage, skipLabel);
 skipLabel->SetColor(sf::Color::Black);
 std::function<void()> endFunc = std::bind(&Tutorial::EndTutorial, this);
 skipButton->clickFunc = endFunc;
 gui->AddObject(skipButton);
}

void Tutorial::Update(float dt)
{

 if (gui != nullptr)
 {
  gui->Update(dt);
  float ypos = 0.12f;

  if (game->inMenu || guihandler.activeGui != 5)
  {
   ypos = 1.f - ypos;
  }
  for (int i = 0; i < 3; i++)
  {
   gui->GUIObjects[i]->position.y = ypos;
  }
 }

 if (tutorial == nullptr)
 {
  return;
 }
 if (skippables[currentPhase] && InputHandler::keyPressed(sf::Keyboard::Key::Tab))
 {

  if (currentPhase == 35)
  {
   EndTutorial();
   return;
  }
  SwitchPhase(currentPhase + 1);
 }
 Planet& p = game->planets[game->activePlanet];

 if (currentPhase == 3 && p.StructuresInArea({ 0, 0 }, { 31, 31 }).size() == 1)
 {
  SwitchPhase(4);
 }
 if (currentPhase == 5)
 {
  StorageSilo* s = dynamic_cast<StorageSilo*>(p.structures[p.StructureInPos({ 16, 16 })]);
  if (s->itemIDs.size() > 1 || s->itemQuantities[0] > 20)
  {
   SwitchPhase(6);
  }
 }
 if (currentPhase == 6)
 {
  bool skip = true;
  for (int i = 0; i < p.items.size(); i++)
  {
   if (!p.items[i].isDeleted)
   {
    skip = false;
    break;
   }
  }
  if (skip)
  {
   SwitchPhase(7);
  }
 }
 if (currentPhase == 8)
 {
  if (InputHandler::pressed(binds::CloseInventory))
  {
   SwitchPhase(9);
  }
 }
 if (currentPhase == 9)
 {
  if (game->toolHandler->placeType == 4)
  {
   SwitchPhase(10);
  }
 }
 if (currentPhase == 10)
 {
  std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
  for (int i = 0; i < structures.size(); i++)
  {
   if (p.structures[structures[i]]->typeID == 4)
   {
    SwitchPhase(11);
    break;
   }
  }
 }
 if (currentPhase == 12)
 {
  if (InputHandler::pressed(binds::CloseInventory))
  {
   SwitchPhase(13);
  }
 }
 if (currentPhase == 13)
 {
  if (game->toolHandler->placeType == 3)
  {
   SwitchPhase(14);
  }
 }
 if (currentPhase == 14)
 {

  sf::Vector2i pos(0, 0);
  std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
  for (int i = 0; i < structures.size(); i++)
  {
   if (p.structures[structures[i]]->typeID == 4)
   {
    pos = p.structures[structures[i]]->position;
    break;
   }
  }

  for (int i = 0; i < 4; i++)
  {
   sf::Vector2i newPos = pos + CONVEYOR_OFFSETS[i];
   int index = p.StructureInPos(newPos);
   if (index != -1 && p.structures[index]->typeID == 3)
   {
    SwitchPhase(15);
   }
  }
 }
 if (currentPhase == 15)
 {
  game->toolHandler->selectedTool = 1;

  sf::Vector2i pos(0, 0);
  std::vector<int> structures = p.StructuresInArea({ 0, 0 }, { 32, 32 });
  for (int i = 0; i < structures.size(); i++)
  {
   if (p.structures[structures[i]]->typeID == 4)
   {
    pos = p.structures[structures[i]]->position;
    break;
   }
  }

  for (int i = 0; i < 4; i++)
  {
   sf::Vector2i newPos = pos + CONVEYOR_OFFSETS[i];
   int index = p.StructureInPos(newPos);
   if (index != -1 && p.structures[index]->typeID == 3 && p.structures[index]->direction == (i + 2) % 4)
   {
    SwitchPhase(16);
   }
  }
 }
 if (currentPhase == 19)
 {
  if (InputHandler::pressed(binds::CloseInventory))
  {
   SwitchPhase(20);
  }
 }
 if (currentPhase == 20)
 {
  if (game->toolHandler->placeType == 0)
  {
   SwitchPhase(21);
  }
 }
 if (currentPhase == 22)
 {
  auto numWood = p.TallyResources({ 0, 0 }, { 0 });
  if (numWood[0] >= 30)
  {
   SwitchPhase(23);
  }
 }
 if (currentPhase == 29)
 {
  auto tally = p.TallyResources({ 0, 0 }, { 1, 2 });
  if (tally[0] >= 15 && tally[1] >= 5)
  {
   SwitchPhase(30);
  }
 }

 if (!game->paused)
 {
  LimitInputs();
 }
}
void Tutorial::Render()
{
 if (gui == nullptr)
 {
  return;
 }
 sf::View currentView = window->getView();
 sf::View GUIView(sf::FloatRect(0.f, 0.f, width, height));
 window->setView(GUIView);
 gui->Render();

 window->setView(currentView);
}

void Tutorial::LimitInputs()
{
 for (int i = 0; i < InputHandler::keysPressed.size(); i++)
 {
  int code = binds::keyToCode(InputHandler::keysPressed[i]);
  bool valid = false;
  for (int j = 0; j < validCodes[currentPhase].size(); j++)
  {
   if (validCodes[currentPhase][j] == code)
   {
    valid = true;
    break;
   }
  }
  if (!valid)
  {
   InputHandler::keysPressed.erase(InputHandler::keysPressed.begin() + i);
   i--;
  }
 }
 for (int i = 0; i < InputHandler::keysDown.size(); i++)
 {
  int code = binds::keyToCode(InputHandler::keysDown[i]);
  bool valid = false;
  for (int j = 0; j < validCodes[currentPhase].size(); j++)
  {
   if (validCodes[currentPhase][j] == code)
   {
    valid = true;
    break;
   }
  }
  if (!valid)
  {
   InputHandler::keysDown.erase(InputHandler::keysDown.begin() + i);
   i--;
  }
 }

 for (int i = 0; i < InputHandler::mouseButtonsPressed.size(); i++)
 {
  int code = binds::buttonToCode(InputHandler::mouseButtonsPressed[i]);
  bool valid = false;
  for (int j = 0; j < validCodes[currentPhase].size(); j++)
  {
   if (validCodes[currentPhase][j] == code)
   {
    valid = true;
    break;
   }
  }
  if (!valid)
  {
   InputHandler::mouseButtonsPressed.erase(InputHandler::mouseButtonsPressed.begin() + i);
   i--;
  }
 }
 for (int i = 0; i < InputHandler::mouseButtonsDown.size(); i++)
 {
  int code = binds::buttonToCode(InputHandler::mouseButtonsDown[i]);
  bool valid = false;
  for (int j = 0; j < validCodes[currentPhase].size(); j++)
  {
   if (validCodes[currentPhase][j] == code)
   {
    valid = true;
    break;
   }
  }
  if (!valid)
  {
   InputHandler::mouseButtonsDown.erase(InputHandler::mouseButtonsDown.begin() + i);
   i--;
  }
 }
}

void Tutorial::EndTutorial()
{
 tutorial = nullptr;
 delete this;
}

Tutorial::~Tutorial()
{
 if (gui != nullptr)
 {
  delete gui;
 }
}
