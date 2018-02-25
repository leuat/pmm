#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

float Interpreter::Visit(Node* n)
{
    n->Execute(0);
}

float Interpreter::Interpret()
{
    Node* tree = m_parser.Parse();
    return Visit(tree);

}
