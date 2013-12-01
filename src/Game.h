#ifndef GAME_H_
#define GAME_H_

#include <OgreFrameListener.h>
#include "GameObjContactListener.h"
#include "GameObj.h"

class BillboardAtlas;
class b2World;

class Game : public Ogre::FrameListener {
public:
    Game(Ogre::SceneManager *scene);
    virtual ~Game();

    void run(const std::string& level);
    BillboardAtlas *atlas();
    b2World *world();

    static const int PPM = 50.0f; //FIXME

protected:
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
    void loadLevel(const std::string& level);

    Ogre::SceneManager *mSceneMgr;
    BillboardAtlas *mBBAtlas;
    b2World *mB2World;
    GameObjContactListener contactListener;
    std::vector<GameObj::SharedPtr> objects;
};

#endif /* end of include guard: GAME_H_ */
