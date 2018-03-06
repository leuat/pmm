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


    int m_currentSid = 0;

    void DefineSid(unsigned int initAddress, unsigned int playAddress) {
        m_currentSid++;
        QString s = QString::number(m_currentSid);

        qDebug() << "SIDFILE_"+s+"_INIT : "  << ("$"+QString::number(initAddress,16));;

        m_constants["SIDFILE_"+s+"_INIT"]->m_value->m_fVal = initAddress;
        m_constants["SIDFILE_"+s+"_PLAY"]->m_value->m_fVal = playAddress;
        m_constants["SIDFILE_"+s+"_INIT"]->m_value->m_strVal = "$"+QString::number(initAddress,16);
        m_constants["SIDFILE_"+s+"_PLAY"]->m_value->m_strVal = "$"+QString::number(playAddress,16);
        ErrorHandler::e.Message("Adding sid file with initaddress $" + QString::number(initAddress,16)
                                +"and play address $" + QString::number(playAddress,16));



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
