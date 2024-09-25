#include <metodos/metodo_de_biseccion.hpp>

void Biseccion::update_root(){
    auto& a = this->croot;
    Number fa = f->f(a);
    Number fb = f->f(b);
    Number c = (a + b) / 2;
    Number fc = f->f(c);

    if ( (fc * fa).is_negative() ) b = c;
    if ( (fc * fb).is_negative() ) a = c;

    if(fc.is_really_close_to_zero()) a = c;
}
