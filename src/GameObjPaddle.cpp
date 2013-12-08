#include "Game.h"
#include "GameObjPaddle.h"
#include "BillboardAtlas.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>
#include <SDL_mouse.h>

GameObjPaddle::GameObjPaddle(Game* game, const GameObjProp& prop, float left, float right) : GameObj(game), minX(left), maxX(right)
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
    fd.filter.categoryBits = GameObj::PADDLE;
    fd.filter.maskBits = GameObj::BALL;
    mB2Body->CreateFixture(&fd);
}

GameObjPaddle::~GameObjPaddle() 
{
    //TODO
}

void GameObjPaddle::update(double dt)
{
    int x, y;

    if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)) {
        Ogre::Vector3 prev = mBillboard->getPosition();
        Ogre::Vector3 next = mGame->screenToWorldPos(x, y);
        fprintf(stderr, "%f %f %f\n", next.x, minX, maxX);
        if (next.x < minX) 
            next.x = minX;
        else if (next.x > maxX) 
            next.x = maxX;
        mB2Body->SetTransform(b2Vec2(next.x / Game::PPM, prev.y / Game::PPM), mB2Body->GetAngle());
        mBillboard->setPosition(next.x, prev.y, 0.0f);
    }
}
