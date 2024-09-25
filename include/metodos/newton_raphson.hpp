#ifndef NEWTON_RAPHSON_HPP
#define NEWTON_RAPHSON_HPP

#include "primitives.hpp"
#include <iostream>
#include <memory>

class NewtonGuesser : Function{
protected:
    std::shared_ptr<Function> original;
public:
    ~NewtonGuesser() override {}
    NewtonGuesser(std::shared_ptr<Function> f): original(f){}

    Number f(Number x) const override{
        Number n = x - (this->original->f(x) / df(*this->original, x));
        std::cout << n.inner << std::endl;
        std::cout << this->original->f(n.inner).inner << std::endl;
        return n;
    }
};

#endif
