/**
 * Project Untitled
 */


#ifndef _RENDERMANAGER_H
#define _RENDERMANAGER_H

#include "IDrawer.h"
#include "RenderContext.h"

class RenderManager {
public:
    [[nodiscard]] const std::shared_ptr<IDrawer> &getDrawer() const;

    void setDrawer(const std::shared_ptr<IDrawer> &drawer);

    [[nodiscard]] const std::shared_ptr<Camera> &getCamera() const;

    void setCamera(const std::shared_ptr<Camera> &camera);

    [[nodiscard]] const std::shared_ptr<Scene> &getScene() const;

    void setScene(const std::shared_ptr<Scene> &scene);

    void render(const std::shared_ptr<RenderContext> &);

private:
    std::shared_ptr<IDrawer> _drawer;
    std::shared_ptr<Camera> _camera = nullptr;
    std::shared_ptr<Scene> _scene = nullptr;
};

#endif //_RENDERMANAGER_H