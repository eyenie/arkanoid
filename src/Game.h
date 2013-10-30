#ifndef GAME_H_
#define GAME_H_

class BillboardAtlas;

class Game {
public:
    Game(Ogre::SceneManager *scene);
    virtual ~Game();

    void run(const std::string& level);

private:
    void loadLevel(const std::string& level);

    Ogre::SceneManager *mSceneMgr;
    BillboardAtlas *mBBAtlas;
};

#endif /* end of include guard: GAME_H_ */
