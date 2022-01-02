/**
 * Project Untitled
 */


#include "render/BaseNoTrasformationSupportDrawer.h"

void BaseNoTrasformationSupportDrawer::setCameraTransformation(const ITransformation &transformation) {
    _cameraTrans = transformation.clone();
}

void BaseNoTrasformationSupportDrawer::setObjectTransformation(const ITransformation &transformation) {
    _objectTrans = transformation.clone();
}
