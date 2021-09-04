#include "render/RenderVisitor.h"

#include <utility>
#include <thread>
#include "scene/Model.h"

void RenderVisitor::visitModel(Model &model) {
    auto objectTransformation = _createObjectTransformation(model);
    _drawer->setObjectTransformation(*objectTransformation);

    int n = std::thread::hardware_concurrency();
    if (!n) n = 1;

    std::vector<std::thread> threads;
    threads.reserve(n);

    auto modelPtr = &model;

    for (int threadI = 0; threadI < n; ++threadI){
        threads.emplace_back([this, threadI, n, modelPtr](){
            for (auto polygon = modelPtr->begin() + threadI; polygon < modelPtr->end(); polygon += n) {
                _drawer->drawPolygon(*polygon, modelPtr->getColor());
            }
        });
    };
    for (int threadI = 0; threadI < n; ++threadI) {
        threads[threadI].join();
    }

}

void RenderVisitor::visitCamera(Camera &camera) {

}

RenderVisitor::RenderVisitor(std::shared_ptr<ITransformationFactory> transformationFactory, std::shared_ptr<IDrawer> drawer)
        : _transformationFactory(std::move(transformationFactory)),
          _drawer(std::move(drawer)) {}

std::unique_ptr<ITransformation> RenderVisitor::_createObjectTransformation(const ISceneObject &obj) {
    Time now = _drawer->getRenderContext()->time;

    auto transformation = _transformationFactory->create();

    transformation->join(
                    *_transformationFactory->createRotation(*obj.getRotation().get(now))
            )
            .join(
                    *_transformationFactory->createScale(*obj.getSize().get(now))
            )
            .join(
                    *_transformationFactory->createPosition(*obj.getPosition().get(now))
            );

    return transformation;
}
