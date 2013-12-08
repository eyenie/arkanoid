#ifndef GAMEOBJPADDLE_H_
#define GAMEOBJPADDLE_H_

#include "GameObj.h"
class BillboardAtlas;
class b2World;

class GameObjPaddle : public GameObj {
public:
    GameObjPaddle(Game* game, const GameObjProp& prop, float left, float right);
    virtual ~GameObjPaddle();

    void update(double dt);
    void setMinMaxX(float min, float max);
    type_ type() { return WALL; }
private:
    float minX;
    float maxX;
};


#endif /* end of include guard: GAMEOBJPADDLE_H_ */
