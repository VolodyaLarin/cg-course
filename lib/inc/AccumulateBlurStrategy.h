/**
 * Project Untitled
 */


#ifndef _ACCUMULATEBLURSTRATEGY_H
#define _ACCUMULATEBLURSTRATEGY_H

#include "IBlurStrategy.h"


class AccumulateBlurStrategy: public IBlurStrategy {
public: 

void apply(const BlurConfig &) override;
    
std::string getName() override;
};

#endif //_ACCUMULATEBLURSTRATEGY_H