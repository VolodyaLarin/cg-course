//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMCOORDFACTORY_H
#define PROJECT_GLMCOORDFACTORY_H

#include <utils/IFactory.h>
#include <GlmCoord.h>

class GlmCoordFactory: public IFactory<ICoord> {
    [[nodiscard]] ICoord::UPtr create() const override {
        return std::make_unique<GlmCoord>();
    }
};



#endif //PROJECT_GLMCOORDFACTORY_H
