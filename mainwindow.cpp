#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "MyAnimatedCoordParams.h"


#include <QObject>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
#include <QFileDialog>

#include <GlmCoordFactory.h>
#include <scene/Camera.h>
#include <iostream>
#include <filesystem>
#include <GlmTransformationFactory.h>
#include <QColorDialog>
#include <QpColor.h>
#include <QpWidget.h>
#include <MatrixBuffer.h>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->canvas->hide();

    canvas = std::make_shared<QpWidget>();
    ui->rightLayout->removeWidget(ui->canvas);
    ui->rightLayout->removeItem(ui->playerBox);
    ui->rightLayout->addWidget(canvas.get());
    ui->rightLayout->addItem(ui->playerBox);


    QObject::connect(&_timer, &QTimer::timeout, [this]() {
        canvas->repaint();
    });

    _timer.setInterval(100 / 6);
    _timer.start();

    auto camera = std::make_shared<Camera>();
    camera->setTransformationFactory(std::make_shared<GlmTransformationFactory>());

    auto zeroACP = [](AnimatedCoordProperty &ac) {
        ac.setBegin(0, GlmCoord());
        ac.setEnd(0, GlmCoord());
    };
    zeroACP(camera->position());
    zeroACP(camera->size());
    zeroACP(camera->rotation());

    camera->position().setBegin(0, GlmCoord(0, 0, 10));
    camera->position().setEnd(120, GlmCoord(0, 0, 30));

    _scene = std::make_shared<Scene>();

    _scene->add(std::static_pointer_cast<ISceneObject>(camera));
    camera->setColor(QpColor());
    camera->setName("Камера");
    _currentObject = camera;

    _renderManager = std::make_shared<RenderManager>();
    _renderManager->setCamera(camera);
    _renderManager->setDrawer(canvas->getDrawer());
    _renderManager->setScene(_scene);

    auto context = std::make_shared<RenderContext>();
    context->z = std::make_shared<ZBuffer>(0,0,1e10);

    canvas->getDrawer()->setRenderContext(context);

    canvas->setDrawFnc([this]() {
        if (_is_played) {
            using namespace std::chrono;
            auto diff = system_clock::now() - _lastTime;
            auto ms = duration_cast<milliseconds>(diff);

            _currentTime += ms.count() / 1000.0f;
            if (_currentTime > 120) {
                _currentTime = 120;
                _is_played = false;
            }
            renderCurrentTime();
        }
        _lastTime = std::chrono::system_clock::now();

        _renderManager->getDrawer()->getRenderContext()->time = _currentTime;

        _renderManager->render(_renderManager->getDrawer()->getRenderContext());
    });

    widgetTranslate = new MyAnimatedCoordParams([this]() -> AnimatedCoordProperty & {
        return _currentObject->position();
    }, this);
    widgetScale = new MyAnimatedCoordParams([this]() -> AnimatedCoordProperty & {
        return _currentObject->size();
    }, this);
    widgetRotate = new MyAnimatedCoordParams([this]() -> AnimatedCoordProperty & {
        return _currentObject->rotation();
    }, this);

    widgetTranslate->show();
    widgetScale->show();
    widgetRotate->show();

    ui->tabWidget_2->addTab(widgetTranslate, QString::fromStdString("Перемещение"));
    ui->tabWidget_2->addTab(widgetRotate, QString::fromStdString("Поворот"));
    ui->tabWidget_2->addTab(widgetScale, QString::fromStdString("Размер"));

    updateObjectsList();
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::updateObjectsList() {
    ui->objectsList->clear();

    int i = 0;
    int currentI = 0;
    auto curObj = _currentObject;
    for (auto &object: *_scene) {
        ui->objectsList->addItem(
                QString::fromStdString(object->getName())
        );
        if (object == curObj) {
            currentI = i;
        }
        i++;
    }
    ui->objectsList->setCurrentRow(currentI);
}

void MainWindow::on_importModel_clicked() {
    QFileDialog dialog(nullptr);

    if (dialog.exec()) {
        auto files = dialog.selectedFiles();
        auto filename = files[0].toStdString();

        Model::Ptr model = nullptr;

        try {
            model = loader.load(filename, GlmCoordFactory());

        } catch (std::exception &e) {
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(
                    "Произошла ошибка. \n" + std::string(e.what())
            ));
            msgBox.exec();
        }

        _scene->add(model);
        model->setColor(QpColor(1, 0, 0));
        model->setName(std::filesystem::path(filename).filename());

        auto zeroACP = [](AnimatedCoordProperty &ac, float value = 0) {
            ac.setBegin(0, GlmCoord(value, value, value));
            ac.setEnd(0, GlmCoord(value, value, value));
        };
        zeroACP(model->position());
        zeroACP(model->size(), 1);
        zeroACP(model->rotation());

        updateObjectsList();
    }
}

void MainWindow::on_objectsList_currentRowChanged(int currentRow) {
    if (currentRow < 0) return;
    _currentObject = *(_scene->begin() + currentRow);

    renderCurrentObjectParameters();
}

void MainWindow::renderCurrentObjectParameters() {
    ui->objectName->setText(
            QString::fromStdString(_currentObject->getName())
    );
    ui->objectColor->setText(
            QString::fromStdString(_currentObject->getColor().getHEX())
    );

    widgetRotate->renderValues();
    widgetScale->renderValues();
    widgetTranslate->renderValues();

}

void MainWindow::on_objectColor_editingFinished() {
    auto color = _currentObject->getColor().clone();
    color->setHEX(ui->objectColor->text().toStdString());
    _currentObject->setColor(*color);
}

void MainWindow::on_objectName_editingFinished() {
    _currentObject->setName(ui->objectName->text().toStdString());
    updateObjectsList();
}

void MainWindow::on_objectColorChoose_clicked() {
    QColorDialog dialog(nullptr);
    const auto &color = _currentObject->getColor();
    dialog.setCurrentColor(QColor(
            color.getR() * 255,
            color.getG() * 255,
            color.getB() * 255,
            color.getA() * 255
    ));

    if (dialog.exec()) {
        auto qColor = dialog.currentColor();
        auto newColor = color.clone();
        newColor->setR(qColor.redF());
        newColor->setG(qColor.greenF());
        newColor->setB(qColor.blueF());
        newColor->setA(qColor.alphaF());

        _currentObject->setColor(*newColor);
        renderCurrentObjectParameters();
    }
}

void MainWindow::on_deleteObject_clicked() {
    for (auto i = _scene->begin(); i != _scene->end(); ++i) {
        if (*i == _currentObject) {
            _scene->remove(i);
            updateObjectsList();
            return;
        }
    }
}

void MainWindow::on_curentTime_userTimeChanged(const QTime &time) {
    _currentTime = time.minute() + time.hour() * 60;
    ui->curentTimeSlider->setValue(_currentTime * 1000);
}

void MainWindow::on_curentTimeSlider_sliderMoved(int position) {
    _currentTime = position / 1000.0f;
    ui->curentTime->setTime(
            QTime(int(_currentTime / 60), int(_currentTime) % 60)
    );

}

void MainWindow::on_playButton_clicked() {
    _is_played = !_is_played;
    renderCurrentTime();
}

void MainWindow::renderCurrentTime() {
    ui->playButton->setText(QString::fromStdString(
            std::string(!_is_played ? "▶" : "▌▌")
    ));
    ui->curentTimeSlider->setValue(_currentTime * 1000);
    ui->curentTime->setTime(
            QTime(int(_currentTime / 60), int(_currentTime) % 60)
    );
}
