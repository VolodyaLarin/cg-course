#include "scene/SceneObjectType.h"

#include <utility>

std::string SceneObjectType::getName() {
    return _name;
}

SceneObjectType::SceneObjectType(std::string name) : _name(std::move(name)) {}
