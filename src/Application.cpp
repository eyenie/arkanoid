#include "Application.h"
#include <OgreWindowEventUtilities.h>
#include "Game.h"

Application::Application() : 
    ogreRoot(0),
    ogreWindow(0),
    sdlWindow(0),
    sdlGLContext(0)
{
}

Application::~Application(void)
{
    if (ogreRoot) {
        delete ogreRoot;
    }

    if (sdlGLContext) {
        SDL_GL_DeleteContext(sdlGLContext);  
    }

    if (sdlWindow) {
        SDL_DestroyWindow(sdlWindow);
    }

    SDL_Quit();
}

void Application::run()
{
    if (!initWindow())
        return;

    initGame();

    mainLoop();
}

Ogre::Camera * Application::getCamera()
{
    return ogreCamera;
}

Ogre::SceneManager * Application::getSceneMgr()
{
    return ogreSceneMgr;
}

Ogre::RenderWindow * Application::getWindow()
{
    return ogreWindow;
}

bool Application::initWindow()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    sdlWindow = SDL_CreateWindow("NameOfWindow", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 
            SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if (sdlWindow == NULL) {
        return false;
    }

    sdlGLContext = SDL_GL_CreateContext(sdlWindow);
    if (sdlGLContext == NULL) {
        return false;
    }

    ogreRoot = new Ogre::Root("", "");

    //FIXME
    ogreRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL");

    //FIXME
    Ogre::RenderSystem *rs = ogreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    if (!rs) {
        return false;
    }
    ogreRoot->setRenderSystem(rs);
    ogreRoot->initialise(false);
    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("True");
    //FIXME
    ogreWindow = ogreRoot->createRenderWindow("main", 640, 480, false, &params);
    ogreWindow->setVisible(true);

    return true;
}

void Application::initGame()
{
    ogreSceneMgr = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
    ogreCamera = ogreSceneMgr->createCamera("main");
    ogreViewport = ogreWindow->addViewport(ogreCamera);
    //FIXME
    ogreViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
    ogreCamera->setAspectRatio(Ogre::Real(ogreViewport->getActualWidth()) / Ogre::Real(ogreViewport->getActualHeight()));

    //FIXME
    ogreCamera->setNearClipDistance(1.5f);
	ogreCamera->setFarClipDistance(4000.0f);
    ogreCamera->setPosition(0, 0, 3900.0f);
    ogreCamera->lookAt(0, 0, 0);

    Ogre::ResourceGroupManager *rgm = Ogre::ResourceGroupManager::getSingletonPtr();
    rgm->addResourceLocation("/home/eyenie/dev/arkanoid/assets", "FileSystem", "General");
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    mGame = new Game(this);
    mGame->run();
    ogreRoot->addFrameListener(mGame);
}

void Application::mainLoop()
{
    SDL_Event event; 
    bool done = false;
    while(!done) {
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    ogreWindow->resize(event.window.data1, event.window.data2);
                    ogreCamera->setAspectRatio(Ogre::Real(ogreViewport->getActualWidth()) / Ogre::Real(ogreViewport->getActualHeight()));
                }
                break;
            }
        }
    
        ogreRoot->renderOneFrame();
    } 
}
