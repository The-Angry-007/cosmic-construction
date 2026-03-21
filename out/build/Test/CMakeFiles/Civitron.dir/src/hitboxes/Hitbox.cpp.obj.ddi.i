# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/Hitbox.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/Hitbox.cpp"
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/Hitbox.cpp" 2

Hitbox::Hitbox(sf::Vector2f position, sf::Vector2f size)
{
 this->position = position;
 this->size = size;
 currentPos = position;
 currentSize = size;
 shapes = {};
}

Hitbox::~Hitbox()
{
 for (uint i = 0; i < shapes.size(); i++)
 {
  delete shapes[i];
 }
}

void Hitbox::AddShape(HitboxShape* shape)
{
 shape->SetTransform(currentPos, currentSize);
 shapes.push_back(shape);
}
void Hitbox::SetTransform(sf::Vector2f position, sf::Vector2f size)
{
 currentPos = this->position + position;
 currentSize = sf::Vector2f(size.x * this->size.x, size.y * this->size.y);
 for (uint i = 0; i < shapes.size(); i++)
 {
  shapes[i]->SetTransform(currentPos, currentSize);
 }
}
void Hitbox::ResetTransform()
{
 currentPos = position;
 currentSize = size;
}

bool Hitbox::intersects(Hitbox* other)
{
 for (uint i = 0; i < shapes.size(); i++)
 {
  for (uint j = 0; j < other->shapes.size(); j++)
  {
   if (shapes[i]->intersects(other->shapes[j]))
   {
    return true;
   }
  }
 }
 return false;
}

void Hitbox::Display(std::vector<Hitbox*> hitboxes)
{

 bool colliding = false;
 for (uint i = 0; i < hitboxes.size(); i++)
 {
  if (hitboxes[i] == this)
  {
   continue;
  }
  if (intersects(hitboxes[i]))
  {
   colliding = true;
   break;
  }
 }

 for (uint i = 0; i < shapes.size(); i++)
 {
  shapes[i]->Display(colliding);
 }
}

bool Hitbox::intersectsPoint(sf::Vector2f point)
{
 for (uint i = 0; i < shapes.size(); i++)
 {
  if (shapes[i]->intersectsPoint(point))
  {
   return true;
  }
 }
 return false;
}
