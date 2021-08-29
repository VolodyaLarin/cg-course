//
// Created by volodya on 29.08.2021.
//

#include <GlmException.h>
#include <GlmTransformationFactory.h>
#include "GlmTransformation.h"
#include "GlmCoord.h"

std::unique_ptr<ICoord> GlmTransformation::apply(const ICoord &coord) {
    auto res = matrix * GlmCoord(coord).vec;
    return std::make_unique<GlmCoord>(res);
}

ITransformation &GlmTransformation::join(const ITransformation &transformation) {
    try {
        auto &glmTransf = dynamic_cast<const GlmTransformation &>(transformation);

        matrix = glmTransf.matrix * matrix;
    }
    catch (std::bad_cast &err) {
        throw GlmException("GlmTransformation can works only with GlmTransformation classes");
    }

    return *this;
}

std::unique_ptr<ITransformation> GlmTransformation::clone() const {
    return std::make_unique<GlmTransformation>(matrix);
}

std::shared_ptr<ITransformationFactory> GlmTransformation::getFactory() {
    return std::make_shared<GlmTransformationFactory>();
}

GlmTransformation::GlmTransformation(const glm::mat4x4 &matrix) : matrix(matrix) {}
