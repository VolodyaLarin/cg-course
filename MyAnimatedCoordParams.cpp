//
// Created by volodya on 30.08.2021.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MyAnimatedCoordParams.h" resolved

#include "MyAnimatedCoordParams.h"
#include "ui_MyAnimatedCoordParams.h"

#include <QTime>
#include <utility>

MyAnimatedCoordParams::MyAnimatedCoordParams(std::function<AnimatedCoordProperty &()> prop, QWidget *parent) :
        QWidget(parent), ui(new Ui::MyAnimatedCoordParams), property(std::move(prop)) {
    ui->setupUi(this);

    renderValues();
}

MyAnimatedCoordParams::~MyAnimatedCoordParams() {
    delete ui;
}

Time MyAnimatedCoordParams::QTime2Time(const QTime &time) {
    return time.hour() * 60 + time.minute();
}

QTime MyAnimatedCoordParams::Time2QTime(Time time) {
    return QTime(int(time) / 60, int(time) % 60);
}

void MyAnimatedCoordParams::on_beginTime_userTimeChanged(const QTime &time) {
    property().setBegin(QTime2Time(time), *property().getBegin().second);
}

void MyAnimatedCoordParams::on_beginX_valueChanged(double value) {
    auto coord = property().getBegin().second->clone();
    coord->setX(value);
    property().setBegin(property().getBegin().first, *coord);
}


void MyAnimatedCoordParams::on_beginY_valueChanged(double value) {
    auto coord = property().getBegin().second->clone();
    coord->setY(value);
    property().setBegin(property().getBegin().first, *coord);
}

void MyAnimatedCoordParams::on_beginZ_valueChanged(double value) {
    auto coord = property().getBegin().second->clone();
    coord->setZ(value);
    property().setBegin(property().getBegin().first, *coord);
}

void MyAnimatedCoordParams::on_endTime_userTimeChanged(const QTime &time) {
    property().setEnd(QTime2Time(time), *property().getEnd().second);

}

void MyAnimatedCoordParams::on_endX_valueChanged(double value) {
    auto coord = property().getEnd().second->clone();
    coord->setX(value);
    property().setEnd(property().getEnd().first, *coord);
}

void MyAnimatedCoordParams::on_endY_valueChanged(double value) {
    auto coord = property().getEnd().second->clone();
    coord->setY(value);
    property().setEnd(property().getEnd().first, *coord);
}

void MyAnimatedCoordParams::on_endZ_valueChanged(double value) {
    auto coord = property().getEnd().second->clone();
    coord->setZ(value);
    property().setEnd(property().getEnd().first, *coord);
}

void MyAnimatedCoordParams::renderValues() {
    auto begin = property().getBegin(), end = property().getEnd();

    ui->beginTime->setTime(Time2QTime(begin.first));
    ui->beginX->setValue(begin.second->getX());
    ui->beginY->setValue(begin.second->getY());
    ui->beginZ->setValue(begin.second->getZ());

    ui->endTime->setTime(Time2QTime(end.first));
    ui->endX->setValue(end.second->getX());
    ui->endY->setValue(end.second->getY());
    ui->endZ->setValue(end.second->getZ());
}
