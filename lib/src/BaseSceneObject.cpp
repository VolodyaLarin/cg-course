/**
 * Project Untitled
 */


#include "BaseSceneObject.h"

AnimatedCoordProperty &BaseSceneObject::position() {
    return _position;
}

AnimatedCoordProperty &BaseSceneObject::rotation() {
    return _rotation;
}

AnimatedCoordProperty &BaseSceneObject::size() {
    return _size;
}

const AnimatedCoordProperty &BaseSceneObject::getPosition() const {
    return _position;
}

const AnimatedCoordProperty &BaseSceneObject::getRotation() const {
    return _rotation;
}

const AnimatedCoordProperty &BaseSceneObject::getSize() const {
    return _size;
}


const IColor &BaseSceneObject::getColor() const {
    return *_color;
}

void BaseSceneObject::setColor(const IColor &color) {
    _color = color.clone();
}
