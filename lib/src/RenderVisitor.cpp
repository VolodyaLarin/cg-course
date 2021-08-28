#include "RenderVisitor.h"

void RenderVisitor::visitModel(Model &model) {

}

void RenderVisitor::visitCamera(Camera &camera) {

}

RenderVisitor::RenderVisitor(const std::shared_ptr<ITransformationFactory> &transformationFactory,
                             const std::shared_ptr<RenderContext> &context, const std::shared_ptr<IDrawer> &drawer)
        : _transformationFactory(transformationFactory), _context(context), _drawer(drawer) {}

void RenderVisitor::_createObjectTransformation(const ISceneObject &) {

}
