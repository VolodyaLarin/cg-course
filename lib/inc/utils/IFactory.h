/**
 * Project Untitled
 */


#ifndef _IFACTORY_H
#define _IFACTORY_H
#include <memory>

template<class T >
class IFactory {
public:
    virtual std::unique_ptr<T> create() = 0;
};

#endif //_IFACTORY_H