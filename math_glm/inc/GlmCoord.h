//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMCOORD_H
#define PROJECT_GLMCOORD_H

#include <utils/ICoord.h>
#include <glm/glm.hpp>

class GlmCoord: public ICoord {
public:
    glm::vec4 vec;

public:
    GlmCoord(const glm::vec4 &vec);
    GlmCoord(const ICoord&);

    type getX() const override;

    type getY() const override;

    type getZ() const override;

    void setX(type type) override;

    void setY(type type) override;

    void setZ(type type) override;

    UPtr sum(const ICoord &coord) const override;

    void add(const ICoord &coord) override;

    UPtr diff(const ICoord &coord) const override;

    void sub(const ICoord &coord) override;

    UPtr clone() const override;

    UPtr invert() const override;

    UPtr mul(type type) const override;

    void mulled(type type) override;
};


#endif //PROJECT_GLMCOORD_H
