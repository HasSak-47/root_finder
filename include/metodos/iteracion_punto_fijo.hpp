#ifndef ITERACION_PUNTO_FIJO_HPP
#define ITERACION_PUNTO_FIJO_HPP

#include "metodos/finder.hpp"
#include "primitives.hpp"

class IteracionPuntoFijo : public Finder{
private:
public:
    std::shared_ptr<Function> guess;
public:
    IteracionPuntoFijo(Function* f, Function* g, Number croot): Finder(f, croot), guess(g){}
    IteracionPuntoFijo(std::shared_ptr<Function> f, std::shared_ptr<Function> g, Number croot): Finder(f, croot), guess(g){}
    void update_root() override;
};

#endif
