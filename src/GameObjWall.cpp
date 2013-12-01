#include "Game.h"
#include "GameObjWall.h"
#include "BillboardAtlas.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjWall::GameObjWall(Game* game, const GameObjProp& prop) : GameObj(game)
{
    mBillboard = mGame->atlas()->createBillboard(prop.filename, prop.width, prop.height);
    mBillboard->setPosition(prop.x, prop.y, 0.0f);

    b2BodyDef bd;
    //FIXME
    bd.position.Set(prop.x / Game::PPM, prop.y / Game::PPM); 
    mB2Body = mGame->world()->CreateBody(&bd);
    mB2Body->SetUserData(this);

    b2PolygonShape shape;
    shape.SetAsBox(prop.width / Game::PPM / 2, prop.height / Game::PPM / 2);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.filter.categoryBits = GameObj::WALL;
    fd.filter.maskBits = GameObj::BALL;
    mB2Body->CreateFixture(&fd);
}

GameObjWall::~GameObjWall() 
{
    //TODO
}

void GameObjWall::update(double dt)
{

}
