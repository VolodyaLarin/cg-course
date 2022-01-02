/**
 * Project Untitled
 */


#ifndef _NEIBORBLURSTRATEGY_H
#define _NEIBORBLURSTRATEGY_H

#include "IBlurStrategy.h"


class NeiborBlurStrategy: public IBlurStrategy {
public:
    void apply(const BlurConfig &config) override;

    std::string getName() override;
};


#endif //_NEIBORBLURSTRATEGY_H