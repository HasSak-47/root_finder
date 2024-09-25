#ifndef FINDER_HPP
#define FINDER_HPP

#include "primitives.hpp"
#include <memory>

class Finder{
protected:
    std::shared_ptr<Function> f;
    Number croot;
public:
    virtual ~Finder(){}
    Finder(Function* f, Number croot): f(f), croot(croot){ }
    Finder(std::shared_ptr<Function> f, Number croot): f(f), croot(croot){ }

    virtual void update_root() = 0;
    virtual Number root();
};

#endif
