//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_OGLDRAWER_H
#define PROJECT_OGLDRAWER_H

#include <render/IDrawer.h>

#include <QOpenGLWidget>


class OglDrawer : public IDrawer{
private:
    int _width = 800;
    int _height = 600;

    long last_time = 0, last_time_2 = 0;
    int frame = 0;

    QOpenGLWidget &_widget;
private:
    void _setOrtho();
public:
    OglDrawer(QOpenGLWidget &widget);

    void drawPolygon(const Polygon &polygon, const IColor &color) override;

    void setCameraTransformation(const ITransformation &transformation) override;

    void setObjectTransformation(const ITransformation &transformation) override;

    void clear() override;

    void show() override;

    void printFps();

    void resize(int w, int h) override;

    IBuffer<IColor> &image() override;
};


#endif //PROJECT_OGLDRAWER_H
