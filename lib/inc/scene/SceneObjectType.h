/**
 * Project Untitled
 */


#ifndef _SCENEOBJECTTYPE_H
#define _SCENEOBJECTTYPE_H

#include <string>

class SceneObjectType {
private:
    std::string _name;
public:
    explicit SceneObjectType(std::string name);

    std::string getName();
};

#endif //_SCENEOBJECTTYPE_H