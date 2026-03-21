# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.hpp" 2
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.cpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUI.cpp" 2

GUI::GUI()
{
 GUIObjects = {};
}

void GUI::AddObject(GUIObject* object)
{
 GUIObjects.push_back(object);
}

void GUI::InsertObject(GUIObject* object, int index)
{
 GUIObjects.insert(GUIObjects.begin() + index, object);
}

int GUI::GetIndex(GUIObject* object)
{
 for (uint i = 0; i < GUIObjects.size(); i++)
 {
  if (GUIObjects[i] == object)
  {
   return i;
  }
 }

 return -1;
}

void GUI::RemoveObject(int index)
{


 GUIObjects.erase(GUIObjects.begin() + index);
}

GUI::~GUI()
{
 for (uint i = 0; i < GUIObjects.size(); i++)
 {
  if (GUIObjects[i] != nullptr)
  {
   delete GUIObjects[i];
  }
 }
}

void GUI::Update(float dt)
{
 for (uint i = 0; i < GUIObjects.size(); i++)
 {
  GUIObjects[i]->Update(dt);
 }
}

void GUI::Render()
{
 for (uint i = 0; i < GUIObjects.size(); i++)
 {
  GUIObjects[i]->Render();
 }
}

void GUI::RenderToTexture(sf::RenderTexture* text)
{
 for (uint i = 0; i < GUIObjects.size(); i++)
 {
  GUIObjects[i]->RenderToTexture(text);
 }
}
