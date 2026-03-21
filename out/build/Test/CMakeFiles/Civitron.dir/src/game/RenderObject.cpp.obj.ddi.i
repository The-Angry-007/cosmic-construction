# 0 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RenderObject.cpp"
# 1 "C:\\Users\\kiera\\Documents\\GitHub\\cosmic-construction\\out\\build\\Test//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RenderObject.cpp"
# 1 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RenderObject.hpp" 1
       

struct RenderObject
{
 sf::Sprite* sprite;
 int zindex;
};
bool operator<(const RenderObject& lhs, const RenderObject& rhs);
# 2 "C:/Users/kiera/Documents/GitHub/cosmic-construction/src/game/RenderObject.cpp" 2

bool operator<(const RenderObject& lhs, const RenderObject& rhs)
{
 float y1 = lhs.sprite->getPosition().y + lhs.zindex;
 float y2 = rhs.sprite->getPosition().y + rhs.zindex;
 if (y1 != y2)
 {
  return y1 < y2;
 }
 return lhs.sprite->getPosition().x < rhs.sprite->getPosition().x;
}
