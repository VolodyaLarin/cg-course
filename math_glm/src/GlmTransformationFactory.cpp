//
// Created by volodya on 29.08.2021.
//

#include <glm/ext/matrix_transform.hpp>

#include <GlmTransformation.h>
#include "GlmTransformationFactory.h"

#include <GlmCoord.h>


std::unique_ptr<ITransformation> GlmTransformationFactory::createPosition(const ICoord &coord) {
    auto matrix = glm::translate(
            glm::mat4x4(),
            glm::vec3(coord.getX(), coord.getY(), coord.getZ())
    );
    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createRotation(const ICoord &coord) {
    auto matrix = glm::mat4x4();

    matrix = glm::rotate(matrix, coord.getX(), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, coord.getY(), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, coord.getZ(), glm::vec3(0.0f, 0.0f, 1.0f));

    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createScale(const ICoord &coord) {
    auto matrix = glm::scale(
            glm::mat4x4(),
            glm::vec3(coord.getX(), coord.getY(), coord.getZ())
    );
    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createPerspective(ICoord::type type) {
    return std::make_unique<GlmTransformation>(glm::mat4x4());
}

std::unique_ptr<ITransformation> GlmTransformationFactory::create() {
    return std::make_unique<GlmTransformation>(glm::mat4x4());
}
