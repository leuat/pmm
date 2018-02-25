#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include "errorhandler.h"
#include "pvar.h"

class Symbol {
public:
    QString m_name;
    QString m_type;
    PVar* m_value = nullptr;
    Symbol(QString name, QString type="") {
        m_name = name;
        m_type = type;

    }

};


class BuiltInTypeSymbol : public Symbol {
public:
    BuiltInTypeSymbol(QString name, QString type) : Symbol(name, type) {
    }
};

class VarSymbol : public Symbol {
public:
    VarSymbol(QString name, QString type) : Symbol(name, type) {

    }
};

class SymbolTable
{
public:
    QMap<QString, Symbol*> m_symbols;
    QString m_name;
    SymbolTable();
    void Define(Symbol* s) {
        m_symbols[s->m_name] = s;
    }

    void setName(QString s) {
        m_name = s;
    }

    void InitBuiltins();

    Symbol* Lookup(QString name) {
        if (!m_symbols.contains(name)) {
            ErrorHandler::e.Error("Symbol '" + name + "' does not exist in the current scope");
        }
        return m_symbols[name];
    }

};

#endif // SYMBOLTABLE_H
