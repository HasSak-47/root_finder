#ifndef FINDER_HPP
#define FINDER_HPP

#include "primitives.hpp"
#include <memory>

class Finder{
protected:
    std::unique_ptr<Function> f;
public:
    virtual ~Finder(){}
    virtual Number root() = 0;
};

#endif
