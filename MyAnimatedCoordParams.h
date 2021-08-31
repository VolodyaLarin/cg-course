//
// Created by volodya on 30.08.2021.
//

#ifndef PROJECT_MYANIMATEDCOORDPARAMS_H
#define PROJECT_MYANIMATEDCOORDPARAMS_H

#include <QWidget>
#include <scene/AnimatedCoordProperty.h>
#include <utils/IFactory.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MyAnimatedCoordParams; }
QT_END_NAMESPACE

class MyAnimatedCoordParams : public QWidget {
Q_OBJECT

public:
    MyAnimatedCoordParams(std::function<AnimatedCoordProperty &()>, QWidget *parent = nullptr);

    ~MyAnimatedCoordParams() override;

    void renderValues();

private:
    Time QTime2Time(const QTime &time);

    QTime Time2QTime(Time time);


private slots:

    void on_beginTime_userTimeChanged(const QTime &time);

    void on_beginX_valueChanged(double arg1);

    void on_beginY_valueChanged(double arg1);

    void on_beginZ_valueChanged(double arg1);

    void on_endTime_userTimeChanged(const QTime &time);

    void on_endX_valueChanged(double arg1);

    void on_endY_valueChanged(double arg1);

    void on_endZ_valueChanged(double arg1);

private slots:

private:
    std::function<AnimatedCoordProperty &()> property;
    Ui::MyAnimatedCoordParams *ui;
};


#endif //PROJECT_MYANIMATEDCOORDPARAMS_H
