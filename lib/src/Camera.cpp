#include "Camera.h"

ITransformation::Ptr Camera::getTransformation(Time) {
    return nullptr;
}

ITransformation::Ptr Camera::getInvTransformation(Time) {
    return nullptr;
}
