#include <SDL2/SDL.h>
#include <OgreException.h>

#include "Application.h"

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char *argv[])
{
    Application app;

    try {
        app.run();
    } catch( Ogre::Exception& e ) {
        //FIXME
        std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
    }

    return 0;
}
