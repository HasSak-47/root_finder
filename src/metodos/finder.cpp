#include <sstream>
#include <metodos/finder.hpp>
#include <stdexcept>

Number Finder::root(){
    size_t iters = 0;
    while(iters++ < 1000 && !this->f->f(croot).is_really_close_to_zero()){
        this->update_root();
    }
    if(!this->f->f(croot).is_really_close_to_zero()){
        std::stringstream ss;
        ss << "el valor es invalido, al intentar usarlo dio: x = " << this->croot.inner << " y f(x) = " << this->f->f(croot).inner;;
        throw std::runtime_error(ss.str());
    }
    return croot;
}
