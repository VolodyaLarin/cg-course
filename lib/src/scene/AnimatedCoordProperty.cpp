/**
 * Project Untitled
 */


#include <utils/CoordWrapper.h>
#include "scene/AnimatedCoordProperty.h"

std::shared_ptr<ICoord> AnimatedCoordProperty::get(Time t) const {
    if (t <= _beginTime) return _beginValue->clone();
    if (t >= _endTime) return _endValue->clone();

    auto test = _beginValue->diff(*_endValue);

    auto b = CoordWrapper(_beginValue), e = CoordWrapper(_endValue);

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

std::pair<Time, const ICoord::UPtr &> AnimatedCoordProperty::getBegin() const {
    return {_beginTime, _beginValue};
}

std::pair<Time, const ICoord::UPtr &> AnimatedCoordProperty::getEnd() const {
    return {_endTime, _endValue};
}
