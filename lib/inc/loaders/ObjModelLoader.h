//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_OBJMODELLOADER_H
#define PROJECT_OBJMODELLOADER_H

#include <vector>
#include "IModelLoader.h"

class ObjModelLoader: public IModelLoader {
public:
    Model::UPtr load(const std::string& filename, const IFactory<ICoord>& factory) override;
private:
    ICoord::UPtr _getNormal(const std::vector<ICoord::Ptr> &polygon, const IFactory<ICoord>& factory);
};


#endif //PROJECT_OBJMODELLOADER_H
