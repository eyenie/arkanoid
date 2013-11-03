#ifndef GAMEOBJBRICK_H_
#define GAMEOBJBRICK_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjBrick : public GameObj {
public:
    GameObjBrick(const GameObjProp& prop, BillboardAtlas *mBBAtlas, b2World *mB2World);
    virtual ~GameObjBrick();

    void update(double dt);
    typ type() { return BRICK; }

private:

};


#endif /* end of include guard: GAMEOBJBRICK_H_ */
