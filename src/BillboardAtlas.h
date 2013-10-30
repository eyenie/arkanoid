#ifndef BILLBOARDATLAS_H_
#define BILLBOARDATLAS_H_

#include <OgreBillboardSet.h>

class BillboardAtlas {
public:
    BillboardAtlas(Ogre::SceneManager *mSceneMgr, Ogre::SceneNode *node, const std::string& filename);
    virtual ~BillboardAtlas();

    Ogre::Billboard *createBillboard(const std::string& name, double w, double h);

private:
    Ogre::BillboardSet* bbset;
    std::map<std::string, unsigned int> names;
};


#endif /* end of include guard: BILLBOARDATLAS_H_ */
