/**
 * Project Untitled
 */


#ifndef _ITRANSFORMATION_H
#define _ITRANSFORMATION_H

#include <memory>

#include "utils/ICoord.h"

class ITransformationFactory;

class ITransformation {
public:
    using Ptr = std::shared_ptr<ITransformation>;

    virtual std::unique_ptr<ICoord> apply(const ICoord &) = 0;

    virtual ITransformation &join(const ITransformation &) = 0;

    [[nodiscard]] virtual std::unique_ptr<ITransformation> clone() const = 0;

    virtual std::shared_ptr<ITransformationFactory> getFactory() = 0;

};

#endif //_ITRANSFORMATION_H