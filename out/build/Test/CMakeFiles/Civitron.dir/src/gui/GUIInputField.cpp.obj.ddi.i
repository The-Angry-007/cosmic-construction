# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.hpp" 1
       
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUILabel.hpp" 1
       
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUILabel.hpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.hpp" 2


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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.cpp" 2
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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIInputField.cpp" 2

GUIInputField::GUIInputField(sf::Vector2f position, sf::Vector2f size)
{
 this->position = position;
 this->size = size;
 label = new GUILabel(position, size, "");
 label->SetColor(sf::Color::Black);
 label->text.setStyle(label->text.Italic);
 cursorPos = 0;
 changed = false;
 focused = false;
 value = "";
 hitbox = new Hitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));
 hitbox->AddShape(new HitboxRect(position, size));
 blocksMouseInput = true;
}

void GUIInputField::Update(float dt)
{
 if (!focused)
 {
  displayValue = value;
  if (isClicked())
  {
   focused = true;
   cursorPos = value.length() - 1;
   if (!changed)
   {
    changed = true;
    value = "";
    cursorPos = -1;
   }
  }
 }
 else
 {
  std::string t = InputHandler::typedText;
  for (int i = 0; i < t.length(); i++)
  {
   if (t[i] != '\b')
   {
    value.insert(value.begin() + cursorPos + 1, t[i]);
    cursorPos++;
   }
   else
   {
    if (value.length() > 0)
    {
     if (cursorPos != -1)
     {
      value.erase(value.begin() + cursorPos);
      cursorPos--;
     }
    }
   }
  }
  displayValue = "";
  for (int i = 0; i < value.length(); i++)
  {
   displayValue += value[i];
   if (i == cursorPos)
   {
    displayValue += '|';
   }
  }
  if (value.length() == 0)
  {
   displayValue += "|";
  }
  if (InputHandler::mbPressed(sf::Mouse::Button::Left) && !isClicked())
  {
   focused = false;
   displayValue = value;
  }
  if (InputHandler::keyPressed(sf::Keyboard::Left))
  {
   cursorPos--;
   if (cursorPos < -1)
   {
    cursorPos = -1;
   }
  }
  if (InputHandler::keyPressed(sf::Keyboard::Right))
  {
   cursorPos++;
   if (cursorPos > value.length() - 1)
   {
    cursorPos--;
   }
  }
 }
}
void GUIInputField::SetTextCol(sf::Color color)
{
 label->SetColor(color);
}

GUIInputField::~GUIInputField()
{
 delete label;
}
void GUIInputField::Render()
{
 label->value = displayValue;
 label->Render();
}
