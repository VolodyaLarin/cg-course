/**
 * Project Untitled
 */



#ifndef _ICOLOR_H
#define _ICOLOR_H

#include <memory>

class IColor {
public:

    virtual float getR() const = 0;

    virtual float getG() const = 0;

    virtual float getB() const = 0;

    virtual float getA() const = 0;

    virtual void setR(float) = 0;

    virtual void setG(float) = 0;

    virtual void setB(float) = 0;

    virtual void setA(float) = 0;
    
    [[nodiscard]] virtual std::unique_ptr<IColor> clone() const = 0;
};

#endif //_ICOLOR_H