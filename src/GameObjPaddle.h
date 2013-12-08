#ifndef GAMEOBJPADDLE_H_
#define GAMEOBJPADDLE_H_

#include "GameObj.h"
#include "GameObjManager.h"

class b2World;

class GameObjPaddle : public GameObj {
public:
    GameObjPaddle(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body);
    virtual ~GameObjPaddle() {}

    void update(double dt);
    void setBounds(float left, float right);
private:
    float maxLeft;
    float maxRight;
};


#endif /* end of include guard: GAMEOBJPADDLE_H_ */
