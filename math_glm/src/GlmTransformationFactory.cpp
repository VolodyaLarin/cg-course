//
// Created by volodya on 29.08.2021.
//

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <GlmTransformation.h>
#include "GlmTransformationFactory.h"

#include <GlmCoord.h>


std::unique_ptr<ITransformation> GlmTransformationFactory::createPosition(const ICoord &coord) const {
    auto matrix = glm::translate(
            glm::mat4x4(1.0f),
            glm::vec3(coord.getX(), coord.getY(), coord.getZ())
    );
    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createRotation(const ICoord &coord) const {
    auto matrix = glm::mat4x4(1.0f);

    matrix = glm::rotate(matrix, coord.getX(), glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, coord.getY(), glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, coord.getZ(), glm::vec3(0.0f, 0.0f, 1.0f));

    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createScale(const ICoord &coord) const {
    auto matrix = glm::scale(
            glm::mat4x4(1.0f),
            glm::vec3(coord.getX(), coord.getY(), coord.getZ())
    );
    return std::make_unique<GlmTransformation>(matrix);
}

std::unique_ptr<ITransformation> GlmTransformationFactory::createPerspective(ICoord::type type) const {
    return std::make_unique<GlmTransformation>(
            glm::perspective(
                    glm::radians(90.0f), // Вертикальное поле зрения в радианах. Обычно между 90&deg; (очень широкое) и 30&deg; (узкое)
                    1.0f,       // Отношение сторон. Зависит от размеров вашего окна. Заметьте, что 4/3 == 800/600 == 1280/960
                    0.01f,              // Ближняя плоскость отсечения. Должна быть больше 0.
                    100.0f             // Дальняя плоскость отсечения.
            )
    );
}

std::unique_ptr<ITransformation> GlmTransformationFactory::create() const {
    return std::make_unique<GlmTransformation>(glm::mat4x4(1.0f));
}
