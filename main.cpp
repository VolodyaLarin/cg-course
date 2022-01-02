#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Utils.h"
#include "Shaders.h"
#include "Buffers.h"

#include "imgui.h"
#include "backends/imgui_impl_glut.h"
#include "backends/imgui_impl_opengl3.h"


#include "scene/Scene.h"

using namespace glm;


#include "OglColor.h"
#include "RenderVisitor.h"
#include "GlmTransformationFactory.h"
#include "render/RenderManager.h"
#include "Gui.h"

RenderManager renderManager;

std::shared_ptr<Shaders> shaders = nullptr;
std::shared_ptr<Scene> scene = nullptr;


static void renderBuffers() {

    int &WIDTH = buffers->WIDTH;
    int &HEIGHT = buffers->HEIGHT;

    const auto &drawer = renderManager.getDrawer();
    auto context = make_shared<RenderContext>();
    context->time = now;
    context->exposition = exposition;
    auto oglDrawer = dynamic_pointer_cast<OglDrawer>(drawer);

    drawer->setRenderContext(context);
    RenderVisitor visitor(oglDrawer);
    visitor.setTransformationFactory(make_shared<GlmTransformationFactory>());
    visitor.setShaders(shaders);

    drawer->setCameraTransformation(*renderManager.getCamera()->getTransformation(context->time));


    /****************Constructing Objects***************/
    shaders->CZ->init(buffers->FBO_CZ, WIDTH, HEIGHT);
    for (auto &object: *scene) {
        object->accept(visitor);
    }
    shaders->CZ->Disable();

    /****************Velocity Calculation***************/
    shaders->VL->init(buffers->FBO_VL, WIDTH, HEIGHT);
    visitor.setSendPosition(true);
    for (auto &object: *scene) {
        object->accept(visitor);
    }
    shaders->VL->Disable();

    /*********************Tile Max**********************/
    shaders->TM->init(buffers->FBO_TM, WIDTH / mK, HEIGHT / mK);
    shaders->TM->apply(mK, buffers->TEX_VL);
    shaders->TM->Disable();

    /*********************Neighbor Max**********************/
    shaders->NM->init(buffers->FBO_NM, WIDTH / mK, HEIGHT / mK);
    shaders->NM->apply(buffers->TEX_TM);
    shaders->NM->Disable();

    /*********************Gather All**********************/
    shaders->GA->init(buffers->FBO_GA, WIDTH, HEIGHT);
    shaders->GA->apply(
            mS, mK,
            buffers->TEX_C, buffers->TEX_Z,
            buffers->TEX_VL, buffers->TEX_NM
    );
    shaders->GA->Disable();


    /*********************Pixel Blur**********************/
    shaders->PixelBlur->init(buffers->FBO_PixelBlur, WIDTH, HEIGHT);
    shaders->PixelBlur->apply(mS, buffers->TEX_C, buffers->TEX_VL);
    shaders->PixelBlur->Disable();
}

void ViewTextures() {
    shaders->View->init(0, buffers->WIDTH, buffers->HEIGHT);

    GLuint toBind = 0;
    switch (display) {
        case COLOR:
            toBind = buffers->TEX_C;
            break;
        case DEPTH:
            toBind = buffers->TEX_Z;
            break;
        case VELOCITY:
            toBind = buffers->TEX_VL;
            break;
        case TILE_MAX:
            toBind = buffers->TEX_TM;
            break;
        case NEIGHBOR_MAX:
            toBind = buffers->TEX_NM;
            break;
        case MAIN:
            toBind = buffers->TEX_GA;
            break;
        case PIXEL_BLUR:
            toBind = buffers->TEX_PixelBlur;
            break;
        case DISPLAY_LENGTH:
            break;
    }

    shaders->View->apply(toBind, mK, cameraNear, cameraFar, int(display));

    shaders->View->Disable();

}

void renderScene() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    computeFPS();
    renderBuffers();
    ViewTextures();

    renderGui(renderManager);

    glutSwapBuffers();
    glutPostRedisplay();
}


void InitCallbacks() {
    glutDisplayFunc(renderScene);
    glutIdleFunc(timeFunc);
}


void init(int w, int h) {
    buffers = std::make_shared<Buffers>(w, h, mK);
    shaders = std::make_shared<Shaders>();


    scene = std::make_shared<Scene>();
    renderManager.setScene(scene);

    {
        auto drawer = std::make_unique<OglDrawer>();
        drawer->setShaders(shaders);
        renderManager.setDrawer(std::move(drawer));
    }


    auto camera = std::make_shared<Camera>();
    camera->setName("Камера");
    camera->setTransformationFactory(std::make_shared<GlmTransformationFactory>());
    camera->setColor(OglColor(0, 0, 0, 1));
    zeroModel(*camera);
    auto x = camera->position().getBegin();
    x.second->setZ(10);
    camera->position().setEnd(0, *x.second);
    camera->position().setBegin(0, *x.second);

    renderManager.setCamera(camera);
    scene->add(camera);
}


int main(int argc, char **argv) {
    const int WIDTH = 1000, HEIGHT = 800;

    glutInit(&argc, argv);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("Course work - motion blur");

    InitCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK) {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    init(WIDTH, HEIGHT);

    initGui();

    glutReshapeFunc([](int w, int h) {
        buffers->setSize(w, h);
        renderManager.getDrawer()->resize(w, h);
        ImGui_ImplGLUT_ReshapeFunc(w, h);
    });

    ImGui_ImplOpenGL3_Init();


    glEnable(GL_DEPTH_TEST);


    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();


    return 0;
}