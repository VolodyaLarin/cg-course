//
// Created by volodya on 30.12.2021.
//

#include "Shaders.h"


void bindFrameBuffer(GLuint FB, int w, int h) {
    glBindFramebuffer(GL_FRAMEBUFFER, FB);
    glViewport(0, 0, w, h);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void attachTexture(GLuint destID, GLenum texture, GLuint texID) {
    glActiveTexture(texture);
    glBindTexture(GL_TEXTURE_2D, texID);
    glUniform1i(destID, int(texture - GL_TEXTURE0));
}


bool ReadFile(const char *pFileName, string &outFile) {
    ifstream f(pFileName);

    bool ret = false;

    if (f.is_open()) {
        string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        ret = true;
    } else {
        fprintf(stderr, "Error in loading file: '%s'\n", pFileName);
    }
    return ret;
}

void AddShader(GLuint pID, const char *srcCode, GLenum ShaderType) {
    GLuint ShaderObj = glCreateShader(ShaderType);
    if (ShaderObj == 0) {
        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
        exit(0);
    }

    const GLchar *p[1];
    p[0] = srcCode;
    GLint Lengths[1];
    Lengths[0] = strlen(srcCode);

    glShaderSource(ShaderObj, 1, p, Lengths);
    glCompileShader(ShaderObj);
    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success) {
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
        exit(1);
    }

    glAttachShader(pID, ShaderObj);
}

GLuint CompileShaders(const char *vsFileName, const char *fgFileName) {
    GLuint pID = glCreateProgram();
    if (pID == 0) {
        fprintf(stderr, "Error creating shader program\n");
        exit(1);
    }

    string vs, fs;
    GLint Success = 0;
    GLchar ErrorLog[1024] = {0};

    if (!ReadFile(vsFileName, vs)) { exit(1); }
    if (!ReadFile(fgFileName, fs)) { exit(1); }

    AddShader(pID, vs.c_str(), GL_VERTEX_SHADER);
    AddShader(pID, fs.c_str(), GL_FRAGMENT_SHADER);

    glLinkProgram(pID);
    glGetProgramiv(pID, GL_LINK_STATUS, &Success);

    if (Success == 0) {
        glGetProgramInfoLog(pID, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    glValidateProgram(pID);
    glGetProgramiv(pID, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(pID, sizeof(ErrorLog), NULL, ErrorLog);
        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
        exit(1);
    }

    return pID;
}
