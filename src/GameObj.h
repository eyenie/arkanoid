#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_

#include <string>

class b2Body;
class Game;
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
    typedef std::shared_ptr<GameObj> SharedPtr;

    enum type_ {
        BALL  = 0x01, 
        BRICK = 0x02, 
        WALL  = 0x04
    };

    enum state_ {
        DESTROYED,
        ACTIVE
    };

    GameObj(Game *game) : mGame(game), mB2Body(0), mBillboard(0), mState(ACTIVE) {};
    virtual void update(double dt) = 0;
    virtual type_ type() = 0;
    virtual ~GameObj();

    state_ state() { return mState; }
    b2Body *body() { return mB2Body; }
    Ogre::Billboard *billboard() { return mBillboard; }

    void setState(state_ s) { mState = s; }


protected:
    Game *mGame;
    b2Body* mB2Body;
    Ogre::Billboard* mBillboard;
    enum state_ mState;
};

#endif /* end of include guard: GAMEOBJ_H_ */
