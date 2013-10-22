#include "Application.h"
#include <OgreWindowEventUtilities.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>

Application::Application()
    : mRoot(0),
    ogreWindow(0),
    sdlWindow(0),
    glContext(0)
{
}

Application::~Application(void)
{
    if (mRoot) {
        delete mRoot;
    }

    if (glContext) {
        SDL_GL_DeleteContext(glContext);  
    }

    if (sdlWindow) {
        SDL_DestroyWindow(sdlWindow);
    }

    SDL_Quit();
}

void Application::run()
{
    if (!init())
        return;

    createCamera();
    loadResources();

    mainLoop();
}

bool Application::init()
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

    glContext = SDL_GL_CreateContext(sdlWindow);
    if (glContext == NULL) {
        return false;
    }

    mRoot = new Ogre::Root("", "");

    //FIXME
    mRoot->loadPlugin("/usr/lib/OGRE/RenderSystem_GL");

    //FIXME
    Ogre::RenderSystem *rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
    if (!rs) {
        return false;
    }
    mRoot->setRenderSystem(rs);
    mRoot->initialise(false);
    Ogre::NameValuePairList params;
    params["currentGLContext"] = Ogre::String("True");
    ogreWindow = mRoot->createRenderWindow("main", 640, 480, false, &params);
    ogreWindow->setVisible(true);

    return true;
}

void Application::createCamera()
{
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
    mCamera = mSceneMgr->createCamera("main");
    mViewport = ogreWindow->addViewport(mCamera);
    //FIXME
    mViewport->setBackgroundColour(Ogre::ColourValue(1,0,1));
    mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

    //FIXME
    mCamera->setNearClipDistance(1.5f);
	mCamera->setFarClipDistance(3000.0f);
    mCamera->setPosition(0, 0, 400);
    mCamera->lookAt(0, 0, 0);
}

void Application::loadResources()
{
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
                    mCamera->setAspectRatio(Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));
                }
                break;
            }
        }
    
        Ogre::WindowEventUtilities::messagePump();
        mRoot->renderOneFrame();
    } 
}