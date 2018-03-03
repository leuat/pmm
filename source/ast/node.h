#ifndef NODE_H
#define NODE_H

#include "source/token.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/assembler/assembler.h"


class Node {
public:
    Token m_op;
    int m_lineNumber;
    uint level = 0;
    Node* m_left = nullptr, *m_right = nullptr;
    virtual PVar Execute(SymbolTable* symTab, uint lvl) = 0;
    virtual void ExecuteSym(SymbolTable* symTab) = 0;
    virtual void Delete() {
        if (m_left!=nullptr) {
            m_left->Delete();
            delete m_left;
            m_left = nullptr;
        }
        if (m_right!=nullptr) {
            m_right->Delete();
            delete m_right;
            m_left = nullptr;

        }
    }
    virtual bool isPureNumeric() {
        return false;
    }
    virtual QString Build(Assembler* as) {
        return "";
    }
    virtual void LoadVariable(Assembler* a) {}
};


class NoOp : public Node {
    public:
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        level = lvl+1;
        return PVar();
    }
    void ExecuteSym(SymbolTable* symTab) override {

    }
};

#endif // NODE_H
