#ifndef BISECCION_REGLA_FALSA_HPP
#define BISECCION_REGLA_FALSA_HPP

#include "metodos/finder.hpp"
#include "primitives.hpp"
#include <stdexcept>

class BiseccionReglaFalsa : public Finder{
private:
    Number b;
public:
    BiseccionReglaFalsa(Function* f, Number a, Number b):
        Finder(f, a),
        b(b) {
        auto fb = this->f->f(b);
        auto fa = this->f->f(a);
        if( (fb * fa).inner > 0 ){
            throw std::runtime_error("rango invalido");
        }
    }

    BiseccionReglaFalsa(std::shared_ptr<Function> f, Number a, Number b):
        Finder(f, a),
        b(b) {
        auto fb = this->f->f(b);
        auto fa = this->f->f(a);
        if( (fb * fa).inner > 0 ){
            throw std::runtime_error("rango invalido");
        }
    }
    void update_root() override;
};

#endif
