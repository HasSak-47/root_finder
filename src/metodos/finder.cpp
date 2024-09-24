#include <metodos/finder.hpp>
#include <stdexcept>

Number Finder::root(){
    size_t iters = 0;
    while(iters++ < 1000 && !this->f->f(croot).is_really_close_to_zero())
        this->update_root();
    if(!this->f->f(croot).is_really_close_to_zero())
        throw std::runtime_error("could not find root");
    return croot;
}
