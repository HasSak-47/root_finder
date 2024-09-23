#include "metodos/biseccion_regla_falsa.hpp"
#include "primitives.hpp"
#include <cmath>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include <cctype>

class Sine;
class Cosine;
class Tangent;

class Secant;
class Cosecant;
class Cotangent;

class ArcSine;
class ArcCosine;
class ArcTangent;

class ArcSecant;
class ArcCosecant;
class ArcCotangent;

class Logarithm;

#define DEFINE_FUNCTION(name, func)\
class name : public Function{\
public:\
    ~name(){} \
    name(){}\
    Number f(Number x) const override {\
        return Number(func(x.inner));\
    }\
\
    static const name curr;\
};\
const name name::curr = {};\

// define functions
DEFINE_FUNCTION(Sine      , sin);
DEFINE_FUNCTION(Cosine    , cos);
DEFINE_FUNCTION(Tangent   , tan);

DEFINE_FUNCTION(ArcSine   , asin);
DEFINE_FUNCTION(ArcCosine , acos);
DEFINE_FUNCTION(ArcTangent, atan);

DEFINE_FUNCTION(Logarithm, log);

struct Pairs{ const Function* func; const char* name;  } pairs[] = {
    { &Sine::curr      , "sin"  },
    { &Cosine::curr    , "cos"  },
    { &Tangent::curr   , "tan"  },
    { &ArcSine::curr   , "asin" },
    { &ArcCosine::curr , "acos" },
    { &ArcTangent::curr, "atan" },
    { &Logarithm::curr , "log"  },
};

struct Token{
    enum class Type{
        Function,
        Variable,
        Constant,
        Operator,
        Open,
        Close,
        Undefined,
    } type = Type::Undefined;
    std::string data = "";

};

std::ostream& operator<<(std::ostream& os, const Token::Type& t){
    switch (t) {
        case Token::Type::Function:
            os << "Func:  ";
            break;
        case Token::Type::Variable:
            os << "Var :  ";
            break;
        case Token::Type::Constant:
            os << "Const: ";
            break;
        case Token::Type::Operator:
            os << "oper:  ";
            break;
        case Token::Type::Open:
            os << "Open: ";
            break;
        case Token::Type::Close:
            os << "Close:  ";
            break;
        default:
            os << "Undef: ";
            break;
    }
    return os;

}
std::ostream& operator<<(std::ostream& os, const Token& t){
    os << t.type << "\"" << t.data << "\"";
    return os;
}

bool is_operator(char c){
    return
        c == '+' || c == '-' ||
        c == '*' || c == '/' ||
        c == '^'
    ;
}

int hiarchy(char k){
    int a = 0;
    switch (a) {
        case '+':
            a = 0;
            break;
        case '-':
            a = 1;
            break;
        case '*':
            a = 2;
            break;
        case '/':
            a = 3;
            break;
        default:
            break;
    }

    return a;
}

bool operator_hirachy(char a, char b){
    // PEMBDAS
    int ia = hiarchy(a);
    int ib = hiarchy(b);
    return ia > ib;
}

bool is_open(char c){ return c == '(' || c == '{' || c == '[' ; }
bool is_close(char c){ return c == ')' || c == '}' || c == ']' ; }

bool can_be_literal(char c){
    return isalnum(c) && !(is_open(c) || is_close(c) || is_operator(c));
}


std::vector<Token> sanatize_and_tokenize(std::string _in){
    std::string in = "";
    for(const auto & c : _in){
        if (!isspace(c) && isprint(c))
            in += c;
    }

    std::vector<Token> tokens = {};

    for(size_t i = 0; i < in.length(); ++i){
        char& c = in[i];
        if(isalpha(c)){
            size_t end = i;
            while( end < in.length() && can_be_literal(in[end])) end++;
            tokens.push_back(Token {
                Token::Type::Undefined,
                in.substr(i, end - i)
            });

            i = end - 1;
        }
        if(isdigit(c)){
            size_t end = i;
            while( end < in.length() && isdigit(in[end])) end++;
            tokens.push_back(Token {
                Token::Type::Constant,
                in.substr(i, end - i)
            });

            i = end - 1;
        }

        if(is_open(c)){
            tokens.push_back(Token {
                Token::Type::Open,
                in.substr(i, 1)
            });
        }
        else
        if(is_close(c)){
            tokens.push_back(Token {
                Token::Type::Close,
                in.substr(i, 1)
            });
        }
        else
        if(is_operator(c)){
            tokens.push_back(Token {
                Token::Type::Operator,
                in.substr(i, 1)
            });
        }
    }
    for(auto & d: tokens){
        if( d.type == Token::Type::Undefined ){
            bool found = false;
            for( const auto& pair : pairs ){
                if( pair.name == d.data ){
                    d.type = Token::Type::Function;
                    found = true;
                }
            }
            if(!found)
                d.type = Token::Type::Variable;
        }
    }
    return tokens;
}


class GenerativeFunction : public Function{
private:
    std::vector<Token> inner;
public:
    ~GenerativeFunction(){}
    GenerativeFunction(std::string form){
        auto data = sanatize_and_tokenize(form);

        // reverse polish notation
        std::vector<Token> queue;
        std::vector<Token> stack;
        for(const auto & d : data){
            if(d.type == Token::Type::Constant || d.type == Token::Type::Variable){
                queue.push_back(d);
            }
            else
            if(d.type == Token::Type::Open){
                stack.push_back(d);
            }
            else
            if(d.type == Token::Type::Close){
                while(stack.size() != 0 && stack.back().type != Token::Type::Open){
                    queue.push_back(stack.back());
                    stack.pop_back();
                }
                if(stack.size() != 0){
                    stack.pop_back();
                }
                if(stack.size() != 0 && stack.back().type == Token::Type::Function){
                    queue.push_back(stack.back());
                    stack.pop_back();
                }
            }
            else
            if(d.type == Token::Type::Function){
                stack.push_back(d);
            }
            else
            if(d.type == Token::Type::Operator){
                if(stack.size() != 0 && operator_hirachy( stack.back().data[0], d.data[0] ) ){
                    queue.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(d);
            }
        }

        while(stack.size() != 0){
            queue.push_back(stack.back());
            stack.pop_back();
        }
        this->inner = queue;
    }

    Number f(Number x) const override{
        using TT = Token::Type;
        std::vector<Number> stack;
        for(const auto & v : this->inner){
            if(v.type == TT::Constant){
                stack.push_back(std::stof(v.data));
            }
            else
            if(v.type == TT::Variable){
                stack.push_back(x);
            }
            else
            if(v.type == TT::Operator){
                auto a = stack.at(stack.size() - 1);
                auto b = stack.at(stack.size() - 2);
                Number next = {0};
                switch (v.data[0]) {
                    case '+':
                        next = a + b;
                        break;
                    case '-':
                        next = a - b;
                        break;
                    case '*':
                        next = a * b;
                        break;
                    case '/':
                        next = a / b;
                        break;
                    case '^':
                        next = Number(std::pow(b.inner, a.inner));
                        break;
                }
                stack.pop_back();
                stack.pop_back();
                stack.push_back(next);
            }
            else
            if(v.type == TT::Function){
                auto& back = stack.back();
                bool found = false;
                for( const auto& pair : pairs ){
                    if( pair.name == v.data ){
                        back = pair.func->f(back);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "error?";
                }

            }
        }
        return stack[0];
    }
};


int main(const int argc, const char* argv[]){
    const char* v = argc == 1 ? "2 * x" : argv[1];
    auto f = new GenerativeFunction(v);
    auto n = BiseccionReglaFalsa(f, -10, 10);
    auto root = n.root();
    std::cout << root.inner << std::endl;

    return 0;
}
