#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_

#include <string>

class b2Body;
namespace Ogre {
    class Billboard;
}

struct GameObjProp {
    std::string filename;
    float x;
    float y;
    float width;
    float height;
};

class GameObj {
public:
    enum typ {BALL, BRICK, WALL};

    GameObj() : mB2Body(0), mBillboard(0) {};
    virtual void update(double dt) = 0;
    virtual typ type() = 0;
    virtual ~GameObj();

    b2Body *body() { return mB2Body; }
    Ogre::Billboard *billboard() { return mBillboard; }


protected:
    b2Body* mB2Body;
    Ogre::Billboard* mBillboard;
};

#endif /* end of include guard: GAMEOBJ_H_ */
