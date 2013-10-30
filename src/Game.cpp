#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include "BillboardAtlas.h"
#include "NLTmxMap.h"
#include "Game.h"

Game::Game(Ogre::SceneManager *scene) : mSceneMgr(scene)
{
    mBBAtlas = new BillboardAtlas(mSceneMgr, mSceneMgr->getRootSceneNode()->createChildSceneNode(), "atlas.xml");
}

Game::~Game()
{
    delete mBBAtlas;
}

void Game::run(const std::string& level)
{
    loadLevel(level);
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
                Ogre::Billboard* b = mBBAtlas->createBillboard(t->filename, t->tileWidth, t->tileHeight);
                b->setPosition(Ogre::Vector3(w * map->tileWidth - half_width, half_height - h * map->tileHeight, 0.0f));
            }
        } 
    }
    delete map;
}
