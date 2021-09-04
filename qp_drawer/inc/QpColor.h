//
// Created by volodya on 02.09.2021.
//

#ifndef PROJECT_QPCOLOR_H
#define PROJECT_QPCOLOR_H

#include <QColor>
#include "utils/IColor.h"

class QpColor: public IColor {
private:
    QColor _color = QColor(0,0,0);
public:
    QpColor() = default;

    QpColor(float r, float g, float b, float a = 1) : _color(r * 255, g * 255, b * 255, a * 255) {}

    explicit QpColor(const QColor &color) : _color(color) {}

    float getR() const override {
        return _color.redF();
    }

    float getG() const override {
        return _color.greenF();
    }

    float getB() const override {
        return _color.blueF();
    }

    float getA() const override {
        return _color.alphaF();
    }

    void setR(float d) override {
        _color.setRedF(d);
    }

    void setG(float d) override {
        _color.setGreenF(d);
    }

    void setB(float d) override {
        _color.setBlueF(d);
    }

    void setA(float d) override {
        _color.setAlphaF(d);
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

    std::unique_ptr<IColor> clone() const override {
        return std::make_unique<QpColor>(_color);
    }
};


#endif //PROJECT_QPCOLOR_H
