//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_OGLCOLOR_H
#define PROJECT_OGLCOLOR_H


#include <iomanip>
#include "utils/IColor.h"

class OglColor : public IColor {
private:
    float _r = 0, _g = 0, _b = 0, _a = 1;
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

    [[nodiscard]] std::string getHEX() const override {
        std::stringstream stream("");

        stream << std::hex;

        int r = getR() * 255, g = getG() * 255, b = getB() * 255, a = getA() * 255;

        auto printN = [](std::stringstream &stream, int N) {
            if (N < 16) stream << 0;
            stream << N;
        };

        printN(stream, r);
        printN(stream, g);
        printN(stream, b);
        printN(stream, a);

        auto hex = stream.str();
        return hex;
    }

    void setHEX(const std::string &string) override {

        auto readN = [](const std::string &str, int pos) -> int {
            if (pos + 1 >= str.size()) return 0;

            std::stringstream stream("");
            stream << std::setfill('0') << std::hex;
            for (int i = pos; i != pos + 2; ++i) {
                stream << str[i];
            }
            int n;
            stream >> n;
            return n;
        };

        setR(readN(string, 0) / 255.0f);
        setG(readN(string, 2) / 255.0f);
        setB(readN(string, 4) / 255.0f);
        setA(readN(string, 6) / 255.0f);
    }
};

#endif //PROJECT_OGLCOLOR_H
