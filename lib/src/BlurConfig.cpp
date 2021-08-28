/**
 * Project Untitled
 */


#include "BlurConfig.h"

int BlurConfig::getSamples() const {
    return _samples;
}

void BlurConfig::setSamples(int samples) {
    _samples = samples;
}

Time BlurConfig::getTime() const {
    return _time;
}

void BlurConfig::setTime(Time time) {
    _time = time;
}

Time BlurConfig::getExposition() const {
    return _exposition;
}

void BlurConfig::setExposition(Time exposition) {
    _exposition = exposition;
}

const std::shared_ptr<Camera> &BlurConfig::getCamera() const {
    return _camera;
}

void BlurConfig::setCamera(const std::shared_ptr<Camera> &camera) {
    _camera = camera;
}

const std::shared_ptr<RenderManager> &BlurConfig::getManager() const {
    return _manager;
}

void BlurConfig::setManager(const std::shared_ptr<RenderManager> &manager) {
    _manager = manager;
}

BlurConfig::BlurConfig(int samples, Time time, Time exposition, const std::shared_ptr<Camera> &camera,
                       const std::shared_ptr<RenderManager> &manager) : _samples(samples), _time(time),
                                                                        _exposition(exposition), _camera(camera),
                                                                        _manager(manager) {}

BlurConfig::BlurConfig() {}
