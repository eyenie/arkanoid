#include "Game.h"
#include "GameObjBall.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjBall::GameObjBall(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) : GameObj(mgr, bb, body)
{
}

GameObjBall::~GameObjBall() 
{
    //TODO
}

void GameObjBall::update(double dt)
{
/*     b2Vec2 pos = mB2Body->GetPosition();
 *     ogreBillboard->setPosition(pos.x * Game::PPM, pos.y * Game::PPM, 0.0f);
 */
}
