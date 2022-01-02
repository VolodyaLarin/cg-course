#include "scene/Polygon.h"

#include <utility>

Polygon::iterator Polygon::begin() {
    return _coords.begin();
}

Polygon::iterator Polygon::end() {
    return _coords.end();
}

Polygon::const_iterator Polygon::begin() const {
    return cbegin();
}

Polygon::const_iterator Polygon::end() const {
    return cend();
}

Polygon::const_iterator Polygon::cbegin() const {
    return _coords.cbegin();
}

Polygon::const_iterator Polygon::cend() const {
    return _coords.cend();
}


const ICoord &Polygon::getNormal() const {
    return *_normal;
}

Polygon::Polygon(std::vector<CoordPtr> coords, Polygon::CoordPtr normal) : _coords(std::move(coords)),
                                                                                         _normal(std::move(normal)) {}
