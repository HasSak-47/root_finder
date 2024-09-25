#include "metodos/iteracion_punto_fijo.hpp"

void IteracionPuntoFijo::update_root(){
    this->croot = this->f->f(this->croot);
}
