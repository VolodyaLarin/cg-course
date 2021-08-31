#include "scene/Camera.h"

ITransformation::Ptr Camera::getTransformation(Time t) const {

    auto transformation = _transformationFactory->createPosition(*getPosition().get(t)->invert());
    auto size = getPosition().get(0)->clone();
    size->setX(0.1);
    size->setY(0.1);
    size->setZ(0.1);

    auto scale = _transformationFactory->createScale(*size);
    auto rotate = _transformationFactory->createRotation(*BaseSceneObject::getRotation().get(t)->invert());
    auto persp = _transformationFactory->createPerspective(_pespK);

    transformation->join(*scale).join(*rotate).join(*persp);

    return transformation;
}

ITransformation::Ptr Camera::getInvTransformation(Time t) const {
    auto transformation = _transformationFactory->createPerspective(- _pespK);

    auto rotate = _transformationFactory->createPosition(*BaseSceneObject::getRotation().get(t));
    auto move = _transformationFactory->createPosition(*getPosition().get(t));

    transformation->join(*rotate).join(*move);

    return transformation;
}

SceneObjectType Camera::getType() const {
    return SceneObjectType("Camera");
}

void Camera::accept(IVisitor &visitor) {
    visitor.visitCamera(*this);
}

void Camera::setTransformationFactory(const std::shared_ptr<ITransformationFactory> &transformationFactory) {
    _transformationFactory = transformationFactory;
}

