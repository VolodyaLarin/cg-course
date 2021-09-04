//
// Created by volodya on 02.09.2021.
//

#ifndef PROJECT_QPDRAWER_H
#define PROJECT_QPDRAWER_H

#include <QImage>
#include "render/BaseDrawer.h"
#include "QpSurface.h"

class QpDrawer: public BaseDrawer {
private:
    QImage _image;
public:
    void drawPolygon(const Polygon &polygon, const IColor &color) override;

    void clear() override;

    void show() override;

    void resize(int i, int i1) override;

    void setRenderContext(std::shared_ptr<RenderContext> context) override;

    IBuffer<IColor> &image() override;

    const QImage &getQImage() const;

private:
    static float findZ(QpSurface surface, int x, int y);
};


#endif //PROJECT_QPDRAWER_H
