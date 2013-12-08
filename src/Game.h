#ifndef GAME_H_
#define GAME_H_

#include <OgreFrameListener.h>
#include <OgreVector3.h>
#include "Application.h"
#include "GameObjContactListener.h"
#include "GameObj.h"

class BillboardAtlas;
class b2World;

class Game : public Ogre::FrameListener {
public:
    Game(Application *app);
    virtual ~Game();

    void            run();

protected:
    bool            frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
    void            loadLevel(const std::string& level);
    void            createPaddle();
    bool            close(float x1, float x2);

    Application *                   mApplication;
    GameObjManager *                mManager;
    std::vector<GameObj::SharedPtr> gameObjects;
};

#endif /* end of include guard: GAME_H_ */
