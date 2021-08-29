//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMCOORD_H
#define PROJECT_GLMCOORD_H

#include <utils/ICoord.h>
#include <glm/glm.hpp>

class GlmCoord: public ICoord {
public:
    glm::vec4 vec = {0,0,0,1};

public:
    explicit GlmCoord() = default;
    GlmCoord(float x, float y, float z): vec(x,y,z,1) {};
    explicit GlmCoord(const glm::vec4 &vec);
    explicit GlmCoord(const ICoord&);


    [[nodiscard]] type getX() const override;

    [[nodiscard]] type getY() const override;

    [[nodiscard]] type getZ() const override;

    void setX(type type) override;

    void setY(type type) override;

    void setZ(type type) override;

    [[nodiscard]] UPtr sum(const ICoord &coord) const override;

    void add(const ICoord &coord) override;

    [[nodiscard]] UPtr diff(const ICoord &coord) const override;

    void sub(const ICoord &coord) override;

    [[nodiscard]] UPtr clone() const override;

    [[nodiscard]] UPtr invert() const override;

    [[nodiscard]] UPtr mul(type type) const override;

    void mulled(type type) override;
};


#endif //PROJECT_GLMCOORD_H
