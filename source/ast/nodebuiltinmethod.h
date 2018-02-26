#ifndef NODEBUILTINMETHOD_H
#define NODEBUILTINMETHOD_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeBuiltinMethod : public Node {
public:
    QString m_procName;
    Node* m_block = nullptr;
    Node* m_text = nullptr;
    NodeBuiltinMethod(QString m, Node* text, Node* block) {
        m_procName = m;
        m_block = block;
        m_text = text;
    }
    PVar Execute(SymbolTable* symTab, uint lvl) override {
        ErrorHandler::e.DebugLow("Calling Builtin",level);
        level = lvl+1;

        if (m_procName.toLower()=="writeln") {
            QString s = "";
            if (m_text!=nullptr)
                s+=m_text->Execute(symTab, level).toString();
            if (m_block!=nullptr)
                s+=m_block->Execute(symTab, level).toString();
            QTextStream out(stdout);
            out << s << endl;
        }
        return PVar();

    }
    void ExecuteSym(SymbolTable* symTab) override {

    }
};


#endif // NODEBUILTINMETHOD_H
