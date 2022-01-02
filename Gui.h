//
// Created by volodya on 02.01.2022.
//

#ifndef PROJECT_GUI_H
#define PROJECT_GUI_H

#include "render/RenderManager.h"
#include "GlmCoordFactory.h"
#include "loaders/ObjModelLoader.h"
#include "imgui.h"
#include "imgui-filebrowser/imfilebrowser.h"

static ImGui::FileBrowser fileDialog(ImGuiFileBrowserFlags_NoModal);

static void initGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImFontConfig font_config;
    font_config.OversampleH = 1; //or 2 is the same
    font_config.OversampleV = 1;
    font_config.PixelSnapH = 1;

    static const ImWchar ranges[] =
            {
                    0x0020, 0x00FF, // Basic Latin + Latin Supplement
                    0x0400, 0x044F, // Cyrillic
                    0,
            };
    io.Fonts->AddFontFromFileTTF("fonts/Tahoma.ttf", 16.0f, &font_config, ranges);
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    auto &style = ImGui::GetStyle();
    style.FrameRounding = 10;
    style.WindowBorderSize = 0;
    style.FrameBorderSize = 1;
    ImGui::StyleColorsDark(&style);


    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();


    ImGui_ImplGLUT_InstallFuncs();
}

static void renderGui(RenderManager& renderManager) {
    auto viewport = ImGui::GetMainViewport();

    fileDialog.SetTitle("Выберите модель");
    fileDialog.SetTypeFilters({".obj"});
    fileDialog.SetWindowSize(viewport->Size.x, viewport->Size.y);

//    ImGui::ShowDemoWindow();
    auto &scene = renderManager.getScene();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
    ImGui::SetNextWindowBgAlpha(0.35f);

    ImGui::SetNextWindowPos({viewport->Size.x - 70, 0});
    ImGui::SetNextWindowSize({70, 30});

    ImGui::Begin("FPS", nullptr, window_flags);
    ImGui::Text("FPS: %.0f", fps);
    ImGui::End();

    fileDialog.Display();

    if (fileDialog.HasSelected()) {
        ObjModelLoader loader;
        auto filename = fileDialog.GetSelected().string();

        fileDialog.ClearSelected();


        Model::Ptr model = nullptr;

        try {
            model = loader.load(filename, GlmCoordFactory());

        } catch (std::exception &e) {
            return;
        }

        scene->add(model);
        model->setColor(OglColor(1, 0, 0));
        model->setName(std::filesystem::path(filename).filename());

        zeroModel(*model);
    }


    ImGui::SetNextWindowPos({0, 0});

    ImGui::SetNextWindowSize({500, viewport->Size.y});


    ImGui::Begin("Параметры", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNav);

    if (ImGui::Button("Загрузить модель")) {
        fileDialog.Open();
    }
    ImGui::SameLine();
    if (ImGui::Button("Добавить куб")) {
        ObjModelLoader loader;
        std::stringstream ss(
                "v 1.000000 1.000000 -1.000000\n"
                "v 1.000000 -1.000000 -1.000000\n"
                "v 1.000000 1.000000 1.000000\n"
                "v 1.000000 -1.000000 1.000000\n"
                "v -1.000000 1.000000 -1.000000\n"
                "v -1.000000 -1.000000 -1.000000\n"
                "v -1.000000 1.000000 1.000000\n"
                "v -1.000000 -1.000000 1.000000\n"
                "f 1/1/1 5/2/1 7/3/1 3/4/1\n"
                "f 4/5/2 3/4/2 7/6/2 8/7/2\n"
                "f 8/8/3 7/9/3 5/10/3 6/11/3\n"
                "f 6/12/4 2/13/4 4/5/4 8/14/4\n"
                "f 2/13/5 1/1/5 3/4/5 4/5/5\n"
                "f 6/11/6 5/10/6 1/1/6 2/13/6\n"
        );
        auto model = loader.loadStream(ss, GlmCoordFactory());
        zeroModel(*model);
        model->setColor(OglColor(0,1,0));
        model->setName("Куб");
        scene->add(std::move(model));
    }


    static const char *modes[] = {
            "Размытие по скорости сосед. пикселей",
            "Размытие по скорости пикселя",
            "Буфер кадра",
            "Буфер глубины",
            "Буфер скорости пикселей",
            "Буфер скорости плитки",
            "Буфер максимальной сосед. скорости плитки",
    };
    std::vector<std::pair<int, Display>> mapNameMode = {
            {0, MAIN},
            {1, PIXEL_BLUR},
            {2, COLOR},
            {3, DEPTH},
            {4, VELOCITY},
            {5, TILE_MAX},
            {6, NEIGHBOR_MAX},
    };

    int mode = std::find_if(mapNameMode.begin(), mapNameMode.end(), [](std::pair<int, Display> cur){
        return cur.second == display;
    })->first;

    ImGui::Combo("Режим", &mode, modes, 7, -1);

    display = mapNameMode[mode].second;

    if (ImGui::Button(isPaused ? "|>" : "| |")) {
        isPaused = !isPaused;
    }

    ImGui::SameLine();


    ImGui::DragFloat("Время", &now, 0.1f, 0.f, 120.f, "%.3f с");


    ImGui::DragFloat("Выдержка", &exposition, 0.05f, 0.f, 10.f, "%.3f с");

    ImGui::InputInt("Размер плитки", &mK, 1, 10);
    if (mK <= 1) {
        mK = 1;
    }
    ImGui::InputInt("Количество семплов", &mS);
    if (mS <= 1) {
        mS = 1;
    }

    ImGui::PushItemWidth(ImGui::GetFontSize() * -12);

    stringstream ss;
    int ll = scene->end() - scene->begin();
    ss << ll;
    ImGui::LabelText(ss.str().c_str(), "Объекты сцены:");


    int i = -1;
    for (auto &object: *scene) {
        i++;

        string id = object->getName() + "__" + char(i + 1);

        if (ImGui::CollapsingHeader((object->getName() + "##" + id).c_str())) {

            // COLOR
            auto &ocolor = object->getColor();
            float color[4] = {
                    ocolor.getR(),
                    ocolor.getG(),
                    ocolor.getB(),
                    1
            };

            ImGui::ColorEdit4((string("Цвет##") + char(i)).c_str(), color);

            object->setColor(OglColor(color[0], color[1], color[2], 1));

            auto drawParams = [](const string &id, AnimatedCoordProperty &prop) {

                auto beg = prop.getBegin();
                auto end = prop.getEnd();

                float X[2] = {beg.second->getX(), end.second->getX()};
                float Y[2] = {beg.second->getY(), end.second->getY()};
                float Z[2] = {beg.second->getZ(), end.second->getZ()};

                float beginTime = beg.first;
                float endTime = end.first;

                ImGui::DragFloatRange2(("Время##" + id).c_str(), &beginTime, &endTime, 0.1, 0.0, 120.0, "%.3f с");
                ImGui::DragFloat2(("x##" + id).c_str(), X, 0.1);
                ImGui::DragFloat2(("y##" + id).c_str(), Y, 0.1);
                ImGui::DragFloat2(("z##" + id).c_str(), Z, 0.1);


                if (beginTime == endTime) {
                    X[0] = X[1] = (X[0] + X[1]) / 2;
                    Y[0] = Y[1] = (Y[0] + Y[1]) / 2;
                    Z[0] = Z[1] = (Z[0] + Z[1]) / 2;

                }

                beg.second->setX(X[0]);
                beg.second->setY(Y[0]);
                beg.second->setZ(Z[0]);


                end.second->setX(X[1]);
                end.second->setY(Y[1]);
                end.second->setZ(Z[1]);

                prop.setBegin(beginTime, *beg.second);
                prop.setEnd(endTime, *end.second);

            };

            ImGui::Text("Позиция");
            drawParams(id + "_position", object->position());
            ImGui::Text("Размер");
            drawParams(id + "_size", object->size());
            ImGui::Text("Поворот");
            drawParams(id + "_rotation", object->rotation());

            if (i != 0 && ImGui::Button(("Удалить объект##" + id).c_str())) {
                scene->remove(scene->begin() + i);
            }
        }
    }

    if (scene->begin() == scene->end()) {
        ImGui::Text("Сцена пуста");
    }


    ImGui::End();

    ImGui::Render();

    ImGuiIO &io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei) io.DisplaySize.x, (GLsizei) io.DisplaySize.y);

    glUseProgram(0);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::EndFrame();
}

#endif //PROJECT_GUI_H
