/**
 * Project Untitled
 */


#ifndef _MODEL_H
#define _MODEL_H

#include "BaseSceneObject.h"
#include "Polygon.h"


class Model: public BaseSceneObject {
public:
    using iterator = std::vector<Polygon>::iterator;
    using const_iterator = std::vector<Polygon>::const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
    
    const_iterator cbegin() const;
    const_iterator cend() const;
    

private: 
    std::vector<Polygon> _polygons;
};

#endif //_MODEL_H