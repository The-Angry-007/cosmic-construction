# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxShape.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxShape.cpp"
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
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/hitboxes/HitboxShape.cpp" 2


HitboxShape::HitboxShape()
{}


HitboxShape::~HitboxShape()
{}

void HitboxShape::SetTransform(sf::Vector2f position, sf::Vector2f size)
{
 currentPos = this->position + position;
 currentSize = sf::Vector2f(this->size.x * size.x, this->size.y * size.y);
}

void HitboxShape::ResetTransform()
{
 currentPos = position;
 currentSize = size;
}


bool HitboxShape::intersects(HitboxShape* other)
{
 return false;
}

void HitboxShape::Display(bool colliding)
{
 return;
}

bool HitboxShape::intersectsPoint(sf::Vector2f point)
{
 return false;
}
