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

    void                 run();
    Ogre::Camera *       getCamera();
    Ogre::SceneManager * getSceneMgr();
    Ogre::RenderWindow * getWindow();

private:
    bool                 initWindow();
    void                 initGame();
    void                 mainLoop();

    Ogre::Root *         ogreRoot;
    Ogre::RenderWindow * ogreWindow;
    Ogre::SceneManager * ogreSceneMgr;
    Ogre::Camera *       ogreCamera;
    Ogre::Viewport *     ogreViewport;

    SDL_Window *         sdlWindow;
    SDL_GLContext        sdlGLContext;

    Game *               mGame;
};

#endif // #ifndef APPLICATION_H_
