/**
 * Project Untitled
 */


#ifndef _RENDERVISITOR_H
#define _RENDERVISITOR_H

#include "scene/IVisitor.h"
#include "utils/ITransformationFactory.h"
#include "OglDrawer.h"
#include "scene/ISceneObject.h"


class RenderVisitor: public IVisitor {
public:
    RenderVisitor(std::shared_ptr<OglDrawer> drawer);

    void visitModel(Model &model) override;

    void visitCamera(Camera &camera) override;

    void setTransformationFactory(const std::shared_ptr<ITransformationFactory> &transformationFactory);

    void setShaders(const shared_ptr<Shaders> &shaders);

    void setSendPosition(bool sendPosition);

private:
    bool _sendPosition = false;

    std::shared_ptr<Shaders> _shaders;
    std::shared_ptr<ITransformationFactory> _transformationFactory;
    std::shared_ptr<OglDrawer> _drawer;
    

    std::unique_ptr<ITransformation> _createObjectTransformation(const ISceneObject&, float);
};

#endif //_RENDERVISITOR_H