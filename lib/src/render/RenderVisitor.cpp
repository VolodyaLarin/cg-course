#include "render/RenderVisitor.h"

#include <utility>

void RenderVisitor::visitModel(Model &model) {

}

void RenderVisitor::visitCamera(Camera &camera) {

}

RenderVisitor::RenderVisitor(std::shared_ptr<ITransformationFactory> transformationFactory,
                             std::shared_ptr<RenderContext> context, std::shared_ptr<IDrawer> drawer)
        : _transformationFactory(std::move(transformationFactory)), _context(std::move(context)), _drawer(std::move(drawer)) {}

void RenderVisitor::_createObjectTransformation(const ISceneObject &) {

}
