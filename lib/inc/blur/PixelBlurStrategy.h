/**
 * Project Untitled
 */


#ifndef _PIXELBLURSTRATEGY_H
#define _PIXELBLURSTRATEGY_H

#include "IBlurStrategy.h"


class PixelBlurStrategy: public IBlurStrategy {
public:
    void apply(const BlurConfig &config) override;

    std::string getName() override;
};

#endif //_PIXELBLURSTRATEGY_H