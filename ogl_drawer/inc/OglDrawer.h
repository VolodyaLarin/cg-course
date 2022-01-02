//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_OGLDRAWER_H
#define PROJECT_OGLDRAWER_H

#include <render/IDrawer.h>
#include "Shaders.h"
#include <glm/glm.hpp>



class OglDrawer : public IDrawer{
private:
    int _width = 800;
    int _height = 600;

    long last_time = 0, last_time_2 = 0;
    int frame = 0;

public:
    glm::mat4 M, V, P, MVP;

    std::shared_ptr<RenderContext> _render_context = nullptr;
    std::shared_ptr<Shaders> _shaders;


public:
    OglDrawer();

    void setShaders(const shared_ptr<Shaders> &shaders);

private:
    void _setOrtho();
public:

    void drawPolygon(const Polygon &polygon, const IColor &color) override;

    void setCameraTransformation(const ITransformation &transformation) override;

    void setObjectTransformation(const ITransformation &transformation) override;

    void setProjectionTransformation(const ITransformation &transformation) override;

    void clear() override;

    void show() override;


    void resize(int w, int h) override;

    IBuffer<IColor> &image() override;

    void setRenderContext(std::shared_ptr<RenderContext> context) override;

    const std::shared_ptr<RenderContext>& getRenderContext() override;
};


#endif //PROJECT_OGLDRAWER_H
