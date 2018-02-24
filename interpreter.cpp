#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

int Interpreter::Visit(Node* n)
{
    return n->getFloatVal();
/*    if (n->m_isLeaf) {
        return n->getIntVal();
    }

    if (n->m_op.m_type==TokenType::PLUS)
        return Visit(n->m_left) + Visit(n->m_right);
    if (n->m_op.m_type==TokenType::MINUS)
        return Visit(n->m_left) - Visit(n->m_right);

    if (n->m_op.m_type==TokenType::MUL)
        return Visit(n->m_left) * Visit(n->m_right);
    if (n->m_op.m_type==TokenType::DIV)
        return Visit(n->m_left) / Visit(n->m_right);

*/
    qDebug() << "Error: not leaf but no operations supporeted";
}

int Interpreter::Interpret()
{
    Node* tree = m_parser.Parse();
    return Visit(tree);

}
