#include <metodos/biseccion_regla_falsa.hpp>

void BiseccionReglaFalsa::update_root(){
    auto& a = this->croot;
    Number fa = f->f(a);
    Number fb = f->f(b);
    Number c = a - (fa * (b - a)) / (fb - fa);
    Number fc = f->f(c);

    if ( (fc * fa).is_negative() ) b = c;
    if ( (fc * fb).is_negative() ) a = c;

    if(fc.is_really_close_to_zero()) a = c;
}
