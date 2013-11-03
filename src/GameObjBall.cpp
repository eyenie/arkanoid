#include "Game.h"
#include "GameObjBall.h"
#include "BillboardAtlas.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>

GameObjBall::GameObjBall(const GameObjProp& prop, BillboardAtlas *mBBAtlas, b2World *mB2World)
{
    mBillboard = mBBAtlas->createBillboard(prop.filename, prop.width, prop.height);
    mBillboard->setPosition(prop.x, prop.y, 0.0f);

    b2BodyDef bd;
    bd.type = b2_dynamicBody;
    bd.fixedRotation = true;
    bd.position.Set(prop.x / Game::PPM, prop.y / Game::PPM); 
    mB2Body = mB2World->CreateBody(&bd);

    b2CircleShape shape;
    shape.m_radius = prop.width / Game::PPM / 2;
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.restitution = 1.0f;
    fd.density = 1.0f;
    fd.friction = 0.0f;
    mB2Body->CreateFixture(&fd);
//    mB2Body->SetLinearVelocity(b2Vec2(0.9, 0.9));
}

GameObjBall::~GameObjBall() 
{
    //TODO
}

void GameObjBall::update(double dt)
{
    b2Vec2 pos = mB2Body->GetPosition();
    b2Vec2 vel = mB2Body->GetLinearVelocity();
    mBillboard->setPosition(pos.x * Game::PPM, pos.y * Game::PPM, 0.0f);
}
