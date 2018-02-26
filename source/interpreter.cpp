#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

float Interpreter::Visit(Node* n)
{
    n->Execute(nullptr, 0);
    return 0;
}

float Interpreter::Interpret()
{
    Node* tree = m_parser.Parse();
    Visit(tree);
    tree->Delete();

}
