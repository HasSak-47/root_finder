#ifndef BISECCION_REGLA_FALSA_HPP
#define BISECCION_REGLA_FALSA_HPP

#include "primitives.hpp"
#include <memory>

class BiseccionReglaFalsa {
private:
    std::unique_ptr<Function> f;
    Number a, b;
public:

    BiseccionReglaFalsa(Function* f, Number a, Number b):
        a(a),
        b(b) {
        this->f = std::unique_ptr<Function>(f);
    }

    void update_root();
    Number root();
};

#endif
