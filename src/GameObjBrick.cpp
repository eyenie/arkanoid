#include "Game.h"
#include "GameObjBrick.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjBrick::GameObjBrick(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) : GameObj(mgr, bb, body)
{
}

GameObjBrick::~GameObjBrick() 
{
}

void GameObjBrick::update(double dt)
{
}
