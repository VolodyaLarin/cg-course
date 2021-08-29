#include "render/RenderManager.h"

const std::shared_ptr<IDrawer> &RenderManager::getDrawer() const {
    return _drawer;
}

void RenderManager::setDrawer(const std::shared_ptr<IDrawer> &drawer) {
    _drawer = drawer;
}

void RenderManager::render(RenderContext &) {

}
