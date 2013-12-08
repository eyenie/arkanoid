#ifndef GAMEOBJBALL_H_
#define GAMEOBJBALL_H_

#include "GameObj.h"
#include "GameObjManager.h"

class b2World;

class GameObjBall : public GameObj {
public:
    GameObjBall(GameObjManager* mgr, Ogre::Billboard* bb, b2Body* body);
    virtual ~GameObjBall();

    void update(double dt);
private:
};


#endif /* end of include guard: GAMEOBJBALL_H_ */
