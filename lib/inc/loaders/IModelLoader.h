//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_IMODELLOADER_H
#define PROJECT_IMODELLOADER_H


#include <scene/Model.h>
#include "utils/IFactory.h"

class IModelLoader {
public:
    virtual Model::UPtr load(const std::string& filename, const IFactory<ICoord>& factory) = 0;
};


#endif //PROJECT_IMODELLOADER_H
