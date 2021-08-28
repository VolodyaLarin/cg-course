/**
 * Project Untitled
 */


#include <CoordPtr.h>
#include "AnimatedCoordProperty.h"

std::shared_ptr<ICoord> AnimatedCoordProperty::get(Time t) const {
    if (t < _beginTime) return _beginValue->clone();
    if (t > _endTime) return _endValue->clone();

    auto b = CoordPtr(_beginValue), e = CoordPtr(_endValue);

    return b + (b - e) / (_beginTime - _endTime) * (t - _beginTime);
}

void AnimatedCoordProperty::setBegin(Time t, const ICoord &c) {
    _beginTime = t;
    _beginValue = c.clone();
}

void AnimatedCoordProperty::setEnd(Time t, const ICoord &c) {
    _endTime = t;
    _endValue = c.clone();
}

std::pair<Time, const ICoord &> AnimatedCoordProperty::getBegin() const {
    return {_beginTime, *_beginValue};
}

std::pair<Time, const ICoord &> AnimatedCoordProperty::getEnd() const {
    return {_endTime, *_endValue};
}
