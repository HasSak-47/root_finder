#include <iostream>
#include <metodos/metodo_de_biseccion.hpp>
#include <ostream>
#include <thread>

void Biseccion::update_root(){
    auto& a = this->croot;
    Number fa = f->f(a);
    Number fb = f->f(b);
    Number c = (a + b) / 2;
    Number fc = f->f(c);
    std::cout << std::endl;

    using namespace std::chrono;
    std::this_thread::sleep_for(100ms);

    if ( (fc * fa).is_negative() ) b = c;
    if ( (fc * fb).is_negative() ) a = c;

    if(fc.is_really_close_to_zero()) a = c;
}
