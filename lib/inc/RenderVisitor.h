/**
 * Project Untitled
 */


#ifndef _RENDERVISITOR_H
#define _RENDERVISITOR_H

#include "IVisitor.h"
#include "ITransformationFactory.h"
#include "RenderContext.h"
#include "IDrawer.h"
#include "ISceneObject.h"


class RenderVisitor: public IVisitor {
public:
    RenderVisitor(const std::shared_ptr<ITransformationFactory> &transformationFactory,
                  const std::shared_ptr<RenderContext> &context, const std::shared_ptr<IDrawer> &drawer);

    void visitModel(Model &model) override;

    void visitCamera(Camera &camera) override;



private:
    std::shared_ptr<ITransformationFactory> _transformationFactory;
    std::shared_ptr<RenderContext> _context;
    std::shared_ptr<IDrawer> _drawer;
    

    void _createObjectTransformation(const ISceneObject&);
};

#endif //_RENDERVISITOR_H