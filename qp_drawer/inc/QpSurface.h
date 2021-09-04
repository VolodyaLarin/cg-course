//
// Created by volodya on 02.09.2021.
//

#ifndef PROJECT_QPSURFACE_H
#define PROJECT_QPSURFACE_H

#include <vector>
#include <QPointF>
#include <utils/CoordWrapper.h>

class QpSurface {
public:
    float a = 0, b = 0, c = 0, d = 0;

    static QpSurface makeSurf(const std::vector<std::shared_ptr<ICoord>>& points) {
        QpSurface surface;

        auto p = points[0];
        auto a = p->diff(*points[1]);
        auto b = p->diff(*points[2]);

        auto vector = a->vectorProduct(*b);

        surface.a = vector->getX();
        surface.b = vector->getY();
        surface.c = vector->getZ();
        surface.d = - surface.a * p->getX() - surface.b *p->getY() - surface.c * p->getZ();

        return surface;
    };
};
#endif //PROJECT_QPSURFACE_H
