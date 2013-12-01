#include "Game.h"
#include "GameObjBrick.h"
#include "BillboardAtlas.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjBrick::GameObjBrick(Game* game, const GameObjProp& prop) : GameObj(game)
{
    mBillboard = mGame->atlas()->createBillboard(prop.filename, prop.width, prop.height);
    mBillboard->setPosition(prop.x, prop.y, 0.0f);

    b2BodyDef bd;
    bd.position.Set(prop.x / Game::PPM, prop.y / Game::PPM); 
    mB2Body = mGame->world()->CreateBody(&bd);
    mB2Body->SetUserData(this);

    b2PolygonShape shape;
    shape.SetAsBox(prop.width / Game::PPM / 2, prop.height / Game::PPM / 2);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.filter.categoryBits = GameObj::BRICK;
    fd.filter.maskBits = GameObj::BALL;
    mB2Body->CreateFixture(&fd);
}

GameObjBrick::~GameObjBrick() 
{
}

void GameObjBrick::update(double dt)
{
}
