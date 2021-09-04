//
// Created by volodya on 02.09.2021.
//

#ifndef PROJECT_MATRIXBUFFER_H
#define PROJECT_MATRIXBUFFER_H

#include "utils/IBuffer.h"

template <class T>
class MatrixBuffer: public IBuffer<T> {
private:
    T zero;
    std::vector<T> _buffer = {};
    int _width = 0, _height = 0;
public:
    MatrixBuffer(int width, int height, T zero = {}): zero(std::move(zero)) {
        resize(width, height);
    }
    void set(int i, int ii, const T &t) override {
        if (i < 0 || i >= _width) return;
        if (ii < 0 || ii >= _height) return;

        _buffer[ii * _width + i] = t;
    }

    const T& get(int i, int ii) override {
        if (i < 0 || i >= _width) return zero;
        if (ii < 0 || ii >= _height) return zero;

        return _buffer[ii * _width + i];
    }

    int getWidth() override {
        return _width;
    }

    int getHeight() override {
        return _height;
    }

    void resize(int width, int height) override {
        _width = width;
        _height = height;
        _buffer.resize(_width * _height);
    }

    void clear() override {
        std::fill(_buffer.begin(), _buffer.end(), zero);
    }
};

typedef MatrixBuffer<float> ZBuffer;

#endif //PROJECT_MATRIXBUFFER_H
