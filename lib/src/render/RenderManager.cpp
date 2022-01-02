#include "render/RenderManager.h"

const std::shared_ptr<IDrawer> &RenderManager::getDrawer() const {
    return _drawer;
}

void RenderManager::setDrawer(const std::shared_ptr<IDrawer> &drawer) {
    _drawer = drawer;
}

void RenderManager::render(const std::shared_ptr<RenderContext> &context, const std::shared_ptr<IVisitor>& visitor) {
    auto cameraTransformation = getCamera()->getTransformation(context->time);

    getDrawer()->clear();
    getDrawer()->setRenderContext(context);
    getDrawer()->setCameraTransformation(*cameraTransformation);


    for (auto &i: *getScene())
    {
        i->accept(*visitor);
    }

    getDrawer()->show();

}

const std::shared_ptr<Camera> &RenderManager::getCamera() const {
    return _camera;
}

void RenderManager::setCamera(const std::shared_ptr<Camera> &camera) {
    _camera = camera;
}

const std::shared_ptr<Scene> &RenderManager::getScene() const {
    return _scene;
}

void RenderManager::setScene(const std::shared_ptr<Scene> &scene) {
    _scene = scene;
}