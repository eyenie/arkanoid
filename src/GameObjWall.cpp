#include "Game.h"
#include "GameObjWall.h"
#include "BillboardAtlas.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjWall::GameObjWall(const GameObjProp& prop, BillboardAtlas *mBBAtlas, b2World *mB2World)
{
    mBillboard = mBBAtlas->createBillboard(prop.filename, prop.width, prop.height);
    mBillboard->setPosition(prop.x, prop.y, 0.0f);

    b2BodyDef bd;
    //FIXME
    bd.position.Set(prop.x / Game::PPM, prop.y / Game::PPM); 
    mB2Body = mB2World->CreateBody(&bd);

    b2PolygonShape shape;
    shape.SetAsBox(prop.width / Game::PPM / 2, prop.height / Game::PPM / 2);
    mB2Body->CreateFixture(&shape , 0.0f);
}

GameObjWall::~GameObjWall() 
{
    //TODO
}

void GameObjWall::update(double dt)
{

}
