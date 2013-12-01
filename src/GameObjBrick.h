#ifndef GAMEOBJBRICK_H_
#define GAMEOBJBRICK_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjBrick : public GameObj {
public:
    GameObjBrick(Game* game, const GameObjProp& prop);
    virtual ~GameObjBrick();

    void update(double dt);
    type_ type() { return BRICK; }

private:

};


#endif /* end of include guard: GAMEOBJBRICK_H_ */
