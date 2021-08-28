#include "Scene.h"

Scene::iterator Scene::begin() {
    return _objects.begin();
}

Scene::iterator Scene::end() {
    return _objects.end();
}

Scene::const_iterator Scene::cbegin() const {
    return _objects.cbegin();
}

Scene::const_iterator Scene::cend() const {
    return _objects.cend();
}

void Scene::add(const Scene::ObjectPtr &object) {
    _objects.push_back(object);
}

void Scene::remove(const Scene::iterator &i) {
    _objects.erase(i);
}

Scene::const_iterator Scene::begin() const {
    return cbegin();
}

Scene::const_iterator Scene::end() const {
    return cend();
}
