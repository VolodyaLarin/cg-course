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

    const std::string &getName() const override;

    void setName(const std::string &string) override;

private:
    AnimatedCoordProperty _position;
    AnimatedCoordProperty _rotation;
    AnimatedCoordProperty _size;
    std::unique_ptr<IColor> _color;
    std::string _name;

};

#endif //_BASESCENEOBJECT_H