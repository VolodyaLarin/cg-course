/**
 * Project Untitled
 */


#ifndef _IBUFFER_H
#define _IBUFFER_H


template<class T>
class IBuffer {
public:
    using Ptr = std::shared_ptr<IBuffer<T>>;

    virtual void set(int, int, const T&) = 0;

    virtual void get(int, int) = 0;

    virtual int getWidth() = 0;

    virtual int getHeight() = 0;
};


#endif //_IBUFFER_H