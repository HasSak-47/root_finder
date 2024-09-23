#ifndef METODO_DE_BISECCION_HPP
#define METODO_DE_BISECCION_HPP

#include "metodos/finder.hpp"
#include <stdexcept>

class Biseccion: public Finder{
protected:
    Number a, b;
public:

    Biseccion(Function* f, Number a, Number b):
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
