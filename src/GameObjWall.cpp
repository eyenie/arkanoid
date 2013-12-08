#include "Game.h"
#include "GameObjWall.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjWall::GameObjWall(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) : GameObj(mgr, bb, body)
{
    b2PolygonShape shape;
    shape.SetAsBox(getWidth() / GameObjManager::PPM / 2, getHeight() / GameObjManager::PPM / 2);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.filter.categoryBits = GameObj::WALL;
    fd.filter.maskBits = GameObj::BALL;
    boxBody->CreateFixture(&fd);
}

GameObjWall::~GameObjWall() 
{
}

void GameObjWall::update(double dt)
{
}
