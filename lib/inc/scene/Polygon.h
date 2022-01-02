/**
 * Project Untitled
 */


#ifndef _POLYGON_H
#define _POLYGON_H

#include <vector>
#include <memory>

#include "utils/ICoord.h"

class Polygon {
public:
    using CoordPtr = std::shared_ptr<ICoord>;
    using iterator = std::vector<CoordPtr>::iterator;
    using const_iterator = std::vector<CoordPtr>::const_iterator;

    Polygon(std::vector<CoordPtr> coords, CoordPtr normal);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    const ICoord &getNormal() const;

private:
    std::vector<CoordPtr> _coords;
    CoordPtr _normal;
};

#endif //_POLYGON_H