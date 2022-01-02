#pragma once

#include <bits/stdc++.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "VisibleArea.h"


static std::shared_ptr<ScreenArea> screenArea;

using namespace std;


bool ReadFile(const char *pFileName, string &outFile);

void AddShader(GLuint pID, const char *srcCode, GLenum ShaderType);

GLuint CompileShaders(const char *vsFileName, const char *fgFileName);

void bindFrameBuffer(GLuint FB, int w, int h);

void attachTexture(GLuint destID, GLenum texture, GLuint texID);

class ShaderProgram {
public:

    virtual void Enable() {
        glUseProgram(pID);
    }

    virtual void Disable() {
        glUseProgram(0);
    }

    virtual void init(GLuint buffer, int WIDTH, int HEIGHT) = 0;

protected:
    GLuint pID = -1;

    void load(const char *vsFileName, const char *fgFileName) {
        pID = CompileShaders(vsFileName, fgFileName);
    }

};


class CZShader : public ShaderProgram {
public:
    GLuint MVP = -1, Model = -1, View = -1, Color = -1;

    CZShader() {
        load("shaders/colorDepth.vs.glsl", "shaders/colorDepth.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        Model = glGetUniformLocation(pID, "M");
        View = glGetUniformLocation(pID, "V");
        MVP = glGetUniformLocation(pID, "MVP");
        Color = glGetUniformLocation(pID, "Color");
    }
};

class VLShader : public ShaderProgram {
public:
    GLuint currMVP = -1, prevMVP = -1, proj = -1;

    VLShader() {
        load("shaders/velocity.vs.glsl", "shaders/velocity.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        currMVP = glGetUniformLocation(pID, "currMVP");
        prevMVP = glGetUniformLocation(pID, "prevMVP");
        proj = glGetUniformLocation(pID, "proj");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void Disable() override {
        glDisable(GL_BLEND);
        ShaderProgram::Disable();
    }
};

class TMShader : public ShaderProgram {
public:
    GLuint K = -1, TEX = -1, Pos = -1;

    TMShader() {
        load("shaders/base.vs.glsl", "shaders/tileMax.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        K = glGetUniformLocation(pID, "K");
        TEX = glGetUniformLocation(pID, "TEX_VL");
        Pos = glGetAttribLocation(pID, "position");
    }

    void apply(int mK, GLuint TEXTURE_VL) {
        glUniform1i(K, mK);

        attachTexture(TEX, GL_TEXTURE0, TEXTURE_VL);

        screenArea->draw();

    }
};

class NMShader : public ShaderProgram {
public:
    GLuint Pos = -1, TEX = -1;

    NMShader() {
        load("shaders/base.vs.glsl", "shaders/neighborMax.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        TEX = glGetUniformLocation(pID, "TEX_TM");
        Pos = glGetAttribLocation(pID, "position");
    }

    void apply(GLuint TEX_TM) {
        attachTexture(TEX, GL_TEXTURE0, TEX_TM);
        screenArea->draw();
    }
};


class VWShader : public ShaderProgram {
public:
    GLuint Pos = -1, Tex = -1, TexType = -1, K = -1, cameraFar = -1, cameraNear = -1;

    VWShader() {
        load("shaders/viewer.vs.glsl", "shaders/viewer.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        Pos = glGetAttribLocation(pID, "position");
        Tex = glGetUniformLocation(pID, "renderedTex");
        K = glGetUniformLocation(pID, "mK");
        TexType = glGetUniformLocation(pID, "texType");
        cameraNear = glGetUniformLocation(pID, "cameraNear");
        cameraFar = glGetUniformLocation(pID, "cameraFar");
    }

    void apply(GLuint toBind, int mK, float IcameraNear, float IcameraFar, int displayMode) {

        attachTexture(Tex, GL_TEXTURE0, toBind);

        glUniform1i(TexType, int(displayMode));
        glUniform1f(cameraFar, IcameraFar);
        glUniform1f(cameraNear, IcameraNear);
        glUniform1i(K, mK);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        screenArea->draw();
        glDisable(GL_BLEND);
    }
};

class GAShader : public ShaderProgram {
public:
    GLuint TEX_C = -1, TEX_VL = -1, TEX_Z = -1, TEX_NM = -1, K = -1, S = -1, cameraNear = -1, cameraFar = -1;

    GAShader() {
        load("shaders/base.vs.glsl", "shaders/gatherAll.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        TEX_C = glGetUniformLocation(pID, "TEX_C");
        TEX_VL = glGetUniformLocation(pID, "TEX_VL");
        TEX_Z = glGetUniformLocation(pID, "TEX_Z");
        TEX_NM = glGetUniformLocation(pID, "TEX_NM");
        K = glGetUniformLocation(pID, "K");
        S = glGetUniformLocation(pID, "S");
        cameraNear = glGetUniformLocation(pID, "cameraNear");
        cameraFar = glGetUniformLocation(pID, "cameraFar");
    }

    void apply(int mS, int mK, GLuint ITEX_C, GLuint ITEX_Z, GLuint ITEX_VL, GLuint ITEX_NM) {

        attachTexture(TEX_C, GL_TEXTURE0, ITEX_C);
        attachTexture(TEX_Z, GL_TEXTURE1, ITEX_Z);
        attachTexture(TEX_VL, GL_TEXTURE2, ITEX_VL);
        attachTexture(TEX_NM, GL_TEXTURE3, ITEX_NM);
        glUniform1i(S, mS);
        glUniform1i(K, mK);

        screenArea->draw();
    }
};


class PixelBlurShader : public ShaderProgram {
public:
    GLuint TEX_C = -1, TEX_VL = -1, S = -1;

    PixelBlurShader() {
        load("shaders/base.vs.glsl", "shaders/pixelBlur.fs.glsl");
    }

    void init(GLuint buffer, int WIDTH, int HEIGHT) override {
        bindFrameBuffer(buffer, WIDTH, HEIGHT);

        this->Enable();
        TEX_C = glGetUniformLocation(pID, "TEX_C");
        TEX_VL = glGetUniformLocation(pID, "TEX_VL");
        S = glGetUniformLocation(pID, "S");
    }

    void apply(int mS, GLuint ITEX_C, GLuint ITEX_VL) {
        attachTexture(TEX_C, GL_TEXTURE0, ITEX_C);
        attachTexture(TEX_VL, GL_TEXTURE1, ITEX_VL);
        glUniform1i(S, mS);

        screenArea->draw();
    }
};


class Shaders {
public:
    std::shared_ptr<CZShader> CZ = make_shared<CZShader>();
    std::shared_ptr<VLShader> VL = make_shared<VLShader>();
    std::shared_ptr<TMShader> TM = make_shared<TMShader>();
    std::shared_ptr<NMShader> NM = make_shared<NMShader>();
    std::shared_ptr<GAShader> GA = make_shared<GAShader>();
    std::shared_ptr<VWShader> View = make_shared<VWShader>();
    std::shared_ptr<PixelBlurShader> PixelBlur = make_shared<PixelBlurShader>();

    Shaders() {
        if (screenArea == nullptr) {
            screenArea = make_shared<ScreenArea>();
        }
    }
};