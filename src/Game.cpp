#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include <OgreRenderWindow.h>
#include <Box2D/Box2D.h>
#include "BillboardAtlas.h"
#include "NLTmxMap.h"
#include "Game.h"
#include "GameObj.h"
#include "GameObjBall.h"
#include "GameObjBrick.h"
#include "GameObjContactListener.h"
#include "GameObjPaddle.h"
#include "GameObjWall.h"

Game::Game(Ogre::SceneManager *scene, Ogre::RenderWindow *window) : mSceneMgr(scene), mWindow(window)
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

Ogre::Vector3 Game::screenToWorldPos(int x, int y)
{
    //TODO division by 0
    Ogre::Real offsetX = static_cast<Ogre::Real>(x) / mWindow->getWidth();
    Ogre::Real offsetY = static_cast<Ogre::Real>(y) / mWindow->getHeight();

    Ogre::Camera *cam = mSceneMgr->getCamera("main");
    Ogre::Ray mouseRay = cam->getCameraToViewportRay(offsetX, offsetY);
    Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
    std::pair<bool, Ogre::Real> result = mouseRay.intersects(plane);
    if (result.first) {
        return  mouseRay.getPoint(result.second);
    }

    assert(false);
    return Ogre::Vector3();
}

void Game::run(const std::string& level)
{
    loadLevel(level);

    //FIXME 
    GameObjProp prop;
    prop.filename = "ball.png";
    prop.width = 50.0f;
    prop.height = 50.0f;
    prop.x = 1500.0f;
    prop.y = 500.0f;
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
    mB2World->Step(0.016f, 8, 3);
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

    static const float EPSILON = 0.1;
    auto it = std::min_element(objects.begin(), objects.end(), [](GameObj::SharedPtr o1, GameObj::SharedPtr o2) -> bool { 
        Ogre::Vector3 p1 = o1->billboard()->getPosition();
        Ogre::Vector3 p2 = o2->billboard()->getPosition();
        return p1.y < p2.y || (abs(p1.y - p2.y) < EPSILON && p1.x < p2.x);
    });
    Ogre::Billboard *bottom_left = (*it)->billboard();

    it = std::min_element(objects.begin(), objects.end(), [](GameObj::SharedPtr o1, GameObj::SharedPtr o2) -> bool { 
        Ogre::Vector3 p1 = o1->billboard()->getPosition();
        Ogre::Vector3 p2 = o2->billboard()->getPosition();
        return p1.y < p2.y || (abs(p1.y - p2.y) < EPSILON && p1.x > p2.x);
    });
    Ogre::Billboard *bottom_right = (*it)->billboard();

    //FIXME add assert, make paddle func
    GameObjProp prop;
    prop.filename = "border.png";
    prop.width = 450.0f;
    prop.height = 50.0f;
    prop.x = (bottom_right->getPosition().x + bottom_left->getPosition().x) / 2;
    prop.y = bottom_left->getPosition().y;
    float maxLeft = bottom_left->getPosition().x + (prop.width + bottom_left->getOwnWidth())/ 2;
    float maxRight = bottom_right->getPosition().x - (prop.width + bottom_right->getOwnWidth())/ 2;
    objects.push_back(GameObj::SharedPtr(new GameObjPaddle(this, prop, maxLeft, maxRight)));
}
