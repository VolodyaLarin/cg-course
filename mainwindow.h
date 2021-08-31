#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene/Scene.h>
#include <loaders/ObjModelLoader.h>
#include <OglWidget.h>
#include <QTimer>
#include "MyAnimatedCoordParams.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Q_DECLARE_METATYPE(Array<ObjectPtr>::iterator)

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;


private slots:

    void on_playButton_clicked();

    void on_curentTimeSlider_sliderMoved(int position);

    void on_curentTime_userTimeChanged(const QTime &time);

    void on_deleteObject_clicked();

    void on_objectName_editingFinished();

    void on_objectColor_editingFinished();

    void on_objectsList_currentRowChanged(int currentRow);

    void on_importModel_clicked();

    void on_objectColorChoose_clicked();

private:
    Ui::MainWindow *ui;
    MyAnimatedCoordParams *widgetTranslate;
    MyAnimatedCoordParams *widgetScale;
    MyAnimatedCoordParams *widgetRotate;

    Scene _scene;
    ObjModelLoader loader;
    std::shared_ptr<OglWidget> canvas = nullptr;

    QTimer _timer;

    Time _currentTime = 0;
    bool _is_played = false;

    Scene::ObjectPtr _currentObject;

    void updateObjectsList();

    void renderCurrentObjectParameters();

    void renderCurrentTime();
};

#endif // MAINWINDOW_H
