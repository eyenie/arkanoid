#include "Game.h"
#include "GameObjPaddle.h"
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>
#include <SDL_mouse.h>

GameObjPaddle::GameObjPaddle(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) : GameObj(mgr, bb, body)
{
    b2PolygonShape shape;
    shape.SetAsBox(getWidth() / GameObjManager::PPM / 2, getHeight() / GameObjManager::PPM / 2);

    b2FixtureDef fd;
    fd.shape = &shape;
    fd.filter.categoryBits = GameObj::PADDLE;
    fd.filter.maskBits = GameObj::BALL;
    boxBody->CreateFixture(&fd);
}

void GameObjPaddle::update(double dt)
{
    int x, y;

    if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)) {
        Ogre::Vector3 next = mManager->worldCoords(x, y);
        if (next.x < maxLeft) 
            next.x = maxLeft;
        else if (next.x > maxRight) 
            next.x = maxRight;

        setPosition(next.x, getY());
    }
}

void GameObjPaddle::setBounds(float left, float right)
{
    maxLeft = left;
    maxRight = right;
}
