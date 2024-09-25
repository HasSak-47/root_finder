#ifndef PRIMITIVES
#define PRIMITIVES

#include <cstdlib>
class Number{
public:
    double inner = 0.;
    bool is_zero(){
        return inner == 0;
    }
    bool is_really_close_to_zero(){
        return std::abs(inner) < 0.1 || inner == 0;
    }
    bool is_negative(){
        return inner < 0;
    }

    Number(double v){
        this->inner = v;
    }

    friend Number operator+(Number lhs, Number rhs);
    friend Number operator-(Number lhs, Number rhs);
    friend Number operator*(Number lhs, Number rhs);
    friend Number operator/(Number lhs, Number rhs);
    friend Number& operator+=(Number& lhs, Number rhs);
    friend Number& operator-=(Number& lhs, Number rhs);
    friend Number& operator*=(Number& lhs, Number rhs);
    friend Number& operator/=(Number& lhs, Number rhs);
};

inline Number operator+(Number lhs, Number rhs) { return lhs.inner + rhs.inner; }
inline Number operator-(Number lhs, Number rhs) { return lhs.inner - rhs.inner; }
inline Number operator*(Number lhs, Number rhs) { return lhs.inner * rhs.inner; }
inline Number operator/(Number lhs, Number rhs) { return lhs.inner / rhs.inner; }

inline Number& operator+=(Number& lhs, Number rhs){ lhs.inner += rhs.inner; return lhs; }
inline Number& operator-=(Number& lhs, Number rhs){ lhs.inner += rhs.inner; return lhs; }
inline Number& operator*=(Number& lhs, Number rhs){ lhs.inner += rhs.inner; return lhs; }
inline Number& operator/=(Number& lhs, Number rhs){ lhs.inner += rhs.inner; return lhs; }

class Function{
public:
    virtual ~Function() {};
    virtual Number f(Number x) const = 0 ;
};

inline Number df(Function& f, Number x) {
    Number dx= 0.001;
    return (f.f(x + dx) - f.f(x) ) / dx;
};

class Derivative : Function{
private:
    Function& original;
public:
    Derivative(Function& original): original(original){}
    ~Derivative() override{};
    Number f(Number x) const override{
        return df(original, x);
    };
};


#endif
