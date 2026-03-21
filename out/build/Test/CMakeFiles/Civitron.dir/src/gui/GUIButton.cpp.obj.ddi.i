# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.cpp"
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.cpp" 2
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/ClickFuncs.hpp" 1
       

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
# 3 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.cpp" 2
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
# 4 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/gui/GUIButton.cpp" 2


GUIButton::GUIButton(sf::Vector2f position, sf::Vector2f size, GUIObject* bgObj, GUIObject* labelObj)
{
 this->position = position;
 this->size = size;

 this->bgObj = bgObj;
 this->labelObj = labelObj;

 bgObj->blocksMouseInput = true;

 clickFunc = ClickFuncs::blankFunc;
 this->dimObj = new GUIPanel(position, size, sf::Color(0, 0, 0, 100));
 hitbox = nullptr;
}
void GUIButton::Render()
{

 bgObj->Render();
 if (isBlockingMouse() && dimObj != nullptr)
 {
  dimObj->Render();
 }

 if (labelObj != nullptr)
 {
  labelObj->Render();
 }
}
void GUIButton::Update(float dt)
{

 bgObj->Update(dt);
 if (labelObj != nullptr)
 {
  labelObj->Update(dt);
 }

 if (isClicked())
 {
  clickFunc();
 }
}

GUIButton::~GUIButton()
{
 delete bgObj;
 if (labelObj != nullptr)
 {
  delete labelObj;
 }
}

bool GUIButton::isBlockingMouse()
{
 return bgObj->isBlockingMouse();
}

bool GUIButton::isClicked()
{
 return bgObj->isClicked();
}
