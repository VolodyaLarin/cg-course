/**
 * Project Untitled
 */


#ifndef _CAMERA_H
#define _CAMERA_H

#include "BaseSceneObject.h"
#include "utils/ITransformation.h"
#include "utils/ITransformationFactory.h"


class Camera: public BaseSceneObject {
public: 
    
    [[nodiscard]] ITransformation::Ptr getTransformation(Time) const;
    
    ITransformation::Ptr getInvTransformation(Time) const;

    [[nodiscard]] SceneObjectType getType() const override;

    void accept(IVisitor &visitor) override;

    void setTransformationFactory(const std::shared_ptr<ITransformationFactory> &transformationFactory);

private:
    float _pespK = 5;
    std::shared_ptr<ITransformationFactory> _transformationFactory;
};

#endif //_CAMERA_H