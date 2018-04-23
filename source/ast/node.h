#ifndef NODE_H
#define NODE_H

#include "source/token.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/assembler/assembler.h"
#include "source/assembler/mos6502.h"


class Node {
public:
    Token m_op;
    int m_lineNumber;
    uint level = 0;
    Node* m_left = nullptr, *m_right = nullptr;
    bool m_isWord = false;

    TokenType::Type m_forceType = TokenType::NADA;

    int m_cycleCounter;
    static int m_currentLineNumber;
    virtual PVar Execute(SymbolTable* symTab, uint lvl) = 0;
    virtual void ExecuteSym(SymbolTable* symTab) = 0;
    virtual bool DataEquals(Node* other) { return false;}
    virtual QString HexValue() {return "0";}
    virtual int numValue() { return 0;}
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
        m_currentLineNumber = m_op.m_lineNumber;
        return "";
    }
    virtual void LoadVariable(Assembler* a) {}
    virtual void StoreVariable(Assembler* a) {}
    virtual TokenType::Type getType(Assembler* as) {
        return m_op.m_type;
    }

    virtual bool isAddress() { return false;}
    virtual void AssignPointer(Assembler* as, QString memoryLocation) {}

    void RequireAddress(Node* n,QString name, int ln) {
        if (!n->isAddress())
            ErrorHandler::e.Error(name + " requires parameter to be memory address", ln);
    }

    void RequireNumber(Node* n,QString name, int ln) {
        if (!n->isPureNumeric())
            ErrorHandler::e.Error(name + " requires parameter to be pure numeric", ln);
    }

    virtual bool isWord(Assembler* as) { return false;}

   virtual bool isMinusOne() { return false; }
    virtual bool isOne() { return false; }

    bool verifyBlockBranchSize(Assembler *as, Node* testBlock)
    {
        AsmMOS6502 tmpAsm;
        tmpAsm.m_symTab = as->m_symTab;
        testBlock->Build(&tmpAsm);
        //qDebug() << "block count:" << tmpAsm.m_source.count();
        int blockCount = tmpAsm.m_source.count();
        return blockCount<80;

    }


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
