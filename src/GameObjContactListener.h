#ifndef GAMEOBJCONTACTLISTENER_H_
#define GAMEOBJCONTACTLISTENER_H_

#include <Box2D/Box2D.h>

class GameObjContactListener : public b2ContactListener {
public:
    virtual void BeginContact(b2Contact* contact);
};

#endif /* end of include guard: GAMEOBJCONTACTLISTENER_H_ */
