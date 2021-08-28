/**
 * Project Untitled
 */


#ifndef _RENDERCONTEXT_H
#define _RENDERCONTEXT_H

#include "IColor.h"
#include "Time.h"
#include "Camera.h"
#include "ICoord.h"
#include "IBuffer.h"

class RenderContext {
public: 
    IBuffer<float>::Ptr z = nullptr;
    IBuffer<ICoord>::Ptr velocity= nullptr;
    Time time = 0;
    std::shared_ptr<Camera> camera = nullptr;
};

#endif //_RENDERCONTEXT_H