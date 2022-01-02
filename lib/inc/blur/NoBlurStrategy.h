/**
 * Project Untitled
 */


#ifndef _NOBLURSTRATEGY_H
#define _NOBLURSTRATEGY_H

#include "IBlurStrategy.h"


class NoBlurStrategy: public IBlurStrategy {
public:
    void apply(const BlurConfig &config) override;

    std::string getName() override;
};

#endif //_NOBLURSTRATEGY_H