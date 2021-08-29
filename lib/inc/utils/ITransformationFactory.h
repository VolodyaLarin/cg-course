/**
 * Project Untitled
 */


#ifndef _ITRANSFORMATIONFACTORY_H
#define _ITRANSFORMATIONFACTORY_H

#include "IFactory.h"
#include "utils/ICoord.h"
#include "ITransformation.h"


class ITransformationFactory: public IFactory<ITransformation> {
public:
    virtual std::unique_ptr<ITransformation> createPosition(const ICoord&) = 0;

    virtual std::unique_ptr<ITransformation> createRotation(const ICoord&) = 0;

    virtual std::unique_ptr<ITransformation> createScale(const ICoord&) = 0;

    virtual std::unique_ptr<ITransformation> createPerspective(ICoord::type)= 0;

    std::unique_ptr<ITransformation> create() override = 0;
};

#endif //_ITRANSFORMATIONFACTORY_H