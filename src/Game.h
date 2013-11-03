#ifndef GAME_H_
#define GAME_H_

#include <OgreFrameListener.h>

class BillboardAtlas;
class b2World;
class GameObj;

class Game : public Ogre::FrameListener {
public:
    Game(Ogre::SceneManager *scene);
    virtual ~Game();

    void run(const std::string& level);

    static const int PPM = 50.0f; //FIXME

protected:
    bool frameRenderingQueued(const Ogre::FrameEvent& evt);

private:
    void loadLevel(const std::string& level);

    Ogre::SceneManager *mSceneMgr;
    BillboardAtlas *mBBAtlas;
    b2World *mB2World;
    std::vector<GameObj *> objects;
};

#endif /* end of include guard: GAME_H_ */
