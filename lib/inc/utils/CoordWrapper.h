//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_COORDWRAPPER_H
#define PROJECT_COORDWRAPPER_H

#include <utility>

#include "utils/ICoord.h"
class CoordWrapper {
private:
    ICoord::Ptr _ptr;
public:
    explicit CoordWrapper(ICoord::Ptr ptr):_ptr(std::move(ptr)) {};
    explicit CoordWrapper(const ICoord::UPtr& ptr):_ptr(ptr->clone()) {};
    explicit CoordWrapper(ICoord::UPtr&& ptr):_ptr(std::move(ptr)) {};

    CoordWrapper(const CoordWrapper &) = delete;

    [[nodiscard]] const ICoord::Ptr &getPtr() const {
        return _ptr;
    }

    CoordWrapper& operator+=(const CoordWrapper& coord) {
        _ptr->add(*coord.getPtr());
        return *this;
    };
    CoordWrapper& operator-=(const CoordWrapper& coord){
        _ptr->sub(*coord.getPtr());
        return *this;
    };

    CoordWrapper operator+(const CoordWrapper& coord) {
        return CoordWrapper(_ptr->sum(*coord.getPtr()));
    };
    CoordWrapper operator-(const CoordWrapper& coord) {
        return CoordWrapper(_ptr->diff(*coord.getPtr()));
    }

    CoordWrapper operator-() {
        return CoordWrapper(_ptr->invert());
    }

    CoordWrapper operator*(ICoord::type val) {

        return CoordWrapper(_ptr->mul(val));
    }

    CoordWrapper& operator*=(ICoord::type val) {
        _ptr->mulled(val);
        return *this;
    }

    CoordWrapper operator/(ICoord::type val) {

        return CoordWrapper(_ptr->mul(1/val));
    }

    CoordWrapper& operator/=(ICoord::type val) {
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
#endif //PROJECT_COORDWRAPPER_H
