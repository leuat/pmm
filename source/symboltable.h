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
    Symbol(QString name, QString type, float var) {
        m_name = name;
        m_type = type;
        m_value = new PVar(var);
    }
    Symbol(QString name, QString type, QString var) {
        m_name = name;
        m_type = type;
        m_value = new PVar(var);
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
    static QMap<QString, Symbol*> m_constants;
    QString m_name;
    SymbolTable();

    static bool isInitialized;
    static void Initialize();

    void Define(Symbol* s) {
        m_symbols[s->m_name] = s;
    }
    void Delete() {
        for (QString val : m_symbols.keys()) {
            Symbol* s = m_symbols[val];
            if (s!=nullptr) {
                if (s->m_value)
                    delete s->m_value;

            }
            delete s;
        }

        // Delete static constants as well
        if (isInitialized) {
            for (QString val : m_constants.keys()) {
                Symbol* s = m_symbols[val];

                if (s!=nullptr) {
                    if (s->m_value)
                        delete s->m_value;

                }
                delete s;
            }
            isInitialized = false;

        }
    }

    void setName(QString s) {
        m_name = s;
    }

    void InitBuiltins();

    Symbol* Lookup(QString name) {
        if (m_constants.contains(name)) {
            return m_constants[name];
        }
        if (!m_symbols.contains(name)) {
            ErrorHandler::e.Error("Symbol '" + name + "' does not exist in the current scope");
        }
        return m_symbols[name];
    }

};

#endif // SYMBOLTABLE_H
