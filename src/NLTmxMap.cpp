#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <OgreDataStream.h>
#include <OgreResourceGroupManager.h>


#include "NLTmxMap.h"



using namespace std;
using namespace boost;



NLTmxMap* NLLoadTmxMap( string const & filename )
{    
    Ogre::DataStreamPtr datastream = Ogre::ResourceGroupManager::getSingleton().openResource(filename);
    std::stringstream ss(datastream->getAsString());


    property_tree::ptree pt;
    property_tree::xml_parser::read_xml( ss, pt);
    
    NLTmxMap* map = new NLTmxMap();
    
    map->width = pt.get<int>( "map.<xmlattr>.width", 0 );
    map->height = pt.get<int>( "map.<xmlattr>.height", 0 );
    map->tileWidth = pt.get<int>( "map.<xmlattr>.tilewidth", 0 );
    map->tileHeight = pt.get<int>( "map.<xmlattr>.tileheight", 0 );
    
    BOOST_FOREACH( property_tree::ptree::value_type &v, pt.get_child("map") ) {
        if ( v.first == "tileset" ) {
            NLTmxMapTileset* tileset = new NLTmxMapTileset();
            
            tileset->firstGid = v.second.get<int>("<xmlattr>.firstgid", 0);
            tileset->name = v.second.get<string>("<xmlattr>.name");
            tileset->tileWidth = v.second.get<int>("<xmlattr>.tilewidth", 0);
            tileset->tileHeight = v.second.get<int>("<xmlattr>.tileheight", 0);
            tileset->filename = v.second.get<string>("image.<xmlattr>.source");
            
            //std::cout << "Tileset " << tileset->name << " filename " << tileset->filename << std::endl;
            
            map->tilesets.push_back( tileset );
        }
    }
    
    BOOST_FOREACH( property_tree::ptree::value_type &v, pt.get_child("map") ) {
        if ( v.first == "layer" ) {
            NLTmxMapLayer* layer = new NLTmxMapLayer();
            
            layer->name = v.second.get<string>("<xmlattr>.name");
            layer->width = v.second.get<int>("<xmlattr>.width");
            layer->height = v.second.get<int>("<xmlattr>.height");
            
            // TODO assert that data.<xmlattr>.encoding == "CSV" here.
            
            string csv = v.second.get<string>("data");
            
            // std::cout << csv.substr( 0, 100 ) << std::endl;
            //std::cout << "Layer " << layer->name << " width " << layer->width << " height " << layer->height << std::endl;
            
            layer->data = new int[ layer->width * layer->height ];
            
            typedef char_separator<char> sep;
            typedef tokenizer< sep > tk;
            
            tk tokens(csv, sep(",\n\r"));
            int index = 0;
            
            for (tk::iterator i(tokens.begin()); i!=tokens.end(); ++i) 
            {
                layer->data[ index ] = lexical_cast<int>( *i );
                index++;
            }
            
            map->layers.push_back( layer );
        }
    }    
    
    BOOST_FOREACH( property_tree::ptree::value_type &v, pt.get_child("map") ) {
        if ( v.first == "objectgroup" ) {
            NLTmxMapObjectGroup* group = new NLTmxMapObjectGroup();
            
            group->name = v.second.get<string>("<xmlattr>.name");
            group->width = v.second.get<int>("<xmlattr>.width");
            group->height = v.second.get<int>("<xmlattr>.height");
            group->visible = v.second.get<int>("<xmlattr>.visible", 0);
            
            //            std::cout << "group " << group->name << std::endl;
            
            BOOST_FOREACH( property_tree::ptree::value_type &o, v.second ) {
                if ( o.first == "object" ) {
                    NLTmxMapObject* object = new NLTmxMapObject();
                    
                    object->name = o.second.get<string>( "<xmlattr>.name" );
                    object->x = o.second.get<int>( "<xmlattr>.x" );
                    object->y = o.second.get<int>( "<xmlattr>.y" );
                    object->width = o.second.get<int>( "<xmlattr>.width" );
                    object->height = o.second.get<int>( "<xmlattr>.height" );
                    
                    //                    std::cout << "object " << object->name << " at " << object->x << ", " << object->y << std::endl;
                    
                    group->objects.push_back( object );
                }
            }
            
            map->objects.push_back( group );
        }
    }
    
    
    
    return map;
}
