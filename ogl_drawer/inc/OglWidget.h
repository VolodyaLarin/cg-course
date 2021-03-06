//
// Created by volodya on 30.08.2021.
//

#ifndef PROJECT_OGLWIDGET_H
#define PROJECT_OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>

#include "OglDrawer.h"

class OglWidget : public QOpenGLWidget {
private:
    std::shared_ptr<IDrawer> drawer = nullptr;
    std::function<void(void)> drawFnc = nullptr;
public:
    explicit OglWidget(QWidget *parent) : QOpenGLWidget(parent)
    {
        // Anti-Aliasing
        QSurfaceFormat format;
        format.setSamples(4);
        setFormat(format);

        drawer = std::make_shared<OglDrawer>(*this);
    }

    [[nodiscard]] const std::shared_ptr<IDrawer> &getDrawer() const {
        return drawer;
    }
    [[nodiscard]] const std::function<void(void)> &getDrawFnc() const {
        return drawFnc;
    }

    void setDrawFnc(const std::function<void(void)> &fnc) {
        drawFnc = fnc;
    }

protected:
    void initializeGL() override {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void resizeGL(int w, int h) override {
        drawer->resize(w, h);
    }

    void paintGL() override {
        drawer->clear();

        if (drawFnc) {
            drawFnc();
        }

        drawer->show();
    }
};

#endif //PROJECT_OGLWIDGET_H
