#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include <Box2D/Box2D.h>
#include "BillboardAtlas.h"
#include "NLTmxMap.h"
#include "Game.h"
#include "GameObj.h"
#include "GameObjBall.h"
#include "GameObjBrick.h"
#include "GameObjContactListener.h"
#include "GameObjWall.h"

Game::Game(Ogre::SceneManager *scene) : mSceneMgr(scene)
{
    mBBAtlas = new BillboardAtlas(mSceneMgr, mSceneMgr->getRootSceneNode()->createChildSceneNode(), "atlas.xml");
    mB2World = new b2World(b2Vec2(0.0f, 0.0f));
    mB2World->SetContactListener(&contactListener);
}

Game::~Game()
{
    delete mBBAtlas;
    delete mB2World;
}

void Game::run(const std::string& level)
{
    loadLevel(level);

    GameObjProp prop;
    prop.filename = "ball.png";
    prop.width = 50.0f;
    prop.height = 50.0f;
    prop.x = 35.0f * PPM;
    prop.y = 10.0f * PPM;
    objects.push_back(GameObj::SharedPtr(new GameObjBall(this, prop)));
}

BillboardAtlas *Game::atlas() 
{
    return mBBAtlas;
}

b2World *Game::world()
{
    return mB2World;
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    mB2World->Step(0.16f, 8, 3);
    for (auto it = objects.begin(); it < objects.end(); it++) {
        (*it)->update(evt.timeSinceLastFrame);
    }

    objects.erase(std::remove_if(objects.begin(), objects.end(), 
                [](GameObj::SharedPtr o) -> bool { return o->state() == GameObj::DESTROYED; }), objects.end());
    return true;
}

void Game::loadLevel(const std::string& level)
{
    NLTmxMap* map = NLLoadTmxMap(level);
    std::map<int, NLTmxMapTileset *> tiles;
    for (NLTmxMapTileset *t : map->tilesets) {
        tiles[t->firstGid] = t;
    }
    float half_width = map->tileWidth * map->width / 2;
    float half_height = map->tileHeight * map->height / 2;
    for (int h = 0; h < map->height; h++) {
        for (int w = 0; w < map->width; w++) {
            int objIndex = map->layers[0]->data[h * map->width + w];
            if (objIndex == 0) {
                continue;
            } else {
                NLTmxMapTileset *t = tiles[objIndex];
                GameObjProp prop;
                prop.filename = t->filename;
                prop.width = t->tileWidth;
                prop.height = t->tileHeight;
                prop.x = w * map->tileWidth - half_width;
                prop.y = half_height - h * map->tileHeight;
                if (prop.filename == "brick-basic.png") {
                    objects.push_back(GameObj::SharedPtr(new GameObjBrick(this, prop)));
                } else
                if (prop.filename == "border.png") {
                    objects.push_back(GameObj::SharedPtr(new GameObjWall(this, prop)));
                } else {
                    assert(false);
                }
            }
        } 
    }
    delete map;
}
