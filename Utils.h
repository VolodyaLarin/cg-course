
#ifndef VERIFICATION_MODEL_UTILS_H
#define VERIFICATION_MODEL_UTILS_H

#include <sys/time.h>
#include "GlmCoord.h"
#include "utils/Time.h"
#include "scene/AnimatedCoordProperty.h"
#include "scene/ISceneObject.h"
#include "Buffers.h"

int mK = 20, mS = 40;
float fps = 0, cameraNear = 0.1f, cameraFar = 60.0f;
Time delta = 0;
Time now = 0;
Time exposition = 1;

std::shared_ptr<Buffers> buffers;
bool isPaused = true;

void zeroACP(AnimatedCoordProperty &ac, float value = 0) {
    ac.setBegin(0, GlmCoord(value, value, value));
    ac.setEnd(0, GlmCoord(value, value, value));
};

void zeroModel(ISceneObject &model) {
    zeroACP(model.position());
    zeroACP(model.size(), 1);
    zeroACP(model.rotation());
}





enum Display {
    MAIN = 0,
    COLOR = 1,
    DEPTH = 2,
    VELOCITY = 3,
    TILE_MAX = 4,
    NEIGHBOR_MAX = 5,
    PIXEL_BLUR = 6,
    DISPLAY_LENGTH = 7
} display = MAIN;

typedef long long LL;

void computeFPS() {
    static LL lastFrameTime = 0;
    static LL LastFrameTime = 0;
    static int frameCount = 0;

    frameCount++;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    LL currentTime = (LL) (tv.tv_sec) * 1000 + (LL) (tv.tv_usec) / 1000;

    delta = currentTime - LastFrameTime;
    LastFrameTime = currentTime;

    if (currentTime - lastFrameTime > 1000) {
        fps = frameCount * 1000.0 / (currentTime - lastFrameTime);
        lastFrameTime = currentTime;
        frameCount = 0;
    }
}



void timeFunc() {
    if (isPaused) return;
    now += delta / 1000;

    if (now > 120) {
        now = 120;
        isPaused = true;
    }

    glutPostRedisplay();

}



#endif //VERIFICATION_MODEL_UTILS_H
