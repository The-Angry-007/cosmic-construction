# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp"
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 1
       

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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Chunk.hpp" 1
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Item.hpp" 1
       



# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ResourceHandler.hpp" 1
       

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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ResourceHandler.hpp" 2

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
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Planet.hpp" 2

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
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.hpp" 2
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Main.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 1
       



# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Game.hpp" 1
       




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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp" 2
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
# 5 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/ToolHandler.cpp" 2

ToolHandler::ToolHandler()
{
 selectedTool = 1;

 selectedObj = guihandler.guis[5]->GUIObjects[3 * guihandler.numTools];
 selectedObj->position = guihandler.toolPoses[selectedTool];
 bgObjs = {};
 for (int i = 0; i < guihandler.numTools; i++)
 {
  bgObjs.push_back(dynamic_cast<GUIPanel*>(guihandler.guis[5]->GUIObjects[guihandler.numTools + i * 2]));
  bgObjs[i]->blocksMouseInput = true;
 }
 draggingItems = {};
 hoveringItem = nullptr;
 placeDir = 0;
 lastPlacedStructure = -1;
 placeType = 0;
 prevTilePos = sf::Vector2i(-10000, -10000);
 previewStructure = nullptr;
 insufficientLabel = nullptr;
 placingFlipped = false;
 selectedImages = {};

 draggingStructure = -1;
 prevmousepos = sf::Vector2f(0.f, 0.f);
 tallyObjs = {};
}
ToolHandler::~ToolHandler()
{
 for (int i = 0; i < selectedImages.size(); i++)
 {
  int j = guihandler.guis[5]->GetIndex(selectedImages[i]);
  guihandler.guis[5]->RemoveObject(j);
 }
 if (insufficientLabel != nullptr)
 {
  guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(insufficientLabel));
 }
 ClearTally();
}
void ToolHandler::Update(float dt, Planet* p)
{

 delete hoveringItem;
 hoveringItem = nullptr;

 if (insufficientLabel != nullptr)
 {
  float time = 1.5f;
  if (insufficientTimer.getElapsedTime().asSeconds() > time)
  {
   guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(insufficientLabel));
   insufficientLabel = nullptr;
  }
  else
  {
   float prog = insufficientTimer.getElapsedTime().asSeconds() / time;
   prog = 1 - prog;
   insufficientLabel->SetColor(sf::Color(255, 0, 0, Lerp(0, 255, prog)));
   insufficientLabel->position = { 0.5f, 0.3f + prog * 0.2f };
  }
 }

 if (InputHandler::pressed(binds::CloseInventory) && (!game->inMenu || guihandler.activeGui == 7))
 {
  if (guihandler.activeGui == 7)
  {
   guihandler.GoBack();
   game->inMenu = false;
  }
  else if (!game->inMenu)
  {
   game->inMenu = true;

   guihandler.OpenGUI(7);
  }
 }
 if (game->inMenu)
 {
  return;
 }

 if (tutorial == nullptr)
 {
  for (int i = 0; i < bgObjs.size(); i++)
  {
   if (bgObjs[i]->isClicked())
   {
    if (i == 0 && selectedTool == 0)
    {
     game->inMenu = true;
     guihandler.OpenGUI(7);
    }
    selectedTool = i;
    InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
    InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
   }
   if (bgObjs[i]->isBlockingMouse())
   {
    InputHandler::mouseIsBlocked = true;
   }
  }
 }

 if (InputHandler::pressed(binds::Tool1))
 {

  selectedTool = 0;
 }
 if (InputHandler::pressed(binds::Tool2))
 {
  selectedTool = 1;
 }
 if (InputHandler::pressed(binds::Tool3))
 {
  selectedTool = 2;
 }
 selectedObj->position = guihandler.toolPoses[selectedTool];
 if (InputHandler::pressed(binds::RotateStructure))
 {
  placeDir = (placeDir + 1) % 4;
 }

 sf::Vector2f mousePos = p->camera.WorldMousePos();
 sf::Vector2i tilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));

 int index = p->StructureInPos(tilePos);







 if (selectedTool == 0)
 {

  if (InputHandler::pressed(binds::FlipStructure))
  {
   placingFlipped = !placingFlipped;
  }

  if (previewStructure != nullptr)
  {
   delete previewStructure;
   previewStructure = nullptr;
  }

  ReloadTally(tilePos);

  if (placeType == 0)
  {
   Conveyor* c = new Conveyor(0, game->activePlanet, placeDir);
   c->SetVisualPosition(tilePos);

   previewStructure = c;

   if (InputHandler::down(binds::UseTool))
   {
    if (p->StructureInPos(tilePos) == -1)
    {
     if (p->DeductResources(0, tilePos))
     {

      int direction = placeDir;

      if (lastPlacedStructure != -1 && p->structures[lastPlacedStructure] != nullptr)
      {
       int dir = 0;
       sf::Vector2i offset = tilePos;
       sf::Vector2i prevpos = p->structures[lastPlacedStructure]->position + p->GetChunk(p->structures[lastPlacedStructure]->chunkID)->position * CHUNK_SIZE;
       offset -= prevpos;
       for (int i = 0; i < 4; i++)
       {
        if (CONVEYOR_OFFSETS[i] == offset)
        {
         dir = i;
        }
       }
       direction = dir;

       dynamic_cast<Conveyor*>(p->structures[lastPlacedStructure])->SetDirection(direction);
       p->updateNeighbours = true;
      }
      else
      {

       if (prevTilePos.x != -10000)
       {
        sf::Vector2i offset = tilePos;
        offset -= prevTilePos;
        int dir = 0;
        for (int i = 0; i < 4; i++)
        {
         if (CONVEYOR_OFFSETS[i] == offset)
         {
          dir = i;
         }
        }
        direction = dir;
       }
      }
      Conveyor* s = new Conveyor(-1, p->id, direction);

      p->AddStructure(s);
      lastPlacedStructure = s->id;
      s->SetPosition(tilePos);
      p->UpdateNeighbours();
     }
     else
     {
      ShowInsufficient();
     }
    }
    else
    {
     if (lastPlacedStructure != -1)
     {
      if (prevTilePos != tilePos && prevTilePos.x != -10000)
      {
       sf::Vector2i offset = tilePos;
       offset -= prevTilePos;
       int dir = 0;
       for (int i = 0; i < 4; i++)
       {
        if (CONVEYOR_OFFSETS[i] == offset)
        {
         dir = i;
        }
       }
       dynamic_cast<Conveyor*>(p->structures[lastPlacedStructure])->SetDirection(dir);
       p->updateNeighbours = true;
      }
     }
     if (p->structures[p->StructureInPos(tilePos)]->typeID == 0)
     {
      lastPlacedStructure = p->StructureInPos(tilePos);
     }
    }
    prevTilePos = tilePos;
   }
   else
   {
    lastPlacedStructure = -1;
    prevTilePos = sf::Vector2i(-10000, -10000);
   }
  }
  else
  {

   sf::Vector2f pos1(mousePos.x / TILE_SIZE.x, mousePos.y / TILE_SIZE.y);
   pos1 -= (sf::Vector2f)(ResourceHandler::structureSizes[placeType] - sf::Vector2i(1, 1)) / 2.f;
   sf::Vector2i pos(floor(pos1.x), floor(pos1.y));

   sf::Vector2i size = ResourceHandler::structureSizes[placeType];


   Structure* s = CreateStructure(placeType);
   s->SetFlipped(placingFlipped);
   s->SetVisualPosition(pos);

   previewStructure = s;

   if (placeType == 10 && placingFlipped)
   {
    sf::Vector2i position = pos;
    for (int i = 1; i < 9; i++)
    {
     position -= CONVEYOR_OFFSETS[placeDir];
     int structure = p->StructureInPos(position);
     if (structure != -1)
     {
      Structure* s = p->structures[structure];
      if (s->typeID == 10 && s->direction == placeDir && !s->isFlipped)
      {
       sf::Color col = sf::Color::Yellow;
       int max = dynamic_cast<Underground*>(s)->maxLength;
       if (i > max)
       {
        break;
       }
       if (i == max)
       {
        col = sf::Color::Green;
       }
       position += CONVEYOR_OFFSETS[placeDir];

       for (int j = 0; j < i - 1; j++)
       {
        ShowSelectArea(position, 0, 0, col);
        position += CONVEYOR_OFFSETS[placeDir];
       }
       break;
      }
     }
    }
   }

   if (InputHandler::pressed(binds::UseTool))
   {
    if (!p->StructureInArea(pos, size))
    {
     if (p->DeductResources(placeType, pos))
     {
      Structure* s2 = CreateStructure(placeType);
      s2->SetID(-1);
      s2->SetFlipped(placingFlipped);
      p->AddStructure(s2);

      s2->SetPosition(pos);
      p->UpdateNeighbours();

      if (placeType == 10)
      {
       placingFlipped = !placingFlipped;
      }
     }
     else
     {
      ShowInsufficient();
     }
    }
   }
  }

  if (previewStructure != nullptr && !InputHandler::mouseIsBlocked && !game->inMenu)
  {
   previewStructure->RenderPreview();
  }
 }






 else if (selectedTool == 1)
 {
  if (draggingStructure != -1)
  {
   if (prevmousepos == sf::Vector2f(0.f, 0.f))
   {
    prevmousepos = mousePos;
   }
   if (p->structures[draggingStructure] == nullptr)
   {
    draggingStructure = -1;
   }
   if (!InputHandler::down(binds::UseTool))
   {
    sf::Vector2f offset = structureStartDraggingPos - mousePos;
    if (offset.x * offset.x + offset.y * offset.y < 9.f)
    {
     p->structures[draggingStructure]->Interact();
    }
    draggingStructure = -1;
    prevmousepos = sf::Vector2f(0.f, 0.f);
   }
   else
   {

    sf::Vector2i originalTilePos(floor(prevmousepos.x / TILE_SIZE.x), floor(prevmousepos.y / TILE_SIZE.y));
    sf::Vector2i newTilePos(floor(mousePos.x / TILE_SIZE.x), floor(mousePos.y / TILE_SIZE.y));
    if (newTilePos != originalTilePos && p->structures[draggingStructure]->placedByPlayer)
    {
     sf::Vector2i diff = newTilePos - originalTilePos;
     Structure* s = p->structures[draggingStructure];
     sf::Vector2i newPos = diff + s->position + p->GetChunk(s->chunkID)->position * CHUNK_SIZE;
     auto structs = p->StructuresInArea(newPos, s->tileSize);
     if (structs.size() == 0 || structs.size() == 1 && structs[0] == draggingStructure)
     {
      s->SetPosition(newPos);
      prevmousepos = mousePos;
     }
    }
   }
  }
  else if (draggingItems.size() == 0 || InputHandler::keyDown(sf::Keyboard::Key::LShift))
  {
   bool end = false;
   std::vector<int> touchingItems = {};
   for (int i = 0; i < p->items.size(); i++)
   {
    if (p->items[i].parent != -1 || p->items[i].isDeleted)
    {
     continue;
    }
    bool dragging = false;
    for (int j = 0; j < draggingItems.size(); j++)
    {
     if (draggingItems[j] == i)
     {
      dragging = true;
      break;
     }
    }
    if (dragging)
     continue;
    if ((p->items[i].hitbox->intersectsPoint(p->camera.WorldMousePos()) && (InputHandler::keyDown(sf::Keyboard::Key::LShift) || p->items[i].accurateHitbox->intersectsPoint(p->camera.WorldMousePos()))) && !InputHandler::mouseIsBlocked)
    {
     touchingItems.push_back(i);
    }
   }
   if (touchingItems.size() > 0)
   {
    int lowestYIndex = 0;
    for (int i = 0; i < touchingItems.size(); i++)
    {
     if (p->items[touchingItems[i]].position.y > p->items[touchingItems[lowestYIndex]].position.y)
     {
      lowestYIndex = i;
     }
     else if (p->items[touchingItems[i]].position.y == p->items[touchingItems[lowestYIndex]].position.y)
     {
      if (p->items[touchingItems[i]].position.x > p->items[touchingItems[lowestYIndex]].position.x)
      {
       lowestYIndex = i;
      }
     }
    }
    int i = touchingItems[lowestYIndex];
    if (InputHandler::pressed(binds::UseTool))
    {
     draggingItems = { i };
    }
    else if (!InputHandler::down(binds::UseTool))
    {

     hoveringItem = new Item(p->items[i].position, -2, p->items[i].typeId);
     hoveringItem->zindex = 100;
     ResourceHandler::itemAtlas->SetSprite(hoveringItem->sprite, hoveringItem->typeId + ResourceHandler::numItems);
     hoveringItem->Render(p);
    }
    else if (InputHandler::down(binds::UseTool) && InputHandler::keyDown(sf::Keyboard::Key::LShift))
    {
     draggingItems.push_back(i);
    }
   }
  }

  if (!InputHandler::down(binds::UseTool))
  {
   if (index != -1 && draggingItems.size() > 1)
   {
    for (int i = 0; i < draggingItems.size(); i++)
    {
     sf::Vector2f pos = (sf::Vector2f)tilePos;
     pos += sf::Vector2f(rand() % 1000, rand() % 1000) / 1000.f;
     pos.x *= TILE_SIZE.x;
     pos.y *= TILE_SIZE.y;
     p->items[draggingItems[i]].position = pos;
     p->MoveItem(draggingItems[i]);
    }
   }
   draggingItems = {};
  }
  else
  {
   sf::Vector2f offset = p->camera.WorldMousePos();
   for (int i = 0; i < draggingItems.size(); i++)
   {
    sf::Vector2f stackOffset(0.f, 1.f * i);
    p->items[draggingItems[i]].position = offset - stackOffset;
    p->items[draggingItems[i]].moveDir = sf::Vector2f(0.f, 0.f);
    p->MoveItem(draggingItems[i]);
   }
  }
  if (draggingItems.size() == 0 && hoveringItem == nullptr)
  {
   if (InputHandler::pressed(binds::UseTool) && index != -1)
   {
    structureStartDraggingPos = mousePos;
    draggingStructure = index;
   }
   else if (InputHandler::pressed(binds::RotateStructure) && index != -1)
   {
    p->structures[index]->SetDirection((p->structures[index]->direction + 1) % 4);
    p->updateNeighbours = true;
   }
   else if (InputHandler::pressed(binds::FlipStructure) && index != -1)
   {
    p->structures[index]->SetFlipped(!p->structures[index]->isFlipped);
    p->updateNeighbours = true;
   }
  }
 }






 else if (selectedTool == 2)
 {
  if (index != -1)
  {
   Structure* s = p->structures[index];
   sf::Vector2i coords = (s->position + p->GetChunk(s->chunkID)->position * CHUNK_SIZE);
   sf::Vector2f tileSize = (sf::Vector2f)s->tileSize - sf::Vector2f(1.f, 1.f);
   ShowSelectArea(coords, tileSize.x, tileSize.y, sf::Color::Red);
  }
  if (InputHandler::down(binds::UseTool) && index != -1)
  {
   if (p->structures[index]->placedByPlayer)
   {
    int type = p->structures[index]->typeID;
    auto cost = ResourceHandler::GetCost(type);
    sf::Vector2f pos = (sf::Vector2f)(p->structures[index]->position + p->GetChunk(p->structures[index]->chunkID)->position * CHUNK_SIZE);
    pos += (sf::Vector2f)(p->structures[index]->tileSize) / 2.f;
    pos.x *= TILE_SIZE.x;
    pos.y *= TILE_SIZE.y;
    for (int i = 1; i < cost.size(); i += 2)
    {
     for (int j = 0; j < cost[i + 1]; j++)
     {
      sf::Vector2f randPos(rand() % 1000 - 500, rand() % 1000 - 500);
      randPos.x *= (p->structures[index]->tileSize.x / 2.f);
      randPos.y *= (p->structures[index]->tileSize.y / 2.f);
      randPos /= 500.f;
      randPos.x *= TILE_SIZE.x;
      randPos.y *= TILE_SIZE.y;

      Item item = Item(pos + randPos, -1, cost[i]);
      item.SetParent(-1);
      p->AddItem(item);
      p->MoveItem(item.id);
     }
    }

    p->structures[index]->Destroy();
    p->RemoveStructure(index);
   }
  }
  if (InputHandler::pressed(binds::UseTool))
  {
   int index = p->StructureInPos(tilePos);
   if (index != -1)
   {
    Structure* s = p->structures[index];
    if (s->typeID == 2)
    {
     Tree* t = dynamic_cast<Tree*>(s);
     t->health--;
     if (t->health <= 0)
     {
      t->Destroy();
      p->RemoveStructure(index);
     }
    }
    else if (s->typeID == 5)
    {
     Boulder* t = dynamic_cast<Boulder*>(s);
     t->health--;
     if (t->health <= 0)
     {
      t->Destroy();
      p->RemoveStructure(index);
     }
    }
   }
  }
 }
 index = p->StructureInPos(tilePos);
 if (index != -1 && ((selectedTool == 1 && hoveringItem == nullptr && draggingItems.size() == 0)))
 {
  Structure* s = p->structures[index];
  sf::Vector2i coords = (s->position + p->GetChunk(s->chunkID)->position * CHUNK_SIZE);
  sf::Vector2f tileSize = (sf::Vector2f)s->tileSize - sf::Vector2f(1.f, 1.f);
  ShowSelectArea(coords, tileSize.x, tileSize.y, sf::Color::White);
 }

 if (selectedTool != 0)
 {
  ClearTally();
 }
}

void ToolHandler::ShowInsufficient()
{
 if (insufficientLabel == nullptr)
 {
  insufficientLabel = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.3f, 0.1f), "Insufficient Resources");
  insufficientLabel->SetColor(sf::Color::Red);
  guihandler.guis[5]->AddObject(insufficientLabel);
 }
 insufficientTimer.restart();
}

Structure* ToolHandler::CreateStructure(int type)
{
 if (type == 1)
 {
  return new StorageSilo(-2, game->activePlanet, placeDir);
 }
 else if (type == 3)
 {
  return new TreeChopper(-2, game->activePlanet, placeDir);
 }
 else if (type == 4)
 {
  return new SaplingPlanter(-2, game->activePlanet, placeDir);
 }
 else if (type == 6)
 {
  return new Drill(-2, game->activePlanet, placeDir);
 }
 else if (type == 7)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 7);
 }
 else if (type == 8)
 {
  return new RefinedDrill(-2, game->activePlanet, placeDir);
 }
 else if (type == 9)
 {
  return new Distributor(-2, game->activePlanet, placeDir);
 }
 else if (type == 10)
 {
  return new Underground(-2, game->activePlanet, placeDir);
 }
 else if (type == 11)
 {
 }
 else if (type == 12)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 12);
 }
 else if (type == 13)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 13);
 }
 else if (type == 14)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 14);
 }
 else if (type == 15)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 15);
 }
 else if (type == 16)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 16);
 }
 else if (type == 17)
 {
  return new FilterConveyor(-2, game->activePlanet, placeDir);
 }
 else if (type == 18)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 18);
 }
 else if (type == 19)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 19);
 }
 else if (type == 20)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 20);
 }
 else if (type == 21)
 {
  return new RecipeStructure(-2, game->activePlanet, placeDir, 21);
 }
 else if (type == 22)
 {
  return new RocketSilo(-2, game->activePlanet, placeDir, 22);
 }
 else
 {
  return nullptr;
 }
}

void ToolHandler::Render()
{

 for (int i = 0; i < selectedImages.size(); i++)
 {
  int j = guihandler.guis[5]->GetIndex(selectedImages[i]);
  guihandler.guis[5]->RemoveObject(j);
  delete selectedImages[i];
 }
 selectedImages = {};
}

void ToolHandler::ReloadTally(sf::Vector2i tilePos)
{

 auto cost = ResourceHandler::GetCost(placeType);
 std::vector<int> types = {};
 for (int i = 1; i < cost.size(); i += 2)
 {
  types.push_back(cost[i]);
 }
 Planet& p = game->planets[game->activePlanet];
 std::vector<int> tally = p.TallyResources(tilePos, types);
 GUI* g = guihandler.guis[5];
 for (int i = 0; i < tallyObjs.size(); i++)
 {
  g->RemoveObject(g->GetIndex(tallyObjs[i]));
  delete tallyObjs[i];
 }
 tallyObjs = {};
 float width = 0.03f;
 float totalWidth = (tally.size() * 2.f) * width * 2.f;
 float y = 0.75f;
 sf::Vector2f startPos(0.5f - totalWidth / 2.f, y);
 sf::Vector2f endPos(0.5f + totalWidth / 2.f, y);
 int N = tally.size() * 2;
 for (int i = 0; i < tally.size(); i++)
 {
  int index = 2 * i + 1;

  sf::Vector2f pos1 = Lerp(startPos, endPos, (index * 2.f - 1.f) / (N * 2.f));
  sf::Vector2f pos2 = Lerp(startPos, endPos, ((index + 1) * 2.f - 1.f) / (N * 2.f));
  std::string str = std::to_string(tally[i]);
  str += " / ";
  str += std::to_string(cost[i * 2 + 2]);
  GUILabel* l = new GUILabel(pos2, sf::Vector2f(width, width), str);
  GUIItem* item = new GUIItem(pos1, sf::Vector2f(width, width), cost[i * 2 + 1], 0);
  item->Update(0.f);
  tallyObjs.push_back(l);
  tallyObjs.push_back(item);
  g->AddObject(l);
  g->AddObject(item);
 }
}

void ToolHandler::ClearTally()
{
 for (int i = 0; i < tallyObjs.size(); i++)
 {
  guihandler.guis[5]->RemoveObject(guihandler.guis[5]->GetIndex(tallyObjs[i]));
  delete tallyObjs[i];
 }
 tallyObjs = {};
}

void ToolHandler::ShowSelectArea(sf::Vector2i pos, int width, int height, sf::Color col)
{
 std::vector<GUIImage*> selectedImages = {};
 for (int i = 0; i < 4; i++)
 {
  selectedImages.push_back(new GUIImage(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), "content\\resources\\images\\selection" + std::to_string(i + 1) + ".png"));
  selectedImages[i]->keepAspectRatio = true;
 }
 Planet* p = game->ActivePlanet();
 sf::Vector2f tl = p->camera.tileToGUIPos({ 0.f, 0.f });
 sf::Vector2f br = p->camera.tileToGUIPos({ 1.f, 1.f });
 sf::Vector2f size = (br - tl) / 2.f;
 sf::Vector2f pos2 = (sf::Vector2f)pos;
 selectedImages[0]->position = p->camera.tileToGUIPos(pos2 + sf::Vector2f(0.f, 0.f) + sf::Vector2f(0.5f, 0.5f));
 selectedImages[0]->size = size;
 selectedImages[1]->position = p->camera.tileToGUIPos(pos2 + sf::Vector2f(width, 0.f) + sf::Vector2f(0.5f, 0.5f));
 selectedImages[1]->size = size;
 selectedImages[2]->position = p->camera.tileToGUIPos(pos2 + sf::Vector2f(width, height) + sf::Vector2f(0.5f, 0.5f));
 selectedImages[2]->size = size;
 selectedImages[3]->position = p->camera.tileToGUIPos(pos2 + sf::Vector2f(0.f, height) + sf::Vector2f(0.5f, 0.5f));
 selectedImages[3]->size = size;
 for (int i = 0; i < 4; i++)
 {
  selectedImages[i]->sprite.setColor(col);
  this->selectedImages.push_back(selectedImages[i]);
  guihandler.guis[5]->InsertObject(selectedImages[i], 0);
 }
}
