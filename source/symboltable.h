#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <QString>
#include <QMap>
#include <QDebug>
#include "errorhandler.h"
#include "pvar.h"
#include "token.h"

class Symbol {
public:
    QString m_name;
    QString m_type;
    PVar* m_value = nullptr;
    TokenType::Type getTokenType() {
        if (m_type.toLower()=="integer")
            return TokenType::INTEGER;
        if (m_type.toLower()=="float")
            return TokenType::REAL;
        if (m_type.toLower()=="address")
            return TokenType::ADDRESS;
        if (m_type.toLower()=="pointer")
            return TokenType::POINTER;
        if (m_type.toLower()=="byte")
            return TokenType::BYTE;
        if (m_type.toLower()=="string")
            return TokenType::STRING;
        return TokenType::NADA;
    }
    Symbol(QString name, QString type="") {
        m_name = name;
        m_type = type;
        m_value = new PVar();

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
    static SymbolTable s;


    static int m_currentSid;

    static void DefineSid(unsigned int initAddress, unsigned int playAddress) {
        m_currentSid++;
        QString s = QString::number(m_currentSid);

        QString init = "SIDFILE_"+s+"_INIT";
        QString play = "SIDFILE_"+s+"_PLAY";
        m_constants[init] = new Symbol("$"+QString::number(initAddress,16),"ADDRESS", initAddress);
        m_constants[play] = new Symbol("$"+QString::number(playAddress,16),"ADDRESS", playAddress);


    }


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
/*        if (!m_symbols.contains(name)) {
            ErrorHandler::e.Error("Symbol/variable '" + name + "' does not exist in the current scope", 0);
            return nullptr;
        }*/
        return m_symbols[name];
    }
    Symbol* LookupVariables(QString name) {
        if (!m_symbols.contains(name)) {
           return nullptr;
        }
        return m_symbols[name];
    }

    Symbol* LookupConstants(QString name) {
        if (m_constants.contains(name)) {
            return m_constants[name];
        }
        return nullptr;
    }

};

#endif // SYMBOLTABLE_H
