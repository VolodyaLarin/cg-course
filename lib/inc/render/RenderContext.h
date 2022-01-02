/**
 * Project Untitled
 */


#ifndef _RENDERCONTEXT_H
#define _RENDERCONTEXT_H

#include <scene/Scene.h>
#include "utils/IColor.h"
#include "utils/Time.h"
#include "scene/Camera.h"
#include "utils/ICoord.h"
#include "utils/IBuffer.h"

class RenderContext {
public: 
    IBuffer<float>::Ptr z = nullptr;
    IBuffer<ICoord>::Ptr velocity= nullptr;
    Time time = 0;
    Time exposition = 0;
};

#endif //_RENDERCONTEXT_H