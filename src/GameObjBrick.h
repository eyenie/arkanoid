#ifndef GAMEOBJBRICK_H_
#define GAMEOBJBRICK_H_

#include "GameObj.h"
#include "GameObjManager.h"

class b2World;

class GameObjBrick : public GameObj {
public:
    GameObjBrick (GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body);
    virtual ~GameObjBrick();

    void update(double dt);
private:

};


#endif /* end of include guard: GAMEOBJBRICK_H_ */
