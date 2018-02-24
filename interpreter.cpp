#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

float Interpreter::Visit(Node* n)
{
    return n->Execute();
}

float Interpreter::Interpret()
{
    Node* tree = m_parser.Parse();
    return Visit(tree);

}
