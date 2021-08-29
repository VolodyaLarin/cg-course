/**
 * Project Untitled
 */


#ifndef _ANIMATEDCOORDPROPERTY_H
#define _ANIMATEDCOORDPROPERTY_H

#include "utils/ICoord.h"
#include "utils/Time.h"

class AnimatedCoordProperty {
public: 
    
[[nodiscard]] std::shared_ptr<ICoord> get(Time t) const ;
void setBegin(Time, const ICoord&);
void setEnd(Time, const ICoord&);
    
[[nodiscard]] std::pair<Time, const ICoord &> getBegin() const ;
    
[[nodiscard]] std::pair<Time, const ICoord &> getEnd() const ;

private: 
    Time _beginTime;
    ICoord::UPtr _beginValue;
    Time _endTime;
    ICoord::UPtr _endValue;
};

#endif //_ANIMATEDCOORDPROPERTY_H