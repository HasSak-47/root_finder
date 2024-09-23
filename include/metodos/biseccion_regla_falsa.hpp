#ifndef BISECCION_REGLA_FALSA_HPP
#define BISECCION_REGLA_FALSA_HPP

#include "primitives.hpp"
#include <memory>
#include <stdexcept>

class BiseccionReglaFalsa {
private:
    std::unique_ptr<Function> f;
    Number a, b;
public:

    BiseccionReglaFalsa(Function* f, Number a, Number b):
        a(a),
        b(b) {
        this->f = std::unique_ptr<Function>(f);
        auto fb = this->f->f(b);
        auto fa = this->f->f(a);
        if( (fb * fa).inner > 0 ){
            throw std::runtime_error("rango invalido");
        }
    }

    void update_root();
    Number root();
};

#endif
