#ifndef NODEVARTYPE_H
#define NODEVARTYPE_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"
#include "source/ast/nodevar.h"

class NodeVarType : public Node {
public:
    QString value;
    Token m_arrayVarType;
    QStringList m_data;
    QString m_filename, m_position;
    QString initVal ="0";

    NodeVarType(Token t, QString position,   Token arrayVarType,QStringList data) {
        m_op = t;
        value = t.m_value;
        m_arrayVarType = arrayVarType;
        m_data = data;
        m_position = position;

    }
    NodeVarType(Token t, QStringList data) {
        m_op = t;
        value = t.m_value;
        //m_arrayVarType = TokenType::STRING;
        m_data = data;

    }
    NodeVarType(Token t,  QString filename, QString position ) {
        m_op = t;
        value = t.m_value;
        m_filename = filename;
        m_position = position;


    }
    NodeVarType(Token t,  QString initvalue ) {
        m_op = t;
        value = t.m_value;
        initVal = initvalue;

    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {

    }

};
#endif // NODEVARTYPE_H
