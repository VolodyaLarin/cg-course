/**
 * Project Untitled
 */


#ifndef _CAMERA_H
#define _CAMERA_H

#include "BaseSceneObject.h"
#include "ITransformation.h"


class Camera: public BaseSceneObject {
public: 
    
ITransformation::Ptr getTransformation(Time);
    
ITransformation::Ptr getInvTransformation(Time);
private: 
    std::shared_ptr<ITransformationFactory> _transformationFactory;
};

#endif //_CAMERA_H