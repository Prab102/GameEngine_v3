#include "Physics.h"
#include "Components.h"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    //return the overlap rectangle size of the bounding boxes of the entity a and b
    //b is generally tile
    // std::cout << "this is pos x " << a->getComponent<CTransform>().pos.x <<std::endl;
    // std::cout << "this is pos y " << a->getComponent<CTransform>().pos.y <<std::endl;
    Vec2 delta(abs(a->getComponent<CTransform>().pos.x - b->getComponent<CTransform>().pos.x), abs(a->getComponent<CTransform>().pos.y - b->getComponent<CTransform>().pos.y));
    float ox = (a->getComponent<CBoundingBox>().halfSize.x) + (b->getComponent<CBoundingBox>().halfSize.x) - delta.x;
    float oy = (a->getComponent<CBoundingBox>().halfSize.y) + (b->getComponent<CBoundingBox>().halfSize.y) - delta.y;
    
    
    return Vec2(ox,oy);
}

Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    //return the previous overlap recatangle size of the bounding boxes of a and b, use the entitys previous position
    // std::cout << "this is pos x " << a->getComponent<CTransform>().pos.x <<std::endl;
    // std::cout << "this is pos y " << a->getComponent<CTransform>().pos.y <<std::endl;
    // std::cout << "this is previous pos x " << a->getComponent<CTransform>().prevPos.x <<std::endl;
    // std::cout << "this is previous pos y " << a->getComponent<CTransform>().prevPos.y <<std::endl;

    Vec2 delta(abs(a->getComponent<CTransform>().prevPos.x - b->getComponent<CTransform>().prevPos.x), abs(a->getComponent<CTransform>().prevPos.y - b->getComponent<CTransform>().prevPos.y));
    float ox = (a->getComponent<CBoundingBox>().halfSize.x) + (b->getComponent<CBoundingBox>().halfSize.x) - delta.x;
    float oy = (a->getComponent<CBoundingBox>().halfSize.y) + (b->getComponent<CBoundingBox>().halfSize.y) - delta.y;
    return Vec2(ox,oy);
}