#include "metodos/iteracion_punto_fijo.hpp"

void IteracionPuntoFijo::update_root(){
    this->croot = this->guess->f(this->croot);
}
