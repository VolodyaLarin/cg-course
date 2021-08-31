//
// Created by volodya on 29.08.2021.
//

#include "GlmCoord.h"

ICoord::type GlmCoord::getX() const {
    return vec.x;
}

ICoord::type GlmCoord::getY() const {
    return vec.y;
}

ICoord::type GlmCoord::getZ() const {
    return vec.z;
}

void GlmCoord::setX(ICoord::type type) {
    vec.x = type;
}

void GlmCoord::setY(ICoord::type type) {
    vec.y = type;
}

void GlmCoord::setZ(ICoord::type type) {
    vec.z = type;
}

ICoord::UPtr GlmCoord::sum(const ICoord &coord) const {
    return std::make_unique<GlmCoord>(vec + GlmCoord(coord).vec);
}

void GlmCoord::add(const ICoord &coord) {
    vec += GlmCoord(coord).vec;
}

ICoord::UPtr GlmCoord::diff(const ICoord &coord) const {
    auto rght = GlmCoord(coord).vec;
    auto res = vec - rght;
    return std::make_unique<GlmCoord>(res);
}

void GlmCoord::sub(const ICoord &coord) {
    vec -= GlmCoord(coord).vec;
}

ICoord::UPtr GlmCoord::clone() const {
    return std::make_unique<GlmCoord>(*this);
}

ICoord::UPtr GlmCoord::invert() const {
    return std::make_unique<GlmCoord>(-vec);
}

ICoord::UPtr GlmCoord::mul(ICoord::type type) const {
    return std::make_unique<GlmCoord>(vec * type);
}

void GlmCoord::mulled(ICoord::type type) {
    vec *= type;
}

GlmCoord::GlmCoord(const glm::vec4 &vec) : vec(vec) {}

GlmCoord::GlmCoord(const ICoord & coord) {
    vec.x = coord.getX();
    vec.y = coord.getY();
    vec.z = coord.getZ();
    vec.w = 1;
}

ICoord::type GlmCoord::scalarProduct(const ICoord &coord) const {
    return vec.x * coord.getX() + vec.z * coord.getZ() +vec.y * coord.getY();
}

ICoord::UPtr GlmCoord::vectorProduct(const ICoord &coord) const {
    ICoord::type
            x = getY() * coord.getZ() - getZ() * coord.getY(),
            y = getZ() * coord.getX() - getX() * coord.getZ(),
            z = getX() * coord.getY() - getY() * coord.getX();

    return std::make_unique<GlmCoord>(x,y,z);
}

ICoord::type GlmCoord::length() const {
    return std::hypot(vec.x, vec.y, vec.z);
}

void GlmCoord::normalize() {
    vec /= length();
}

ICoord::UPtr GlmCoord::normalized() const {
    return std::make_unique<GlmCoord>(vec / length());
}
