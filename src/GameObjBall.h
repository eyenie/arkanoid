#ifndef GAMEOBJBALL_H_
#define GAMEOBJBALL_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjBall : public GameObj {
public:
    GameObjBall(Game* game, const GameObjProp& prop);
    virtual ~GameObjBall();

    void update(double dt);
    type_ type() { return BALL; }
private:
};


#endif /* end of include guard: GAMEOBJBALL_H_ */
