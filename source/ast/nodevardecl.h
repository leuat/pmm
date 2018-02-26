#ifndef NODEVARDECL_H
#define NODEVARDECL_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"

class NodeVarDecl : public Node {
public:
    Node* m_varNode = nullptr;
    Node* m_typeNode;
    NodeVarDecl(Node* varNode, Node* typeNode) {
        m_varNode = varNode;
        m_typeNode = typeNode;
    }

    void Delete() override {
        if (m_varNode) {
            m_varNode->Delete();
            delete m_varNode;
        }
        if (m_typeNode) {
            m_typeNode->Delete();
            delete m_typeNode;
        }

    }

    PVar Execute(SymbolTable* symTab, uint lvl) override {
        Pmm::Data::d.Set(m_op.m_lineNumber, m_op.m_currentLineText);
        level = lvl+1;
        ErrorHandler::e.DebugLow("Calling VarDecl",level);
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {
        QString typeName = ((NodeVar*)m_typeNode)->value;
        Symbol* typeSymbol = symTab->Lookup(typeName);
        QString varName = ((NodeVar*)m_varNode)->value;
        ErrorHandler::e.DebugLow("Typename define : " + typeName + "  variable " + varName);

        Symbol* varSymbol = new VarSymbol(varName, typeSymbol->m_name);
        symTab->Define(varSymbol);
    }


};



#endif // NODEVARDECL_H
