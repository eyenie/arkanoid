#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Game;

class Application 
{
public:
    Application();
    ~Application(void);

    void run();

private:
    bool initWindow();
    void initGame();
    void loadResources();
    void mainLoop();

    Ogre::Root *mRoot;
    Ogre::RenderWindow *ogreWindow;
    SDL_Window *sdlWindow;
    SDL_GLContext glContext;

    Ogre::SceneManager *mSceneMgr;
    Ogre::Camera *mCamera;
    Ogre::Viewport *mViewport;

    Game *mGame;
};

#endif // #ifndef APPLICATION_H_
