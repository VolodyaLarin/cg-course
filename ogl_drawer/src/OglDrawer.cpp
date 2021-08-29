//
// Created by volodya on 29.08.2021.
//

#include "OglDrawer.h"

#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "GlmTransformation.h"
#include "GlmException.h"

#include <QOpenGLContext>

#include <QOpenGLFunctions_3_0>
#include <QOpenGLExtraFunctions>




void OglDrawer::drawPolygon(const Polygon &polygon, const IColor &color) {
    glBegin(GL_POLYGON);
        glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
        for (auto &coord : polygon) {
            glVertex3f(coord->getX(),coord->getY(), coord->getZ());
        }
    glEnd();
}

void OglDrawer::setCameraTransformation(const ITransformation &transformation) {
    try {
        auto& glmTransf = dynamic_cast<const GlmTransformation&>(transformation);

        glMatrixMode(GL_PROJECTION);

        auto matrix  = glm::value_ptr(glmTransf.matrix);

        glLoadMatrixf(matrix);
        _setOrtho();

    }
    catch (std::bad_cast& err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::setObjectTransformation(const ITransformation &transformation) {
    try {
        auto& glmTransf = dynamic_cast<const GlmTransformation&>(transformation);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(glmTransf.matrix));
    }
    catch (std::bad_cast& err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::clear() {
    _widget.makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f,1.0f,1.0f,1.0f);
}

void OglDrawer::show() {
    _widget.doneCurrent();
}

void OglDrawer::resize(int w, int h) {
    _width = w;
    _height = h;

    // @todo update camera matrix!
}

IBuffer<IColor> &OglDrawer::image() {

}

void OglDrawer::_setOrtho() {
    glMatrixMode(GL_PROJECTION);

    float k  = float(_width) / _height;

    glScalef(1, k, 1);
//    glOrtho(-1, 1, -k, k, -1000000000000.0f, 10000000000.0f);
}

OglDrawer::OglDrawer(QOpenGLWidget &widget) : _widget(widget) {}
