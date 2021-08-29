/**
 * Project Untitled
 */


#ifndef _BASENOTRASFORMATIONSUPPORTDRAWER_H
#define _BASENOTRASFORMATIONSUPPORTDRAWER_H

#include "IDrawer.h"


class BaseNoTrasformationSupportDrawer: public IDrawer {
public:
    void setCameraTransformation(const ITransformation &transformation) override;

    void setObjectTransformation(const ITransformation &transformation) override;

private: 
    std::shared_ptr<ITransformation> _cameraTrans;
    std::shared_ptr<ITransformation> _objectTrans;
};

#endif //_BASENOTRASFORMATIONSUPPORTDRAWER_H