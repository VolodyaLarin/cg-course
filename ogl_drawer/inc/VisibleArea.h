#pragma once

class ScreenArea {
public:
    GLuint Vertices = -1, numVertices = 0, numTriangles = 0;

    ScreenArea() {
        const GLfloat quadVertices[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                1.0f, 1.0f, 0.0f,
        };

        numVertices = sizeof(quadVertices) / sizeof(GLfloat);
        numTriangles = numVertices / 3;
        glGenBuffers(1, &Vertices);
        glBindBuffer(GL_ARRAY_BUFFER, Vertices);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), quadVertices, GL_STATIC_DRAW);
    }

    void draw() {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, Vertices);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);
        glDrawArrays(GL_TRIANGLES, 0, numTriangles);
        glDisableVertexAttribArray(0);
    }
};