/**
 * Project Untitled
 */


#ifndef _IVISITOR_H
#define _IVISITOR_H


class Model;
class Camera;

class IVisitor {
public:
    virtual void visitModel(Model&) = 0;

    virtual void visitCamera(Camera&) = 0;
};

#endif //_IVISITOR_H