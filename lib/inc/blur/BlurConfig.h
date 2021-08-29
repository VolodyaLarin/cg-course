/**
 * Project Untitled
 */


#ifndef _BLURCONFIG_H
#define _BLURCONFIG_H

#include <memory>
#include "scene/Camera.h"
#include "render/RenderManager.h"
#include "utils/Time.h"

class BlurConfig {
private:
    int _samples = 0;
    Time _time = 0;
    Time _exposition = 0;
    std::shared_ptr<Camera> _camera = nullptr;
    std::shared_ptr<RenderManager> _manager = nullptr;
public:
    BlurConfig();

    BlurConfig(int samples, Time time, Time exposition, const std::shared_ptr<Camera> &camera,
               const std::shared_ptr<RenderManager> &manager);

    [[nodiscard]] int getSamples() const;

    void setSamples(int samples);

    [[nodiscard]] Time getTime() const;

    void setTime(Time time);

    [[nodiscard]] Time getExposition() const;

    void setExposition(Time exposition);

    [[nodiscard]] const std::shared_ptr<Camera> &getCamera() const;

    void setCamera(const std::shared_ptr<Camera> &camera);

    [[nodiscard]] const std::shared_ptr<RenderManager> &getManager() const;

    void setManager(const std::shared_ptr<RenderManager> &manager);
};

#endif //_BLURCONFIG_H