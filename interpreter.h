#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"


class Interpreter
{
public:

    Parser m_parser;
    Interpreter(Parser p);
    float Visit(Node* n);
    float Interpret();
};

#endif // INTERPRETER_H
