#ifndef ITERACION_PUNTO_FIJO_HPP
#define ITERACION_PUNTO_FIJO_HPP

#include "metodos/finder.hpp"
#include "primitives.hpp"

class IteracionPuntoFijo : Finder{
public:
    IteracionPuntoFijo(Function* f, Number croot): Finder(f, croot){}
    void update_root() override;
};

#endif
