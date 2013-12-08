#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include <OgreRenderWindow.h>
#include <Box2D/Box2D.h>
#include "NLTmxMap.h"
#include "Game.h"
#include "GameObj.h"
#include "GameObjBall.h"
#include "GameObjBrick.h"
#include "GameObjContactListener.h"
#include "GameObjPaddle.h"
#include "GameObjWall.h"

Game::Game(Application *app) : mApplication(app)
{
    mManager = new GameObjManager(mApplication, "atlas.xml");
}

Game::~Game()
{
}

void Game::run()
{
    loadLevel("level1.tmx");
    createPaddle();
}

bool Game::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // update all objects
    for (auto it = gameObjects.begin(); it < gameObjects.end(); it++) {
        (*it)->update(evt.timeSinceLastFrame);
    }

    // remove dead objects
    gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), 
                [](GameObj::SharedPtr o) -> bool { return o->getState() == GameObj::DESTROYED; }), gameObjects.end());

    return true;
}

void Game::loadLevel(const std::string& level)
{
    NLTmxMap* map = NLLoadTmxMap(level);
    std::map<int, NLTmxMapTileset *> tiles;
    for (NLTmxMapTileset *t : map->tilesets) {
        tiles[t->firstGid] = t;
    }
    // (0, 0) is center of screen
    float half_width = map->tileWidth * map->width / 2;
    float half_height = map->tileHeight * map->height / 2;
    for (int h = 0; h < map->height; h++) {
        for (int w = 0; w < map->width; w++) {
            int objIndex = map->layers[0]->data[h * map->width + w];
            if (objIndex == 0) {
                continue;
            } else {
                NLTmxMapTileset *t = tiles[objIndex];
                GameObjDef def;
                def.filename = t->filename;
                def.width = t->tileWidth;
                def.height = t->tileHeight;
                def.x = w * map->tileWidth - half_width;
                def.y = half_height - h * map->tileHeight;
                gameObjects.push_back(mManager->createObject(def));
            }
        } 
    }

    delete map;
}

void Game::createPaddle()
{
    auto compare = [this](std::function<bool(float, float)> cmp) { 
        return [this, cmp](GameObj::SharedPtr o1, GameObj::SharedPtr o2) { 
            if (close(o1->getY(), o2->getY())) {
                return cmp(o1->getX(), o2->getX());
            } else {
                return o1->getY() < o2->getY();
            }
        };
    };

    auto bottom_left = *std::min_element(gameObjects.begin(), gameObjects.end(), compare(std::less<float>()));
    auto bottom_right = *std::min_element(gameObjects.begin(), gameObjects.end(), compare(std::greater<float>()));

    assert(close(bottom_left->getY(), bottom_right->getY()) 
            && !close(bottom_left->getX(), bottom_right->getX())
            && bottom_left->getX() < bottom_right->getX());

    GameObjDef def;
    def.filename = "paddle.png";
    def.width = 450.0f;
    def.height = 50.0f;
    def.x = (bottom_right->getX() + bottom_left->getX()) / 2;
    def.y = bottom_left->getY();
    auto paddle = mManager->createObject(def);
    //TODO remove dynamic cast
    GameObjPaddle *p = dynamic_cast<GameObjPaddle *>(paddle.get());
    float left = bottom_left->getX() + (def.width + bottom_left->getWidth()) / 2;
    float right = bottom_right->getX() - (def.width + bottom_right->getWidth()) / 2;
    p->setBounds(left, right);
    gameObjects.push_back(paddle);
}

bool Game::close(float x1, float x2)
{
    static const float EPSILON = 0.1;
    return abs(x1 - x2) < EPSILON;
}

//
//    //FIXME 
//    def.filename = "ball.png";
//    def.width = 50.0f;
//    def.height = 50.0f;
//    def.x = 1500.0f;
//    def.y = 500.0f;
//    gameObjects.push_back(GameObj::SharedPtr(new GameObjBall(this, def)));
