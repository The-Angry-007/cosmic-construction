# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp"
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/Main.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game.hpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Camera.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Camera.hpp" 2
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
       

# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/Structure.hpp" 1
       


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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp" 2


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
# 7 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/Settings.cpp" 2
Settings::Settings()
{


 GUIObjects = {};

 bgGUI = new GUI();
 {
  GUIPanel* dimmer = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.5f, 0.5f), sf::Color(0, 0, 0, 150));
  bgGUI->AddObject(dimmer);
  GUIPanel* p = new GUIPanel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.4f, 0.4f), sf::Color(150, 150, 150));

  bgGUI->AddObject(p);
  GUIPanel* topPanel = new GUIPanel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.4f, 0.03f), sf::Color(125, 125, 125));
  bgGUI->AddObject(topPanel);
 }
 pageGuis = {};

 {
  GUI* g = new GUI();
  GUIImage* i = new GUIImage(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f, 0.04f), "content/resources/images/buttonBezels.png");
  GUILabel* l = new GUILabel(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f - 0.01f, 0.04f - 0.01f), "Controls");
  l->SetColor(sf::Color::Black);
  GUIButton* b = new GUIButton(sf::Vector2f(0.33f, 0.22f), sf::Vector2f(0.15f, 0.04f), i, l);
  g->AddObject(b);

  GUIImage* i2 = new GUIImage(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f, 0.04f), "content/resources/images/buttonBezels.png");
  GUILabel* l2 = new GUILabel(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f - 0.01f, 0.04f - 0.01f), "Audio");
  l2->SetColor(sf::Color::Black);
  GUIButton* b2 = new GUIButton(sf::Vector2f(0.67f, 0.22f), sf::Vector2f(0.15f, 0.04f), i2, l2);
  g->AddObject(b2);

  GUILabel* l3 = new GUILabel(sf::Vector2f(0.5f, 0.3f), sf::Vector2f(0.35f, 0.025f), "Framerate:");
  l3->SetColor(sf::Color::Black);
  g->AddObject(l3);
  GUIPanel* sliderBG = new GUIPanel(sf::Vector2f(0.5f, 0.37f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
  GUIImage* sliderKnob = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "content/resources/images/squareButton.png");
  sliderKnob->keepAspectRatio = true;
  GUISlider* s = new GUISlider(sf::Vector2f(0.5f, 0.37f), sf::Vector2f(0.35f, 0.015f), sliderKnob, sliderBG, nullptr);
  g->AddObject(s);
  s->value = 0.f;
  s->minVal = 0;
  s->maxVal = 260;
  s->numSteps = 26;
  saveInterval = 5;

  GUILabel* l4 = new GUILabel(sf::Vector2f(0.5f, 0.45f), sf::Vector2f(0.35f, 0.025f), "Autosave Interval:");
  l4->SetColor(sf::Color::Black);
  g->AddObject(l4);
  GUIPanel* sliderBG2 = new GUIPanel(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
  GUIImage* sliderKnob2 = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "content/resources/images/squareButton.png");
  sliderKnob2->keepAspectRatio = true;
  GUISlider* s2 = new GUISlider(sf::Vector2f(0.5f, 0.53f), sf::Vector2f(0.35f, 0.015f), sliderKnob2, sliderBG2, nullptr);
  g->AddObject(s2);
  s2->minVal = 5;
  s2->maxVal = 65;
  s2->numSteps = 12;
  s2->value = 0.f;

  GUIImage* i3 = new GUIImage(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), "content/resources/images/buttonBezels.png");
  GUILabel* l5 = new GUILabel(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f - 0.01f, 0.04f - 0.01f), "Go Back");
  l5->SetColor(sf::Color::Black);
  GUIButton* b3 = new GUIButton(sf::Vector2f(0.5f, 0.75f), sf::Vector2f(0.3f, 0.04f), i3, l5);
  g->AddObject(b3);
  std::function<void()> exit = std::bind(&Settings::ExitSettings, this);
  b3->clickFunc = exit;
  GUILabel* optionsLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Options");
  optionsLabel->SetColor(sf::Color::Black);
  g->AddObject(optionsLabel);
  pageGuis.push_back(g);
 }

 {
  GUI* g = new GUI();
  GUILabel* controlsLabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Controls");
  controlsLabel->SetColor(sf::Color::Black);
  g->AddObject(controlsLabel);
  pageGuis.push_back(g);
  selectedBind = -1;
  bindCodes = {};
  bindGUIs = {};
  AddBind("Pause", &binds::Pause);
  AddBind("Fullscreen", &binds::Fullscreen);
  AddBind("Camera Pan", &binds::Pan);
  AddBind("Use Tool", &binds::UseTool);
  AddBind("Tool 1", &binds::Tool1);
  AddBind("Tool 2", &binds::Tool2);
  AddBind("Tool 3", &binds::Tool3);
  AddBind("Close Inventory", &binds::CloseInventory);
  AddBind("Rotate Structure", &binds::RotateStructure);
  AddBind("Flip Structure", &binds::FlipStructure);
 }

 {
  GUI* g = new GUI();
  GUILabel* audiolabel = new GUILabel(sf::Vector2f(0.5f, 0.13f), sf::Vector2f(0.9f, 0.025f), "Audio");
  audiolabel->SetColor(sf::Color::Black);
  g->AddObject(audiolabel);
  GUILabel* l = new GUILabel(sf::Vector2f(0.5f, 0.2f), sf::Vector2f(0.35f, 0.025f), "Master Volume: ");
  l->SetColor(sf::Color::Black);
  g->AddObject(l);
  GUIPanel* sliderBG = new GUIPanel(sf::Vector2f(0.5f, 0.25f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
  GUIImage* sliderKnob = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "content/resources/images/squareButton.png");
  sliderKnob->keepAspectRatio = true;
  GUISlider* s = new GUISlider(sf::Vector2f(0.5f, 0.25f), sf::Vector2f(0.35f, 0.015f), sliderKnob, sliderBG, nullptr);
  g->AddObject(s);

  GUILabel* l2 = new GUILabel(sf::Vector2f(0.5f, 0.35f), sf::Vector2f(0.35f, 0.025f), "Music Volume: ");
  l2->SetColor(sf::Color::Black);
  g->AddObject(l2);
  GUIPanel* sliderBG2 = new GUIPanel(sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
  GUIImage* sliderKnob2 = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "content/resources/images/squareButton.png");
  sliderKnob2->keepAspectRatio = true;
  GUISlider* s2 = new GUISlider(sf::Vector2f(0.5f, 0.4f), sf::Vector2f(0.35f, 0.015f), sliderKnob2, sliderBG2, nullptr);
  g->AddObject(s2);

  GUILabel* l3 = new GUILabel(sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.35f, 0.025f), "Sound Effects Volume: ");
  l3->SetColor(sf::Color::Black);
  g->AddObject(l3);
  GUIPanel* sliderBG3 = new GUIPanel(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.35f, 0.015f), sf::Color(50, 50, 50));
  GUIImage* sliderKnob3 = new GUIImage(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.025f, 0.025f), "content/resources/images/squareButton.png");
  sliderKnob3->keepAspectRatio = true;
  GUISlider* s3 = new GUISlider(sf::Vector2f(0.5f, 0.55f), sf::Vector2f(0.35f, 0.015f), sliderKnob3, sliderBG3, nullptr);
  g->AddObject(s3);
  pageGuis.push_back(g);
 }
 currentGUI = 0;
 masterVolume = 1.f;
 musicVolume = 1.f;
 effectsVolume = 1.f;


 std::string dir = SaveHandler::workingDir;
 SaveHandler::ResetWorkingDir();
 saveDir = SaveHandler::workingDir + "\\settings.txt";
 SaveHandler::workingDir = dir;

 std::string data = SaveHandler::ReadData(saveDir);
 auto lines = Split(data, '\n');

 if (lines.size() == 1)
 {
  SaveSettings();
 }
 else
 {
  LoadSettings();
 }
}
void Settings::LoadSettings()
{
 auto data = SaveHandler::ReadData(saveDir);
 auto lines = Split(data, '\n');
 uint numLines = lines.size();

 numLines -= 5;
 framerate = std::stoi(lines[0]);
 GUI* cGUI = pageGuis[0];
 GUISlider* s1 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[3]);
 if (framerate == -1)
 {
  window->setFramerateLimit(1000);
  window->setVerticalSyncEnabled(true);
  s1->value = 0;
 }
 else if (framerate == 10000)
 {
  window->setVerticalSyncEnabled(false);
  window->setFramerateLimit(10000);

  s1->value = 1.f;
 }
 else
 {
  window->setVerticalSyncEnabled(false);
  window->setFramerateLimit(framerate);
  s1->value = ((float)framerate) / 260.f;
 }
 saveInterval = std::stoi(lines[1]);
 GUISlider* s2 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[5]);
 if (saveInterval == -1)
 {
  s2->value = 1.f;
 }
 else
 {
  s2->value = (saveInterval - 5.f) / 65.f;
 }
 masterVolume = std::stof(lines[2]);
 musicVolume = std::stof(lines[3]);
 effectsVolume = std::stof(lines[4]);
 GUI* g = pageGuis[2];
 dynamic_cast<GUISlider*>(g->GUIObjects[2])->value = masterVolume;
 dynamic_cast<GUISlider*>(g->GUIObjects[4])->value = musicVolume;
 dynamic_cast<GUISlider*>(g->GUIObjects[6])->value = effectsVolume;
 for (uint i = 0; i < numLines; i++)
 {
  *bindCodes[i] = std::stoi(lines[i + 5]);
  std::string str = binds::GetName(*bindCodes[i]);
  if (str.size() < 5)
  {
   str = "  " + str + "  ";
  }
  dynamic_cast<GUILabel*>(bindGUIs[i]->GUIObjects[2])->value = str;
 }
}
void Settings::SaveSettings()
{
 std::vector<std::string> lines = {};

 lines.push_back(std::to_string(framerate));

 lines.push_back(std::to_string(saveInterval));

 lines.push_back(std::to_string(masterVolume));
 lines.push_back(std::to_string(musicVolume));
 lines.push_back(std::to_string(effectsVolume));
 for (uint i = 0; i < bindCodes.size(); i++)
 {
  lines.push_back(std::to_string(*bindCodes[i]));
 }
 std::string data = concat(lines);
 SaveHandler::WriteData(saveDir, data);
}
void Settings::AddBind(std::string label, int* value)
{
 bindCodes.push_back(value);
 GUI* g = new GUI();
 float lowestPos = 0.18f + 0.04f;
 float gap = 0.1f;
 if (bindGUIs.size() > 0)
 {
  lowestPos = bindGUIs[bindGUIs.size() - 1]->GUIObjects[0]->position.y + gap;
 }
 GUILabel* l = new GUILabel(sf::Vector2f(0.3f, lowestPos), sf::Vector2f(0.2f, 0.03f), label);
 l->origin = sf::Vector2f(1.f, 0.5f);
 l->SetColor(sf::Color::Black);
 GUIPanel* p = new GUIPanel(sf::Vector2f(0.66f, lowestPos), sf::Vector2f(0.15f, 0.04f), sf::Color(100, 100, 100));
 p->blocksMouseInput = true;
 GUILabel* l2 = new GUILabel(sf::Vector2f(0.66f, lowestPos), sf::Vector2f(0.1f, 0.03f), binds::GetName(*value));
 l2->SetColor(sf::Color::Black);
 g->AddObject(l);
 g->AddObject(p);
 g->AddObject(l2);
 bindGUIs.push_back(g);
}

void Settings::Update(float dt)
{
 if (InputHandler::pressed(binds::Pause))
 {
  if (currentGUI > 0)
  {
   currentGUI = 0;
   InputHandler::RemovePressed(binds::Pause);
   InputHandler::RemoveDown(binds::Pause);
  }
 }
 behindGUI->Update(dt);
 bgGUI->Update(dt);
 GUI* cGUI = pageGuis[currentGUI];
 cGUI->Update(dt);
 if (currentGUI == 0)
 {
  GUISlider* s1 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[3]);
  GUILabel* l1 = dynamic_cast<GUILabel*>(cGUI->GUIObjects[2]);
  if (s1->value < 0.01f)
  {
   l1->value = "Framerate: Vertical Sync enabled";
   window->setVerticalSyncEnabled(true);
   window->setFramerateLimit(1000);
   framerate = -1;
  }
  else if (s1->value > 0.99f)
  {
   l1->value = "Framerate: Unlimited";
   window->setVerticalSyncEnabled(false);
   window->setFramerateLimit(10000);
   framerate = 10000;
  }
  else
  {
   framerate = round(s1->pValue);
   l1->value = "Framerate: " + std::to_string(framerate) + " fps";
   window->setVerticalSyncEnabled(false);
   window->setFramerateLimit(framerate);
  }
  GUISlider* s2 = dynamic_cast<GUISlider*>(cGUI->GUIObjects[5]);
  GUILabel* l2 = dynamic_cast<GUILabel*>(cGUI->GUIObjects[4]);
  if (s2->value > 0.99f)
  {
   saveInterval = -1;
   l2->value = "Autosave Interval: Never";
  }
  else
  {
   saveInterval = s2->pValue;
   l2->value = "Autosave Interval: " + std::to_string(saveInterval) + " minutes";
  }
  if (cGUI->GUIObjects[0]->isClicked())
  {
   currentGUI = 1;
  }
  else if (cGUI->GUIObjects[1]->isClicked())
  {
   currentGUI = 2;
  }
 }
 else if (currentGUI == 1)
 {
  float move = InputHandler::scroll.y * 0.05f;

  if (move < 0)
  {
   float lowest = bindGUIs[bindGUIs.size() - 1]->GUIObjects[1]->position.y + bindGUIs[0]->GUIObjects[1]->size.y;
   if (lowest - move < 0.87f)
   {
    move = 0.f;
   }
  }
  else if (move > 0)
  {
   float highest = bindGUIs[0]->GUIObjects[1]->position.y - bindGUIs[0]->GUIObjects[1]->size.y;
   if (highest + move > 0.18f)
   {
    move = 0.f;
   }
  }
  for (uint i = 0; i < bindGUIs.size(); i++)
  {
   if (abs(InputHandler::scroll.y) > 0.05f)
   {
    for (uint j = 0; j < bindGUIs[i]->GUIObjects.size(); j++)
    {
     bindGUIs[i]->GUIObjects[j]->position += sf::Vector2f(0.f, move);
    }
   }
   bindGUIs[i]->Update(dt);
   if (selectedBind == -1)
   {
    if (bindGUIs[i]->GUIObjects[1]->isClicked())
    {
     selectedBind = i;
     InputHandler::RemoveMbPressed(sf::Mouse::Button::Left);
     InputHandler::RemoveMbDown(sf::Mouse::Button::Left);
     dynamic_cast<GUILabel*>(bindGUIs[i]->GUIObjects[2])->value = "   ...   ";
    }
   }
  }
  if (selectedBind != -1)
  {
   if (InputHandler::keysPressed.size() > 0)
   {
    int code = binds::keyToCode(InputHandler::keysPressed[0]);
    *bindCodes[selectedBind] = code;
    std::string str = binds::GetName(code);
    if (str.size() < 5)
    {
     str = "  " + str + "  ";
    }
    dynamic_cast<GUILabel*>(bindGUIs[selectedBind]->GUIObjects[2])->value = str;
    selectedBind = -1;
    InputHandler::RemoveKeyPressed(InputHandler::keysPressed[0]);
    InputHandler::RemoveKeyDown(InputHandler::keysPressed[0]);
   }
   else if (InputHandler::mouseButtonsPressed.size() > 0)
   {
    int code = binds::buttonToCode(InputHandler::mouseButtonsPressed[0]);
    *bindCodes[selectedBind] = code;
    dynamic_cast<GUILabel*>(bindGUIs[selectedBind]->GUIObjects[2])->value = binds::GetName(code);
    selectedBind = -1;
    InputHandler::RemoveMbPressed(InputHandler::mouseButtonsPressed[0]);
    InputHandler::RemoveMbDown(InputHandler::mouseButtonsPressed[0]);
   }
  }
 }
 else if (currentGUI == 2)
 {
  GUI* g = pageGuis[2];
  masterVolume = dynamic_cast<GUISlider*>(g->GUIObjects[2])->value;
  musicVolume = dynamic_cast<GUISlider*>(g->GUIObjects[4])->value;
  effectsVolume = dynamic_cast<GUISlider*>(g->GUIObjects[6])->value;
  dynamic_cast<GUILabel*>(g->GUIObjects[1])->value = "Master Volume: " + std::to_string((int)(dynamic_cast<GUISlider*>(g->GUIObjects[2])->value * 100)) + "%";
  dynamic_cast<GUILabel*>(g->GUIObjects[3])->value = "Music Volume: " + std::to_string((int)(dynamic_cast<GUISlider*>(g->GUIObjects[4])->value * 100)) + "%";
  dynamic_cast<GUILabel*>(g->GUIObjects[5])->value = "Sound Effects Volume: " + std::to_string((int)(dynamic_cast<GUISlider*>(g->GUIObjects[6])->value * 100)) + "%";
 }
}

void Settings::Render()
{
 behindGUI->Render();
 bgGUI->Render();
 pageGuis[currentGUI]->Render();
 if (currentGUI == 1)
 {
  sf::RenderTexture text;
  text.create(width, height);
  text.setView(sf::View(sf::Vector2f(width / 2.f, height / 2.f), sf::Vector2f(width, height)));
  text.clear(sf::Color::Transparent);
  for (uint i = 0; i < bindGUIs.size(); i++)
  {
   bindGUIs[i]->RenderToTexture(&text);
  }
  text.display();
  sf::Sprite s(text.getTexture());
  sf::IntRect bounds(sf::Vector2i(width * 0.1f, height * 0.16f), sf::Vector2i(width * 0.8f, height * (0.8f - 0.06f)));
  s.setTextureRect(bounds);
  s.setPosition(bounds.left, bounds.top);
  s.setOrigin(0.f, 0.f);

  window->draw(s);
 }
}

Settings::~Settings()
{
 delete behindGUI;
 delete bgGUI;
 for (uint i = 0; i < pageGuis.size(); i++)
 {
  delete pageGuis[i];
 }
}
void Settings::ExitSettings()
{
 SaveSettings();
 guihandler.GoBack();
}
