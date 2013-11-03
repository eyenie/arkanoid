#ifndef GAMEOBJBALL_H_
#define GAMEOBJBALL_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjBall : public GameObj {
public:
    GameObjBall(const GameObjProp& prop, BillboardAtlas *mBBAtlas, b2World *mB2World);
    virtual ~GameObjBall();

    void update(double dt);
    typ type() { return BALL; }
private:
};


#endif /* end of include guard: GAMEOBJBALL_H_ */
