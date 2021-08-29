//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_OGLCOLOR_H
#define PROJECT_OGLCOLOR_H


#include "utils/IColor.h"

class OglColor: public IColor{
private:
    float _r = 0,_g = 0,_b = 0, _a = 1;
public:
    OglColor() = default;
    OglColor(float r, float g, float b) : _r(r), _g(g), _b(b) {}
    OglColor(float r, float g, float b, float a) : _r(r), _g(g), _b(b), _a(a) {}

    float getR() const override {
        return _r;
    }

    float getG() const override {
        return _g;
    }

    float getB() const override {
        return _b;
    }

    float getA() const override {
        return _a;
    }

    void setR(float d) override {
        _r = d;
    }

    void setG(float d) override {
        _g = d;
    }

    void setB(float d) override {
        _b = d;
    }

    void setA(float d) override {
        _a = d;
    }

    [[nodiscard]] std::unique_ptr<IColor> clone() const override {
        return std::make_unique<OglColor>(*this);
    }
};
#endif //PROJECT_OGLCOLOR_H
