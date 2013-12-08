#include "GameObj.h"
#include "GameObjManager.h"
#include <OgreBillboard.h>

GameObj::GameObj(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) : 
    mManager(mgr), mState(ACTIVE), ogreBillboard(bb), boxBody(body)
{
    boxBody->SetUserData(this);
}

GameObj::~GameObj()
{
    mManager->removeObject(this);
}

float GameObj::getX()
{
    return ogreBillboard->getPosition().x;
}

float GameObj::getY()
{
    return ogreBillboard->getPosition().y;
}

void GameObj::setPosition(float x, float y)
{
    boxBody->SetTransform(b2Vec2(x / GameObjManager::PPM, y / GameObjManager::PPM), boxBody->GetAngle());
    ogreBillboard->setPosition(x, y, 0.0f);
}

float GameObj::getWidth()
{
    return ogreBillboard->getOwnWidth();
}

float GameObj::getHeight()
{
    return ogreBillboard->getOwnHeight();
}

GameObj::State GameObj::getState() 
{ 
    return mState; 
}

void GameObj::setState(State s) 
{ 
    mState = s; 
}
