/**
 * Project Untitled
 */


#ifndef _BASESCENEOBJECT_H
#define _BASESCENEOBJECT_H

#include <memory>
#include "scene/ISceneObject.h"


class BaseSceneObject: public ISceneObject {
public:

    AnimatedCoordProperty &position() override;

    AnimatedCoordProperty &rotation() override;

    AnimatedCoordProperty &size() override;

    const AnimatedCoordProperty &getPosition() const override;

    const AnimatedCoordProperty &getRotation() const override;

    const AnimatedCoordProperty &getSize() const override;

    const IColor &getColor() const override;

    void setColor(const IColor &color) override;

private:
    AnimatedCoordProperty _position;
    AnimatedCoordProperty _rotation;
    AnimatedCoordProperty _size;
    std::unique_ptr<IColor> _color;
};

#endif //_BASESCENEOBJECT_H