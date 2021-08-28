//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_COORDPTR_H
#define PROJECT_COORDPTR_H

#include <utility>

#include "ICoord.h"
class CoordPtr {
private:
    ICoord::Ptr _ptr;
public:
    explicit CoordPtr(ICoord::Ptr ptr):_ptr(std::move(ptr)) {};
    explicit CoordPtr(const ICoord::UPtr& ptr):_ptr(ptr->clone()) {};
    explicit CoordPtr(ICoord::UPtr&& ptr):_ptr(std::move(ptr)) {};

    CoordPtr(const CoordPtr &) = delete;

    [[nodiscard]] const ICoord::Ptr &getPtr() const {
        return _ptr;
    }

    CoordPtr& operator+=(const CoordPtr& coord) {
        _ptr->add(*coord.getPtr());
        return *this;
    };
    CoordPtr& operator-=(const CoordPtr& coord){
        _ptr->sub(*coord.getPtr());
        return *this;
    };

    CoordPtr operator+(const CoordPtr& coord) {
        return CoordPtr(_ptr->sum(*coord.getPtr()));
    };
    CoordPtr operator-(const CoordPtr& coord) {
        return CoordPtr(_ptr->diff(*coord.getPtr()));
    }

    CoordPtr operator-() {
        return CoordPtr(_ptr->invert());
    }

    CoordPtr operator*(ICoord::type val) {

        return CoordPtr(_ptr->mul(val));
    }

    CoordPtr& operator*=(ICoord::type val) {
        _ptr->mulled(val);
        return *this;
    }

    CoordPtr operator/(ICoord::type val) {

        return CoordPtr(_ptr->mul(1/val));
    }

    CoordPtr& operator/=(ICoord::type val) {
        _ptr->mulled(1/val);
        return *this;
    }

    operator ICoord::Ptr() {
        return _ptr;
    }
    operator ICoord::UPtr() {
        return _ptr->clone();
    }

};
#endif //PROJECT_COORDPTR_H
