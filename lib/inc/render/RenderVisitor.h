/**
 * Project Untitled
 */


#ifndef _RENDERVISITOR_H
#define _RENDERVISITOR_H

#include "scene/IVisitor.h"
#include "utils/ITransformationFactory.h"
#include "RenderContext.h"
#include "IDrawer.h"
#include "scene/ISceneObject.h"


class RenderVisitor: public IVisitor {
public:
    RenderVisitor(std::shared_ptr<ITransformationFactory> transformationFactory,
                  std::shared_ptr<RenderContext> context, std::shared_ptr<IDrawer> drawer);

    void visitModel(Model &model) override;

    void visitCamera(Camera &camera) override;



private:
    std::shared_ptr<ITransformationFactory> _transformationFactory;
    std::shared_ptr<RenderContext> _context;
    std::shared_ptr<IDrawer> _drawer;
    

    void _createObjectTransformation(const ISceneObject&);
};

#endif //_RENDERVISITOR_H