# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.hpp" 2
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.cpp" 2
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
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/ClickFuncs.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIObject.hpp" 1
       

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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Camera.hpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/FilterConveyor.cpp" 2


FilterConveyor::FilterConveyor(int id, int planetID, int direction)
{
 SetID(id);
 this->planetID = planetID;
 typeID = 17;
 SetDirection(direction);
 tileSize = ResourceHandler::structureSizes[typeID];
 sprite = sf::Sprite();
 ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction);
 overlaySprite = sf::Sprite();
 ResourceHandler::structureAtlas->SetSprite(overlaySprite, 17, 8);

 gap = 0.2f;
 progress = { {}, {}, {}, {} };
 items = { {}, {}, {}, {} };
 speed = 3.f;
 blocksItems = false;
 placedByPlayer = true;
 isConveyor = true;

 filterItem = -1;
}

void FilterConveyor::UpdateNeighbours()
{
 std::vector<sf::Vector2i> offsets = {
  { 0, -1 },
  { 1, 0 },
  { 0, 1 },
  { -1, 0 }
 };
 std::vector<int> directions = {
  2, 3, 0, 1
 };
 neighbours = {};
 Planet& p = game->planets[planetID];
 sf::Vector2i pos = position + p.GetChunk(chunkID)->position * CHUNK_SIZE;
 for (int i = 0; i < offsets.size(); i++)
 {
  sf::Vector2i newPos = pos + offsets[i];
  int structure = p.StructureInPos(newPos);
  if (structure != -1)
  {
   Structure* s = p.structures[structure];

   neighbours.push_back(structure);
  }
  else
  {
   neighbours.push_back(-1);
  }
 }
}
void FilterConveyor::Update(float dt)
{
}

void FilterConveyor::Render()
{
 zindex = -32;
 Planet& p = game->planets[planetID];
 p.renderObjects.push_back(RenderObject {
  &sprite,
  zindex });

 p.renderObjects.push_back(RenderObject {
  &overlaySprite,
  99 });

 if (filterItem != -1)
 {
  Item& item = game->planets[planetID].items[filterItem];
  item.zindex = 100;
  sf::Vector2i tilepos = position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
  sf::Vector2f pos((tilepos.x + 0.5f) * TILE_SIZE.x, (tilepos.y + 0.5f) * TILE_SIZE.y);
  item.position = pos;
  item.Render(&game->planets[planetID]);
 }

 for (uint i = 0; i < 4; i++)
 {
  for (uint j = 0; j < items[i].size(); j++)
  {
   sf::Vector2f startPos(0.5f, 0.5f);
   startPos += (sf::Vector2f)CONVEYOR_OFFSETS[i] / 2.f;
   sf::Vector2f endPos(0.5f, 0.5f);
   float prog = progress[i][j];
   if (i != (direction + 2) % 4)
    prog = 1 - prog;
   if (prog > 1.f)
   {
    prog = 1.f;
   }
   sf::Vector2f pos = Lerp(startPos, endPos, prog);
   pos += (sf::Vector2f)position;
   pos += (sf::Vector2f)(game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
   pos.x *= TILE_SIZE.x;
   pos.y *= TILE_SIZE.y;
   game->planets[planetID].items[items[i][j]].position = pos;
   game->planets[planetID].items[items[i][j]].Render(&game->planets[planetID]);
  }
 }
}

void FilterConveyor::TryAddGroundItem(int index)
{

 int dir = (direction + 2) % 4;
 if (progress[dir].size() > 0 && progress[dir][progress[dir].size() - 1] < gap)
 {
  return;
 }
 this->items[dir].push_back(index);
 progress[dir].push_back(0.f);
 Item* item = &game->planets[planetID].items[index];
 Chunk* chunk = game->planets[planetID].GetChunk(item->chunkID);
 for (int i = 0; i < chunk->items.size(); i++)
 {
  if (chunk->items[i] == index)
  {
   chunk->items.erase(chunk->items.begin() + i);
   break;
  }
 }
 item->SetParent(id);

 return;
}

void FilterConveyor::SetPosition(sf::Vector2i position)
{
 Structure::SetPosition(position);
 overlaySprite.setPosition(sprite.getPosition());
}
void FilterConveyor::SetDirection(int direction)
{
 this->direction = direction;
 ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
}

void FilterConveyor::SetFlipped(bool flipped)
{
 this->isFlipped = flipped;
 ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
}

JSON FilterConveyor::ToJSON()
{
 JSON j = JSON();
 j.AddAttribute("PositionX", std::to_string(position.x));
 j.AddAttribute("PositionY", std::to_string(position.y));
 j.AddAttribute("TypeID", std::to_string(typeID));
 j.AddAttribute("Direction", std::to_string(direction));
 j.AddAttribute("ID", std::to_string(id));
 j.AddAttribute("ChunkID", std::to_string(chunkID));
 j.AddAttribute("FilterItem", filterItem);
 j.AddAttribute("IsFlipped", isFlipped);
 j.AddAttribute("UpgradeLevel", upgradeLevel);
 for (uint i = 0; i < 4; i++)
 {
  std::string strItems = "";
  std::string strProgress = "";
  for (int j = 0; j < items[i].size(); j++)
  {
   strItems += std::to_string(items[i][j]);
   strProgress += std::to_string(progress[i][j]);
   if (j != items[i].size() - 1)
   {
    strItems += ",";
    strProgress += ",";
   }
  }
  j.AddAttribute("items " + std::to_string(i), strItems);
  j.AddAttribute("progress " + std::to_string(i), strProgress);
 }
 return j;
}

void FilterConveyor::FromJSON(JSON j)
{
 sf::Vector2i pos(0, 0);
 pos.x = std::stoi(j.GetValue("PositionX"));
 pos.y = std::stoi(j.GetValue("PositionY"));
 typeID = std::stoi(j.GetValue("TypeID"));
 SetUpgradeLevel(j.GetInt("UpgradeLevel"));
 direction = std::stoi(j.GetValue("Direction"));
 SetID(std::stoi(j.GetValue("ID")));
 chunkID = std::stoi(j.GetValue("ChunkID"));
 pos += game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE;
 isFlipped = j.GetInt("IsFlipped");

 ResourceHandler::structureAtlas->SetSprite(sprite, 17, direction + 4 * isFlipped);
 SetPosition(pos);
 filterItem = j.GetInt("FilterItem");

 for (int i = 0; i < 4; i++)
 {
  auto items = Split(j.GetValue("items " + std::to_string(i)), ',');

  if (items.size() == 1 && items[0].length() == 0)
  {
   continue;
  }
  auto progress = Split(j.GetValue("progress " + std::to_string(i)), ',');
  for (int j = 0; j < items.size(); j++)
  {
   this->items[i].push_back(std::stoi(items[j]));
   this->progress[i].push_back(std::stof(progress[j]));
  }
 }
}

FilterConveyor::~FilterConveyor()
{
}

void FilterConveyor::RenderPreview()
{
 int opacity = 100;
 sf::Color col = sf::Color::Green;

 if (!CanBePlaced())
 {
  col = sf::Color(255, 100, 100);
 }
 col.a = opacity;
 sprite.setColor(col);
 Planet& p = game->planets[planetID];
 p.renderObjects.push_back(RenderObject {
  &sprite,
  2000 });
}

void FilterConveyor::Destroy()
{
 for (int i = 0; i < 4; i++)
 {
  for (int j = 0; j < items[i].size(); j++)
  {
   Item& item = game->planets[planetID].items[items[i][j]];
   item.SetParent(-1);
   item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
   item.position += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
   item.position.x *= TILE_SIZE.x;
   item.position.y *= TILE_SIZE.y;
   game->planets[planetID].MoveItem(items[i][j]);
  }
 }
 if (filterItem != -1)
 {
  Item& item = game->planets[planetID].items[filterItem];
  item.zindex = 1;
  item.SetParent(-1);
  item.position = (sf::Vector2f)(position + game->planets[planetID].GetChunk(chunkID)->position * CHUNK_SIZE);
  item.position += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
  item.position.x *= TILE_SIZE.x;
  item.position.y *= TILE_SIZE.y;
  game->planets[planetID].MoveItem(item.id);
 }
}

bool FilterConveyor::TryAddItem(int index, int direction, float progress)
{
 if (direction != (this->direction + 2) % 4)
 {
  return false;
 }
 if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
 {
  this->progress[direction].push_back(progress);
  items[direction].push_back(index);
  return true;
 }
 return false;
}

bool FilterConveyor::CanAddItem(int direction, float progress)
{
 if (direction != (this->direction + 2) % 4)
 {
  return false;
 }

 if (this->progress[direction].size() == 0 || this->progress[direction].back() - progress > gap)
 {

  return true;
 }
 return false;
}

float FilterConveyor::Distance(int direction)
{
 if (progress[direction].size() == 0)
 {
  return 1.f;
 }
 return progress[direction].back();
}

bool FilterConveyor::AcceptsItems(int direction)
{
 return (direction == (this->direction + 2) % 4);
}

void FilterConveyor::Progress(float dt)
{
 for (int i = 0; i < 4; i++)
 {
  for (int j = 0; j < progress[i].size(); j++)
  {
   progress[i][j] += dt * speed;
  }
 }
}

void FilterConveyor::TryAdd()
{
 int numChecked = 0;
 int index = 0;
 while (numChecked < 4)
 {
  numChecked++;
  index = (index + 1) % 4;
  if (index == (direction + 2) % 4)
  {
   continue;
  }

  if (neighbours[index] != -1)
  {
   if (progress[index].size() > 0)
   {
    Structure* s = game->planets[planetID].structures[neighbours[index]];
    if (s->isConveyor)
    {
     ConveyorType* c = dynamic_cast<ConveyorType*>(s);
     int dir = (index + 2) % 4;
     if (progress[index][0] >= 1.f && c->TryAddItem(items[index][0], dir, progress[index][0] - 1.f))
     {
      progress[index].erase(progress[index].begin());
      items[index].erase(items[index].begin());
     }
    }
    else
    {
     if (progress[index][0] >= 1.f && s->TryAddItem(items[index][0]))
     {
      items[index].erase(items[index].begin());
      progress[index].erase(progress[index].begin());
     }
    }
   }
  }
 }
 int dir = (direction + 2) % 4;
 if (progress[dir].size() > 0 && progress[dir][0] >= 1.f)
 {
  int outputDir = direction;

  if (filterItem != -1)
  {
   auto& items = game->planets[planetID].items;
   int filterType = items[filterItem].typeId;
   if (filterType == items[this->items[dir][0]].typeId)
   {

    if (this->isFlipped)
    {
     outputDir = (direction + 1) % 4;
    }
    else
    {
     outputDir = (direction + 3) % 4;
    }
   }
  }

  else
  {
   filterItem = items[dir][0];
   progress[dir].erase(progress[dir].begin());
   items[dir].erase(items[dir].begin());
   return;
  }

  if (progress[outputDir].size() == 0 || progress[outputDir].back() > gap)
  {
   progress[outputDir].push_back(progress[dir][0] - 1.f);
   items[outputDir].push_back(items[dir][0]);
   items[dir].erase(items[dir].begin());
   progress[dir].erase(progress[dir].begin());
  }
 }
}

void FilterConveyor::KeepDistance()
{
 for (int j = 0; j < 4; j++)
 {

  if (j == (direction + 2) % 4)
  {
   if (progress[j].size() == 0)
   {
    continue;
   }

   int outputDir = this->direction;
   if (filterItem != -1)
   {
    auto& items = game->planets[planetID].items;
    int filterType = items[filterItem].typeId;
    if (filterType == items[this->items[j][0]].typeId)
    {
     if (this->isFlipped)
     {
      outputDir = (direction + 1) % 4;
     }
     else
     {
      outputDir = (direction + 3) % 4;
     }
    }
   }

   if (progress[outputDir].size() > 0)
   {
    float dist = progress[outputDir].back();
    if (dist < gap)
    {
     progress[j][0] = 1.f - (gap - dist);
    }
   }

   for (int k = 1; k < progress[j].size(); k++)
   {
    if (progress[j][k - 1] - progress[j][k] < gap)
    {
     progress[j][k] = progress[j][k - 1] - gap;
     if (progress[j][k] < 0)
     {
      progress[j][k] = 0.f;
     }
    }
   }
   continue;
  }

  if (neighbours[j] != -1)
  {
   int direction = j;

   for (int i = 0; i < progress[direction].size(); i++)
   {
    if (i == 0)
    {

     if (progress[direction][i] > 1.f)
     {
      progress[direction][i] = 1.f;
     }
     Structure* s = game->planets[planetID].structures[neighbours[direction]];

     if (s->isConveyor)
     {
      ConveyorType* c = dynamic_cast<ConveyorType*>(s);
      float dist = c->Distance((direction + 2) % 4);
      if (1.f - progress[direction][0] + dist < gap)
      {
       progress[direction][0] = 1.f - (gap - dist);
      }
     }
    }
    else
    {

     if (progress[direction][i - 1] - progress[direction][i] < gap)
     {
      progress[direction][i] = progress[direction][i - 1] - gap;
      if (progress[direction][i] < 0)
      {
       progress[direction][i] = 0.f;
      }
     }
    }
   }
  }
  else
  {


   for (int k = 0; k < progress[j].size(); k++)
   {
    if (k == 0)
    {
     if (progress[j][k] > 1.f)
     {
      progress[j][k] = 1.f;
     }
    }
    else
    {

     if (progress[j][k - 1] - progress[j][k] < gap)
     {
      progress[j][k] = progress[j][k - 1] - gap;
      if (progress[j][k] < 0)
      {
       progress[j][k] = 0.f;
      }
     }
    }
   }
  }
 }
}
