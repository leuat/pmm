#ifndef NODEUNARYOP_H
#define NODEUNARYOP_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeUnaryOp : public Node {
public:
    NodeUnaryOp(Token t, Node* right) {
        m_op = t;
        m_right = right;
        m_left = nullptr;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling Unary Op Node",level);

        if (m_op.m_type==TokenType::PLUS)
            return m_right->Execute(symTab, level)*1;
        if (m_op.m_type==TokenType::MINUS)
            return m_right->Execute(symTab, level)*-1;
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        m_right->ExecuteSym(symTab);
    }

};

#endif // NODEUNARYOP_H
