#include "BillboardAtlas.h"
#include "Game.h"
#include "GameObj.h"
#include <Box2D/Box2D.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>


GameObj::~GameObj()
{
    mGame->world()->DestroyBody(mB2Body);
    mGame->atlas()->removeBillboard(mBillboard);
}
