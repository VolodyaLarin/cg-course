/**
 * Project Untitled
 */


#ifndef _BASENOTRASFORMATIONSUPPORTDRAWER_H
#define _BASENOTRASFORMATIONSUPPORTDRAWER_H

#include "IDrawer.h"


class BaseDrawer: public IDrawer {
public:
    void setCameraTransformation(const ITransformation &transformation) override;

    void setObjectTransformation(const ITransformation &transformation) override;

    void setRenderContext(std::shared_ptr<RenderContext> context) override;

    const std::shared_ptr<RenderContext> &getRenderContext() override;

protected:
    std::shared_ptr<ITransformation> _cameraTrans;
    std::shared_ptr<ITransformation> _objectTrans;
    std::shared_ptr<RenderContext> _context;
};

#endif //_BASENOTRASFORMATIONSUPPORTDRAWER_H