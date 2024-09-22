#ifndef BISECCION_REGLA_FALSA_HPP
#define BISECCION_REGLA_FALSA_HPP

#include "primitives.hpp"
#include <memory>

class BiseccionReglaFalsa : public Function{
private:
    std::unique_ptr<Function> f;
    Number a, b;
public:

    BiseccionReglaFalsa(Function* f, Number a, Number b):
        a(a),
        b(b) {
        this->f = std::unique_ptr<Function>(f);
    }

    void update_root(){
        Number fa = f->f(a);
        Number fb = f->f(b);
        Number c = a - (fa * (b - a)) / (fb - fa);
        Number fc = f->f(c);

        if ( (fc * fa).is_negative() ) this->b = c;
        if ( (fc * fb).is_negative() ) this->a = c;
    }

    Number root(){
        while( !this->a.is_really_close_to_zero() )
            update_root();

        return this->a;
    }
};

#endif
