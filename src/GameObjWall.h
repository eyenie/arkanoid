#ifndef GAMEOBJWALL_H_
#define GAMEOBJWALL_H_

#include "GameObj.h"
#include "GameObjManager.h"
class b2World;

class GameObjWall : public GameObj {
public:
    GameObjWall(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body);
    virtual ~GameObjWall();

    void update(double dt);
private:
};


#endif /* end of include guard: GAMEOBJWALL_H_ */
