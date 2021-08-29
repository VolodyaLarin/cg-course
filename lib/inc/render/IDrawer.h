/**
 * Project Untitled
 */


#ifndef _IDRAWER_H
#define _IDRAWER_H

#include "utils/IColor.h"
#include "utils/ITransformation.h"
#include "scene/Polygon.h"
#include "utils/IBuffer.h"

class IDrawer {
public:

    virtual void drawPolygon(const Polygon &, const IColor &) = 0;

    virtual void setCameraTransformation(const ITransformation&) = 0;

    virtual void setObjectTransformation(const ITransformation&) = 0;

    virtual void clear() = 0;

    virtual void show() = 0;

    virtual void resize(int, int) = 0;

    virtual IBuffer<IColor> & image() = 0;
};

#endif //_IDRAWER_H