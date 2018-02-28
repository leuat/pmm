#ifndef NODEBINOP_H
#define NODEBINOP_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodeVar.h"

class NodeBinOP : public Node {
public:

    NodeBinOP(Node* left, Token op, Node* right) {
        m_right = right;
        m_left = left;
        m_op = op;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
        m_left->ExecuteSym(symTab);
        m_right->ExecuteSym(symTab);
    }

    QString Build(Assembler *as) override {
        m_left->Build(as);
        as->Term();
        bool isWord = false;
        QString varName="";
        if ( dynamic_cast<const NodeVar*>(m_left) != nullptr) {
            NodeVar* v= (NodeVar*)m_left;
            varName = v->value;
            Symbol* s = as->m_symTab->Lookup(varName);

            if (s->m_type.toLower()=="integer") isWord=true;
        }

        if (!isWord) {
            as->BinOP(m_op.m_type);
            m_right->Build(as);
            as->Term();
        }
        else {
            as->m_labelStack["wordAdd"].push();
            QString lbl = as->getLabel("wordAdd");
            as->Asm("clc");
            as->Asm("lda " +varName);
            as->ClearTerm();
            as->BinOP(m_op.m_type);
            m_right->Build(as);
            as->Term();
            as->Asm("sta " + varName);
            as->Asm("bcc "+lbl);
            as->Asm("inc " +varName + "+1");
            as->Label(lbl);
            as->m_labelStack["wordAdd"].pop();
        }
        return "";
    }

};


#endif // NODEBINOP_H
