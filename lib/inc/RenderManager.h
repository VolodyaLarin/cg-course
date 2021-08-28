/**
 * Project Untitled
 */


#ifndef _RENDERMANAGER_H
#define _RENDERMANAGER_H

#include "IDrawer.h"
#include "RenderContext.h"

class RenderManager {
public:
    [[nodiscard]] const std::shared_ptr<IDrawer> &getDrawer() const;

    void setDrawer(const std::shared_ptr<IDrawer> &drawer);

    void render(RenderContext&);

private:
    std::shared_ptr<IDrawer> _drawer;
};

#endif //_RENDERMANAGER_H