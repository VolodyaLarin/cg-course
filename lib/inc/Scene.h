/**
 * Project Untitled
 */


#ifndef _SCENE_H
#define _SCENE_H

#include <vector>
#include <memory>
#include "ISceneObject.h"



class Scene {
public:
    using ObjectPtr = std::shared_ptr<ISceneObject>;
    using iterator = std::vector<ObjectPtr>::iterator;
    using const_iterator = std::vector<ObjectPtr>::const_iterator;

    iterator begin();
    iterator end();

    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;


    [[nodiscard]] const_iterator cbegin() const;
    [[nodiscard]] const_iterator cend() const;
    
    void add(const ObjectPtr&);
    
    void remove(const iterator&);
private: 
    std::vector<ObjectPtr> _objects = {};
};

#endif //_SCENE_H