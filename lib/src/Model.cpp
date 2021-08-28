#include "Model.h"

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
