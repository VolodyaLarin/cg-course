/**
 * Project Untitled
 */


#ifndef _ICOORD_H
#define _ICOORD_H

#include <memory>

class ICoord {
public:
    using Ptr = std::shared_ptr<ICoord>;
    using UPtr = std::unique_ptr<ICoord>;
    using type = float;

    [[nodiscard]] virtual type getX() const = 0;

    [[nodiscard]] virtual type getY() const = 0;

    [[nodiscard]] virtual type getZ() const = 0;

    virtual void setX(type) = 0;

    virtual void setY(type) = 0;

    virtual void setZ(type) = 0;

    [[nodiscard]] virtual ICoord::UPtr sum(const ICoord &) const = 0;

    virtual void add(const ICoord &) = 0;

    [[nodiscard]] virtual ICoord::UPtr diff(const ICoord &) const = 0;

    virtual void sub(const ICoord &) = 0;

    [[nodiscard]] virtual ICoord::UPtr clone() const = 0;

    [[nodiscard]] virtual ICoord::UPtr invert() const = 0;

    [[nodiscard]] virtual ICoord::UPtr mul(type) const = 0;

    virtual void mulled(type) = 0;

};

#endif //_ICOORD_H