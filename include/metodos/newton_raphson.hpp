#ifndef NEWTON_RAPHSON_HPP
#define NEWTON_RAPHSON_HPP

#include "primitives.hpp"
#include <memory>

class NewtonGuesser : Function{
protected:
    std::shared_ptr<Function> original;
public:
    ~NewtonGuesser() override {}
    NewtonGuesser(std::shared_ptr<Function> f): original(f){}

    Number f(Number x) const override{
        return x - (this->original->f(x) / df(*this->original, x));
    }
};

#endif
