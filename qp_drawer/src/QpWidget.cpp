//
// Created by volodya on 03.09.2021.
//

#include <QpDrawer.h>

#include <utility>
#include <iostream>
#include "QpWidget.h"
#include "QPainter"
#include "QResizeEvent"

void QpWidget::paintEvent(QPaintEvent *event) {
    _drawFnc();
    auto image = _drawer->getQImage();
    QPainter painter(this);


    painter.drawImage(QRect(0,0, width, height), image, image.rect(), Qt::DiffuseAlphaDither);

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

    painter.setFont(QFont("Arial", 50));
    painter.drawText( 5, 55, QString::number(fps));
}

std::shared_ptr<IDrawer> QpWidget::getDrawer() const {
    return _drawer;
}

void QpWidget::setDrawer(const std::shared_ptr<IDrawer> &drawer) {
    _drawer = std::dynamic_pointer_cast<QpDrawer>(drawer);
}

const std::function<void()> &QpWidget::getDrawFnc() const {
    return _drawFnc;
}

void QpWidget::setDrawFnc(const std::function<void(void)> &drawFnc) {
    _drawFnc = drawFnc;
}

void QpWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    width = event->size().width();
    height = event->size().height();

    _drawer->resize(width, height);
}

QpWidget::QpWidget(QWidget *parent) : QWidget(parent) {
    _drawer = std::make_shared<QpDrawer>();
}
