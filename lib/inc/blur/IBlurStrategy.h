/**
 * Project Untitled
 */


#ifndef _IBLURSTRATEGY_H
#define _IBLURSTRATEGY_H

#include "BlurConfig.h"
#include <string>

class IBlurStrategy {
public:

    virtual void apply(const BlurConfig &) = 0;

    virtual std::string getName() = 0;
};

#endif //_IBLURSTRATEGY_H