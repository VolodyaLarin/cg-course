#include "scene/Camera.h"

ITransformation::Ptr Camera::getTransformation(Time t) const {

    auto transformation = _transformationFactory->createPosition(*getPosition().get(t)->invert());

    auto rotate = _transformationFactory->createPosition(*BaseSceneObject::getRotation().get(t)->invert());
    auto persp = _transformationFactory->createPerspective(_pespK);

    transformation->join(*rotate).join(*persp);

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

