/**
 * Project Untitled
 */


#include "render/BaseDrawer.h"

void BaseDrawer::setCameraTransformation(const ITransformation &transformation) {
    _cameraTrans = transformation.clone();
}

void BaseDrawer::setObjectTransformation(const ITransformation &transformation) {
    _objectTrans = transformation.clone();
}

void BaseDrawer::setRenderContext(std::shared_ptr<RenderContext> context) {
    _context = context;
}

const std::shared_ptr<RenderContext> &BaseDrawer::getRenderContext() {
    return _context;
}
