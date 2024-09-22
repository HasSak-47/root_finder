#ifndef PRIMITIVES
#define PRIMITIVES

#include <cstdlib>
class Number{
protected:
    double inner = 0.;
public:
    bool is_zero(){
        return inner == 0;
    }
    bool is_really_close_to_zero(){
        return std::abs(inner) <= 0.00001;
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
    ~Function();
    virtual Number f(Number x);
};

#endif
