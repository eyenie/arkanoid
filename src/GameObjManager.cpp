#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
#include "Application.h"
#include "GameObjManager.h"
#include "GameObjBall.h"
#include "GameObjBrick.h"
#include "GameObjPaddle.h"
#include "GameObjWall.h"

GameObjManager::GameObjManager(Application *app, const std::string& atlasXml) : mApplication(app)
{
    boxWorld = new b2World(b2Vec2(0.0f, 0.0f));
    boxWorld->SetContactListener(&mContactListener);

    Ogre::SceneManager* sceneMgr = mApplication->getSceneMgr();
    Ogre::SceneNode * node = mApplication->getSceneMgr()->getRootSceneNode();

    Ogre::DataStreamPtr datastream = Ogre::ResourceGroupManager::getSingleton().openResource(atlasXml);
    std::stringstream ss(datastream->getAsString());

    boost::property_tree::ptree pt;
    boost::property_tree::read_xml(ss, pt);

    std::vector<Ogre::FloatRect> vec;
    unsigned int tex_width  = pt.get<unsigned int>("TextureAtlas.<xmlattr>.width");
    unsigned int tex_height = pt.get<unsigned int>("TextureAtlas.<xmlattr>.height");
    unsigned int i = 0;
    for (boost::property_tree::ptree::value_type &v : pt.get_child("TextureAtlas")) {
        float x = v.second.get<float>("<xmlattr>.x", 0.0f);
        float y = v.second.get<float>("<xmlattr>.y", 0.0f);
        float w = v.second.get<float>("<xmlattr>.w", 0.0f);
        float h = v.second.get<float>("<xmlattr>.h", 0.0f);
        vec.push_back(Ogre::FloatRect(x / tex_width, y / tex_height, (x + w) / tex_width, (y + h) / tex_height));
        mTexcoords[v.second.get<std::string>("<xmlattr>.n", "")] = i++;
    }
 
    ogreBillboardSet = sceneMgr->createBillboardSet("BBSet", vec.size());
    ogreBillboardSet->setMaterialName("test");
    ogreBillboardSet->setTextureCoords(&vec[0], vec.size());
    node->attachObject(ogreBillboardSet);
}

GameObjManager::~GameObjManager()
{
}

void GameObjManager::update(double dt)
{
    boxWorld->Step(0.016f, 8, 3);
}

GameObj::SharedPtr GameObjManager::createObject(const GameObjDef& def)
{
    Ogre::Billboard* bb = ogreBillboardSet->createBillboard(Ogre::Vector3(def.x, def.y, 0));
    bb->setTexcoordIndex(mTexcoords[def.filename]);
    //FIXME
    if (def.filename == "paddle.png") {
        bb->setTexcoordIndex(mTexcoords["border.png"]);
    }
    bb->setDimensions(def.width, def.height);
    bb->setPosition(def.x, def.y, 0.0f);

    b2BodyDef bd;
    bd.position.Set(def.x / PPM, def.y / PPM); 
    bd.type = b2_staticBody;
    b2Body *body = boxWorld->CreateBody(&bd);

    GameObj::SharedPtr o;

    if (def.filename == "ball.png") {
        o = std::make_shared<GameObjBall>(this, bb, body);
    } else if (def.filename == "brick-basic.png") {
        o = std::make_shared<GameObjBrick>(this, bb, body);
    } else if (def.filename == "border.png") {
        o = std::make_shared<GameObjWall>(this, bb, body);
    } else if (def.filename == "paddle.png") {
        o = std::make_shared<GameObjPaddle>(this, bb, body);
    } else {
        assert(false);
    }

    return o;
}

/* GameObjBall::GameObjBall(GameObjManager* mgr, const GameObjDef& def) : GameObj(mgr)
 * {
 * 
 * 
 *
       mB2Body->SetUserData(this);
 *     bd.type = b2_dynamicBody;
 *     bd.fixedRotation = true;
 *     b2CircleShape shape;
 *     shape.m_radius = def.width / Game::PPM / 2;
 *     b2FixtureDef fd;
 *     fd.shape = &shape;
 *     fd.restitution = 1.0f;
 *     fd.density = 1.0f;
 *     fd.friction = 0.0f;
 *     fd.filter.categoryBits = GameObj::BALL;
 *     fd.filter.maskBits = GameObj::BRICK | GameObj::WALL | GameObj::PADDLE;
 *     mB2Body->CreateFixture(&fd);
 *     mB2Body->SetLinearVelocity(b2Vec2(29, 29));
 * }
 */


/* GameObjBrick::GameObjBrick(Game* game, const GameObjProp& prop) : GameObj(game)
 * {
 *     mBillboard = mGame->atlas()->createBillboard(prop.filename, prop.width, prop.height);
 * 
 *     b2BodyDef bd;
 *     bd.position.Set(prop.x / Game::PPM, prop.y / Game::PPM); 
 *     mB2Body = mGame->world()->CreateBody(&bd);
 *     mB2Body->SetUserData(this);
 * 
 *     b2PolygonShape shape;
 *     shape.SetAsBox(prop.width / Game::PPM / 2, prop.height / Game::PPM / 2);
 * 
 *     b2FixtureDef fd;
 *     fd.shape = &shape;
 *     fd.filter.categoryBits = GameObj::BRICK;
 *     fd.filter.maskBits = GameObj::BALL;
 *     mB2Body->CreateFixture(&fd);
 * }
 */

void GameObjManager::removeObject(GameObj *obj)
{
//    bbset->removeBillboard(bb);
//    mGame->world()->DestroyBody(mB2Body);
//    mGame->atlas()->removeBillboard(mBillboard);
}


Ogre::Vector3 GameObjManager::worldCoords(int x, int y)
{
    //TODO division by 0
    Ogre::Real offsetX = static_cast<Ogre::Real>(x) / mApplication->getWindow()->getWidth();
    Ogre::Real offsetY = static_cast<Ogre::Real>(y) / mApplication->getWindow()->getHeight();
    
    Ogre::Camera *cam = mApplication->getCamera();
    Ogre::Ray mouseRay = cam->getCameraToViewportRay(offsetX, offsetY);
    Ogre::Plane plane(Ogre::Vector3::UNIT_Z, 0);
    std::pair<bool, Ogre::Real> result = mouseRay.intersects(plane);
    if (result.first) {
        return  mouseRay.getPoint(result.second);
    }

    assert(false);
    return Ogre::Vector3();
}
