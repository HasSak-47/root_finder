#include <iostream>
#include <metodos/metodo_de_biseccion.hpp>
#include <ostream>
#include <thread>

void Biseccion::update_root(){
    Number fa = f->f(a);
    Number fb = f->f(b);
    Number c = (a + b) / 2;
    Number fc = f->f(c);
    std::cout << std::endl;

    using namespace std::chrono;
    std::this_thread::sleep_for(100ms);

    if ( (fc * fa).is_negative() ) this->b = c;
    if ( (fc * fb).is_negative() ) this->a = c;

    if(fc.is_really_close_to_zero()) this->a = c;
}

Number Biseccion::root(){
    while( !this->f->f(this->a).is_really_close_to_zero() ){
        update_root();
    }

    return this->a;
}
