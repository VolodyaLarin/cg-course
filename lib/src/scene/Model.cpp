#include "scene/Model.h"

#include <utility>

Model::iterator Model::begin() {
    return _polygons.begin();
}

Model::iterator Model::end() {
    return _polygons.end();
}

Model::const_iterator Model::begin() const {
    return cbegin();
}

Model::const_iterator Model::end() const {
    return cend();
}

Model::const_iterator Model::cbegin() const {
    return _polygons.cbegin();
}

Model::const_iterator Model::cend() const {
    return _polygons.cend();
}

SceneObjectType Model::getType() const {
    return SceneObjectType("Model");
}

void Model::accept(IVisitor &visitor) {
    visitor.visitModel(*this);
}

Model::Model(std::vector<Polygon>&& polygons) : _polygons(std::move(polygons)) {}
