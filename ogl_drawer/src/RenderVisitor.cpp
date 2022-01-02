#include "RenderVisitor.h"

#include <utility>
#include <thread>
#include "scene/Model.h"
#include "OglDrawer.h"
#include "GlmTransformation.h"

void RenderVisitor::visitModel(Model &model) {
    shared_ptr<ITransformation> objectTransformation = _createObjectTransformation(model, _drawer->getRenderContext()->time);
    shared_ptr<ITransformation> objectDTransformation= _createObjectTransformation(model, _drawer->getRenderContext()->time - _drawer->getRenderContext()->exposition);


    if (_sendPosition) {
        auto VP = _drawer->V;
        auto P = _drawer->P;

        auto M1 = std::dynamic_pointer_cast<GlmTransformation>(objectTransformation)->matrix;
        auto M2 = std::dynamic_pointer_cast<GlmTransformation>(objectDTransformation)->matrix;

        auto MVP1 = VP * M1;
        auto MVP2 = VP * M2;

        glUniformMatrix4fv(_shaders->VL->currMVP, 1, GL_FALSE, &MVP1[0][0]);
        glUniformMatrix4fv(_shaders->VL->prevMVP, 1, GL_FALSE, &MVP2[0][0]);
        glUniformMatrix4fv(_shaders->VL->proj, 1, GL_FALSE, &P[0][0]);
    } else {

        _drawer->setObjectTransformation(*objectTransformation);

        auto &MVP = _drawer->MVP;
        auto &M = _drawer->M;
        auto &V = _drawer->V;
        auto &color = model.getColor();

        glUniformMatrix4fv(_shaders->CZ->MVP, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(_shaders->CZ->Model, 1, GL_FALSE, &M[0][0]);
        glUniformMatrix4fv(_shaders->CZ->View, 1, GL_FALSE, &V[0][0]);
    }

    for (auto &polygon: model) {
        _drawer->drawPolygon(polygon, model.getColor());
    }

}

void RenderVisitor::visitCamera(Camera &camera) {

}

RenderVisitor::RenderVisitor(std::shared_ptr<OglDrawer> drawer)
        : _drawer(std::move(drawer)) {}

std::unique_ptr<ITransformation> RenderVisitor::_createObjectTransformation(const ISceneObject &obj, Time now)  {

    auto transformation = _transformationFactory->create();

    transformation->join(
                    *_transformationFactory->createRotation(*obj.getRotation().get(now))
            )
            .join(
                    *_transformationFactory->createScale(*obj.getSize().get(now))
            )
            .join(
                    *_transformationFactory->createPosition(*obj.getPosition().get(now))
            );

    return transformation;
}

void RenderVisitor::setTransformationFactory(const std::shared_ptr<ITransformationFactory> &transformationFactory) {
    _transformationFactory = transformationFactory;
}

void RenderVisitor::setShaders(const shared_ptr<Shaders> &shaders) {
    _shaders = shaders;
}

void RenderVisitor::setSendPosition(bool sendPosition) {
    _sendPosition = sendPosition;
}

