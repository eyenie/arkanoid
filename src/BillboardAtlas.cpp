#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <OgreResourceGroupManager.h>
#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include "BillboardAtlas.h"

BillboardAtlas::BillboardAtlas(Ogre::SceneManager *mSceneMgr, Ogre::SceneNode *node, const std::string& filename)
{
    Ogre::DataStreamPtr datastream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
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
        names[v.second.get<std::string>("<xmlattr>.n", "")] = i++;
    }
 
    bbset = mSceneMgr->createBillboardSet("BBSet", vec.size());
    bbset->setMaterialName("test");
    bbset->setTextureCoords(&vec[0], vec.size());
    node->attachObject(bbset);
}

BillboardAtlas::~BillboardAtlas()
{
    //TODO
}

Ogre::Billboard *BillboardAtlas::createBillboard(const std::string& name, double w, double h)
{
    Ogre::Billboard* bb = bbset->createBillboard(Ogre::Vector3(0, 0, 0));
    bb->setTexcoordIndex(names[name]);
    bb->setDimensions(w, h);
    return bb;
}

void BillboardAtlas::removeBillboard(Ogre::Billboard *bb)
{
    bbset->removeBillboard(bb);
}


