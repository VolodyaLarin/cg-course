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
    static float LightVec[] = {3 / 5.0f, -4 / 5.0f, 0};


    auto &normal = polygon.getNormal();
    auto gr0 = [](float x) {
        return x > 0 ? x : 1;
    };
    float intens =
            0.2f + 0.8f - gr0(std::acos(
                    normal.getX() * LightVec[0] +
                    normal.getY() * LightVec[1] +
                    normal.getZ() * LightVec[2]
            ) / M_PI) * 0.8f;

    glBegin(GL_POLYGON);
    {
        glColor4f(color.getR() * intens, color.getG() * intens, color.getB() * intens, color.getA());
        for (auto &coord: polygon) {
            glVertex3f(coord->getX(), coord->getY(), coord->getZ());
        }
    }
    glEnd();
}

void OglDrawer::setCameraTransformation(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        glMatrixMode(GL_PROJECTION);

        auto matrix = glm::value_ptr(glmTransf.matrix);

        glLoadMatrixf(matrix);
        _setOrtho();

    }
    catch (std::bad_cast &err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::setObjectTransformation(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(glm::value_ptr(glmTransf.matrix));
    }
    catch (std::bad_cast &err) {
        throw GlmException("OglDrawer can works only with GlmTransformation classes");
    }
}

void OglDrawer::clear() {
    _widget.makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void OglDrawer::show() {
    printFps();
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

    float k = float(_width) / _height;

    glScalef(1, k, 1);
}

OglDrawer::OglDrawer(QOpenGLWidget &widget) : _widget(widget) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void OglDrawer::printFps() {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000000;

    static const int framesCount = 64;
    if (frame == 0)
        last_time = ms.count();
    if (frame == framesCount)
        last_time_2 = ms.count();
    frame = (frame + 1) % (framesCount * 2);

    int fps = 0;
    if (frame < framesCount) {
        auto dt = ms.count() - last_time_2;
        fps = (frame + framesCount) * 1000 / dt;
    } else {
        auto dt = ms.count() - last_time;
        fps = frame * 1000 / dt;
    }

    auto printNumber = [](short x) {
        auto dl = [](int x, int y) {
            static glm::vec2 sign[] = {
                    glm::vec2(0, 0), // 0
                    glm::vec2(0, 1), // 1
                    glm::vec2(1, 0), // 2
                    glm::vec2(1, 1), // 3
                    glm::vec2(0, 2), // 4
                    glm::vec2(1, 2), // 5
            };

            glBegin(GL_LINES);
            {
                glVertex2f(sign[x].x, sign[x].y);
                glVertex2f(sign[y].x, sign[y].y);
            }
            glEnd();
        };

        /*
            4----5
            |    |
            1----3
            |    |
            0----2
         */

        if (x == 0 || x == 2 || x == 3 || x == 5 || x == 6 || x == 7 || x == 8 || x == 9) dl(4, 5);
        if (x == 0 || x == 4 || x == 5 || x == 6 || x == 8 || x == 9) dl(4, 1);
        if (x == 0 || x == 1 || x == 2 || x == 3 || x == 4 || x == 7 || x == 8 || x == 9) dl(5, 3);
        if (x == 2 || x == 3 || x == 4 || x == 5 || x == 6 || x == 8 || x == 9) dl(1, 3);
        if (x == 0 || x == 2 || x == 6 || x == 8) dl(0, 1);
        if (x == 0 || x == 1 || x == 3 || x == 4 || x == 5 || x == 6 || x == 7 || x == 8 || x == 9) dl(3, 2);
        if (x == 0 || x == 2 || x == 3 || x == 5 || x == 6 || x == 8 || x == 9) dl(0, 2);
    };
    glColor3f(0, 0.7, 0);
    glLineWidth(3);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    {
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        {
            glLoadIdentity();
            glTranslatef(-1, 1, 0);
            glScalef(0.03, 0.03 * _width / _height, 0);
            glTranslatef(1, -3, 0);
            printNumber(fps / 100);
            glTranslatef(1.5, 0, 0);
            printNumber(fps / 10 % 10);
            glTranslatef(1.5, 0, 0);
            printNumber(fps % 10);
        }
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }
    glPopMatrix();

}
