#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QString>
#include <QMap>
#include <QDebug>

class Symbol {
public:
    QString m_name;
    QString m_type;
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

    SymbolTable();
    void Define(Symbol* s) {
        m_symbols[s->m_name] = s;
    }

    void InitBuiltins();

    Symbol* Lookup(QString name) {
        if (!m_symbols.contains(name)) {
            qDebug() << "Symbol " << name << " does not exist in the current scope";
            exit(1);
        }
        return m_symbols[name];
    }

};

#endif // SYMBOLTABLE_H
