#ifndef GAMEOBJ_H_
#define GAMEOBJ_H_

#include <string>
#include <memory>

class b2Body;
class GameObjManager;
namespace Ogre {
    class Billboard;
}

class GameObj {
public:
    typedef std::shared_ptr<GameObj> SharedPtr;

    enum Type {
        BALL   = 0x01, 
        BRICK  = 0x02, 
        PADDLE = 0x04,
        WALL   = 0x08
    };

    enum State {
        ACTIVE,
        DESTROYED
    };

    GameObj(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body);
    virtual ~GameObj();

    virtual void update(double dt) = 0;
    float        getX();
    float        getY();
    void         setPosition(float x, float y);
    float        getWidth();
    float        getHeight();
    State        getState();
    void         setState(State s);
protected:
    GameObjManager *    mManager;
    enum State          mState;
    Ogre::Billboard *   ogreBillboard;
    b2Body *            boxBody;
};

#endif /* end of include guard: GAMEOBJ_H_ */
