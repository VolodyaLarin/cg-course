//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMTRANSFORMATION_H
#define PROJECT_GLMTRANSFORMATION_H

#include <glm/glm.hpp>
#include <utils/ITransformation.h>

class GlmTransformation: public ITransformation {
public:
    glm::mat4x4 matrix;
public:
    explicit GlmTransformation(const glm::mat4x4 &matrix);

    ICoord::UPtr apply(const ICoord &coord) override;

    ITransformation &join(const ITransformation &transformation) override;

    [[nodiscard]] std::unique_ptr<ITransformation> clone() const override;

    std::shared_ptr<ITransformationFactory> getFactory() override;
};
#endif //PROJECT_GLMTRANSFORMATION_H
