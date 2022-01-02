/**
 * Project Untitled
 */


#ifndef _IDRAWER_H
#define _IDRAWER_H

#include "utils/IColor.h"
#include "utils/ITransformation.h"
#include "scene/Polygon.h"
#include "utils/IBuffer.h"
#include "RenderContext.h"

class IDrawer {
public:

    virtual void drawPolygon(const Polygon &, const IColor &) = 0;

    virtual void setCameraTransformation(const ITransformation&) = 0;

    virtual void setObjectTransformation(const ITransformation&) = 0;

    virtual void setProjectionTransformation(const ITransformation&) = 0;

    virtual void clear() = 0;

    virtual void show() = 0;

    virtual void resize(int, int) = 0;

    virtual IBuffer<IColor> & image() = 0;

    virtual void setRenderContext(std::shared_ptr<RenderContext> context) = 0;

    virtual const std::shared_ptr<RenderContext>& getRenderContext() = 0;

};

#endif //_IDRAWER_H