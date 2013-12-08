#ifndef GAMEOBJMANAGER_H_
#define GAMEOBJMANAGER_H_

#include <map>
#include <OgreVector3.h>
#include "GameObj.h"
#include "GameObjContactListener.h"

class Application;
class b2World;
namespace Ogre {
    class BillboardSet;
}

struct GameObjDef {
    std::string filename;
    float       x;
    float       y;
    float       width;
    float       height;
};

class GameObjManager {
public:
    typedef std::function<GameObj::SharedPtr(GameObjManager*, Ogre::Billboard*, b2Body*)> FnType;

    GameObjManager(Application *app, const std::string& atlasXml);
    ~GameObjManager();

    void                update(double dt);
    GameObj::SharedPtr  createObject(const GameObjDef& def);
    void                removeObject(GameObj *obj);
    Ogre::Vector3       worldCoords(int x, int y);

    static const int PPM = 50.0f; // Pixels To Meters for Box2D
private:
    void registerObjects();
    template<typename T> 
    static GameObj::SharedPtr newObject(GameObjManager *mgr, Ogre::Billboard *bb, b2Body *body) 
    {
        return GameObj::SharedPtr(new T(mgr, bb, body)); 
    }

    Ogre::BillboardSet *                ogreBillboardSet;
    b2World *                           boxWorld;
    Application *                       mApplication;
    GameObjContactListener              mContactListener;
    std::map<std::string, unsigned int> mTexcoords;
    std::map<std::string, FnType>       mConstructors;
};

#endif /* end of include guard: GAMEOBJMANAGER_H_ */
