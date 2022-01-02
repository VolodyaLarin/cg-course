//
// Created by volodya on 29.08.2021.
//

#include "OglDrawer.h"

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#include "GlmTransformation.h"
#include "GlmException.h"
#include "GlmCoord.h"


void OglDrawer::drawPolygon(const Polygon &polygon, const IColor &color) {
    static float LightVec[] = {3 / 5.0f, -4 / 5.0f, 0};


    auto &n = polygon.getNormal();
    auto normalV = glm::vec4(n.getX(), n.getY(), n.getZ(), 1);
    normalV = normalV * M;
    auto beginV = glm::vec4() * M;

    normalV = normalV - beginV;

    auto normalG = GlmCoord(normalV);
    auto normal = normalG.normalized();

    auto gr0 = [](float x) {
        return x > 0 ? x : 1;
    };
    float intens =
            0.2f + 0.8f - gr0(std::acos(
                    normal->getX() * LightVec[0] +
                    normal->getY() * LightVec[1] +
                    normal->getZ() * LightVec[2]
            ) / M_PI) * 0.8f;


    glUniform3f(_shaders->CZ->Color, color.getR() * intens, color.getG() * intens, color.getB() * intens);

    glBegin(GL_POLYGON);
    {
        for (auto &coord: polygon) {
            glVertex3f(coord->getX(), coord->getY(), coord->getZ());
        }
    }
    glEnd();

}

void OglDrawer::setCameraTransformation(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        V = glmTransf.matrix;

        MVP = P * V * M;
    }
    catch (std::bad_cast &err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::setObjectTransformation(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        M = glmTransf.matrix;

        MVP = P * V * M;
    }
    catch (std::bad_cast &err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}


void OglDrawer::setProjectionTransformation(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        P = glmTransf.matrix;

        MVP = P * V * M;
    }
    catch (std::bad_cast &err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void OglDrawer::show() {

}

void OglDrawer::resize(int w, int h) {
    _width = w;
    _height = h;

    _setOrtho();
}

IBuffer<IColor> &OglDrawer::image() {

}

void OglDrawer::_setOrtho() {
    P = glm::perspective(45., (double)_width/(double) _height, 0.1, 60.);
}


const std::shared_ptr<RenderContext> &OglDrawer::getRenderContext() {
    return _render_context;
}

void OglDrawer::setRenderContext(std::shared_ptr<RenderContext> context) {
    _render_context = context;
}

void OglDrawer::setShaders(const std::shared_ptr<Shaders> &shaders) {
    _shaders = shaders;
}

OglDrawer::OglDrawer() {
    _setOrtho();
}

