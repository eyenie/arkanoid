#ifndef GAMEOBJWALL_H_
#define GAMEOBJWALL_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjWall : public GameObj {
public:
    GameObjWall(Game* game, const GameObjProp& prop);
    virtual ~GameObjWall();

    void update(double dt);
    type_ type() { return WALL; }
private:
};


#endif /* end of include guard: GAMEOBJWALL_H_ */
