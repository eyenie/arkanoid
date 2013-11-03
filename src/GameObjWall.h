#ifndef GAMEOBJWALL_H_
#define GAMEOBJWALL_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjWall : public GameObj {
public:
    GameObjWall(const GameObjProp& prop, BillboardAtlas *mBBAtlas, b2World *mB2World);
    virtual ~GameObjWall();

    void update(double dt);
    typ type() { return WALL; }
private:
};


#endif /* end of include guard: GAMEOBJWALL_H_ */
