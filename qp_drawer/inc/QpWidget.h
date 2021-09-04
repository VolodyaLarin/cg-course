//
// Created by volodya on 03.09.2021.
//

#ifndef PROJECT_QPWIDGET_H
#define PROJECT_QPWIDGET_H

#include <QWidget>
#include <QpDrawer.h>

class QpWidget: public QWidget {
private:
    std::shared_ptr<QpDrawer> _drawer = nullptr;
    std::function<void(void)> _drawFnc = nullptr;
    int width = 0, height = 0;

    long last_time = 0, last_time_2 = 0, frame = 0;
public:
    explicit QpWidget(QWidget *parent = nullptr);

    std::shared_ptr<IDrawer> getDrawer() const;

    void setDrawer(const std::shared_ptr<IDrawer> &drawer);

    const std::function<void(void)> &getDrawFnc() const;

    void setDrawFnc(const std::function<void(void)> &drawFnc);

protected:
    void resizeEvent(QResizeEvent *event) override;

    void paintEvent(QPaintEvent *event) override;
};


#endif //PROJECT_QPWIDGET_H
