//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMTRANSFORMATIONFACTORY_H
#define PROJECT_GLMTRANSFORMATIONFACTORY_H

#include <utils/ITransformationFactory.h>

class GlmTransformationFactory: public ITransformationFactory  {
    std::unique_ptr<ITransformation> createPosition(const ICoord &coord) override;

    std::unique_ptr<ITransformation> createRotation(const ICoord &coord) override;

    std::unique_ptr<ITransformation> createScale(const ICoord &coord) override;

    std::unique_ptr<ITransformation> createPerspective(ICoord::type type) override;

    std::unique_ptr<ITransformation> create() override;
};


#endif //PROJECT_GLMTRANSFORMATIONFACTORY_H
