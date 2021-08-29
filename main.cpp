#include <QApplication>
#include <QPushButton>

#include <QOpenGLWidget>
#include <QTimer>
#include <QResizeEvent>

#include <OglDrawer.h>
#include <GlmCoord.h>
#include <OglColor.h>
#include <loaders/ObjModelLoader.h>
#include <GlmCoordFactory.h>
#include <GlmTransformationFactory.h>
#include <iostream>
#include "chrono"


class MyGLWidget : public QOpenGLWidget {
public:
    Model::Ptr model;
    std::shared_ptr<IDrawer> drawer;

    std::vector<OglColor> colors = {
            OglColor(0 / 255.0f, 18 / 255.0f, 25 / 255.0f),
            OglColor(0 / 255.0f, 95 / 255.0f, 115 / 255.0f),
            OglColor(10 / 255.0f, 147 / 255.0f, 150 / 255.0f),
            OglColor(148 / 255.0f, 210 / 255.0f, 189 / 255.0f),
            OglColor(233 / 255.0f, 216 / 255.0f, 166 / 255.0f),
            OglColor(238 / 255.0f, 155 / 255.0f, 0 / 255.0f),
            OglColor(202 / 255.0f, 103 / 255.0f, 2 / 255.0f),
            OglColor(187 / 255.0f, 62 / 255.0f, 3 / 255.0f),
            OglColor(174 / 255.0f, 32 / 255.0f, 18 / 255.0f),
            OglColor(155 / 255.0f, 34 / 255.0f, 38 / 255.0f),
    };


    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

protected:
    void initializeGL() override {
        drawer = std::make_shared<OglDrawer>(*this);
        model = ObjModelLoader().load("./deer.obj", GlmCoordFactory());
        for (auto &pol: *model) {
            for (auto &coord: pol) {
                std::cout << coord->getX() << " " << coord->getY() << " " << coord->getZ() << ";";
            }
            std::cout << std::endl;
        }

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void resizeGL(int w, int h) override {
        drawer->resize(w, h);
    }

    void paintGL() override {
        using namespace std::chrono;

        // get current time
        auto now = system_clock::now();

        // get number of milliseconds for the current second
        // (remainder after division into seconds)
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 10000000;


        float x = ms.count() / 500.0f;
        drawer->clear();

        auto camera_view = GlmTransformationFactory().create();
        (
                *camera_view
        ).join(
                *GlmTransformationFactory().createScale(GlmCoord(0.1, 0.1, 0.1))
        ).join(
                *GlmTransformationFactory().createPosition(GlmCoord(0, 0, -1.4))
        ).join(
                *GlmTransformationFactory().createPerspective(0.001)
        );

        drawer->setCameraTransformation(*camera_view);


        auto objectView = GlmTransformationFactory().create();
        (
                *objectView
        ).join(
                *GlmTransformationFactory().createRotation(GlmCoord(0.1, x * 0.75, 0))
        );

        drawer->setObjectTransformation(*objectView);


        int i = 0;
        for (auto &pol: *model) {
            drawer->drawPolygon(pol, colors[i % colors.size()]);
            i++;
        }
        drawer->show();
    }

//    void resizeEvent(QResizeEvent *e) override {
////        drawer->resize(e->)
//    }

};

int main(int argc, char *argv[]) {
    srandom(time(nullptr));

    QApplication a(argc, argv);

    MyGLWidget widget(nullptr);
    widget.resize(800, 600);
    widget.show();

    QTimer timer;

    auto widget_ptr = &widget;
    QObject::connect(&timer, &QTimer::timeout, [widget_ptr]() {
        widget_ptr->repaint();
    });

    timer.setInterval(10);
    timer.start();

    return QApplication::exec();
}
