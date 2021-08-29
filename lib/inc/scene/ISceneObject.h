/**
 * Project Untitled
 */


#ifndef _ISCENEOBJECT_H
#define _ISCENEOBJECT_H

#include "AnimatedCoordProperty.h"
#include "utils/IColor.h"
#include "SceneObjectType.h"
#include "IVisitor.h"

class ISceneObject {
public: 
    
    virtual AnimatedCoordProperty & position() = 0;

    virtual AnimatedCoordProperty & rotation() = 0;

    virtual AnimatedCoordProperty & size() = 0;

    [[nodiscard]] virtual const AnimatedCoordProperty & getPosition() const = 0;

    [[nodiscard]] virtual const AnimatedCoordProperty & getRotation() const = 0;

    [[nodiscard]] virtual const AnimatedCoordProperty & getSize() const = 0;

    [[nodiscard]] virtual SceneObjectType getType() const = 0;

    [[nodiscard]] virtual const IColor& getColor() const = 0;

    virtual void setColor(const IColor&) = 0;

    virtual void accept(IVisitor &) = 0;
};

#endif //_ISCENEOBJECT_H