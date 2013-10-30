#pragma once


#include <string>
#include <vector>




class NLTmxMapTileset {
public:
    int firstGid;
    std::string name;
    int tileWidth;
    int tileHeight;
    std::string filename;
};


class NLTmxMapLayer {
public:
    std::string name;
    int width;
    int height;
    int* data;
    
    ~NLTmxMapLayer() {
        delete[] data;
    }
};


class NLTmxMapObject {
public:
    std::string name;
    int x;
    int y;
    int width;
    int height;
};


class NLTmxMapObjectGroup {
public:
    std::string name;
    int width;
    int height;
    bool visible;
    
    std::vector<NLTmxMapObject*> objects;
    
    ~NLTmxMapObjectGroup() {
        for ( unsigned int i=0; i < objects.size(); i++ ) {
            delete objects[i];
        }
    }
};


class NLTmxMap {
public:
    
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    
    std::vector<NLTmxMapTileset*> tilesets;
    std::vector<NLTmxMapLayer*> layers;
    std::vector<NLTmxMapObjectGroup*> objects;
    
    ~NLTmxMap() {
        for ( unsigned int i=0; i < objects.size(); i++ ) {
            delete objects[i];
        }
        
        for ( unsigned int i=0; i < layers.size(); i++ ) {
            delete layers[i];
        }
        
        for ( unsigned int i=0; i < tilesets.size(); i++ ) {
            delete tilesets[i];
        }
    }

    
};


NLTmxMap* NLLoadTmxMap( std::string const & filename );

