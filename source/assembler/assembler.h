#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <QString>
#include <QVector>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include "source/token.h"
#include "source/errorhandler.h"
#include "source/symboltable.h"

class Stack {
public:
    QVector<QString> m_vars;
    QString m_current;
    void push(QString s) {
        m_vars.push_back(s);
        m_current = s;
    }
    void pop() {
        m_current=m_vars[m_vars.count()-1];
        //m_vars.removeLast();
        m_vars.remove(m_vars.count()-1);
    }
  public:
        QString current() const;
};
class LabelStack {
public:
    QVector<QString> m_vars;
    QString m_current;

    QMap<QString, bool> sNumbersUsed;

    void push() {
        bool ok=false;
        while (!ok) {
            m_current = QString::number(rand()%100000);
            ok=true;
            if (sNumbersUsed.contains(m_current))
                ok = false;
        }
        sNumbersUsed[m_current] = true;

        m_vars.push_back(m_current);
    }
    void pop() {
        if (m_vars.count()==0) {
            ErrorHandler::e.Error("Trying to pop labelstack from zero : " + m_current);
        }
        m_vars.remove(m_vars.count()-1);
        if (m_vars.count()!=0)
            m_current = m_vars[m_vars.count()-1];

    }
};


class Assembler
{
public:
    QStringList m_source;
    QStringList m_appendix;
    QString m_term;
    QMap<QString, Stack> m_stack;
    QMap<QString, LabelStack> m_labelStack;
    SymbolTable* m_symTab;
    QString m_projectDir;


    QStringList m_tempVars;
    int m_varDeclEndsLineNumber = 0;
    int m_totalOptimizedLines;

    QMap<int, int> m_cycles;
    QMap<int, int> m_blockIndent;

    QVector<int> m_cycleCounter;
    QVector<int> m_blockCounter;

    void PushCounter();
    void PopCounter(int ln);

    void PushBlock(int ln);
    void PopBlock(int ln);

    virtual int getLineCount() {return m_source.count();}
    int CountCycles(QString s);
    virtual int CountInstructionCycle(QStringList s) {return 0;}

    void VarDeclEnds() {
        if (m_varDeclEndsLineNumber == 0) // Only assign if not previously
            m_varDeclEndsLineNumber = m_source.count();
    }

    QString getLabel(QString s) {
        return s+m_labelStack[s].m_current;
    }

    QString NewLabel(QString s) {
        m_labelStack[s].push();
        return s+m_labelStack[s].m_current;
    }

    void PopLabel(QString s) {
        m_labelStack[s].pop();
    }

    Assembler();
    void Save(QString filename);
    void Nl();
    void Write(QString str, int level=0);

    virtual void Program(QString name) = 0;
    virtual void EndProgram() = 0;
    virtual void VarDeclHeader() = 0;
    virtual void DeclareVariable(QString name, QString type, QString initVal)=0;
    virtual void DeclareString(QString name, QStringList initVal) {}
    virtual void DeclareArray(QString name, QString type, int count, QStringList lst, QString position) {}
    virtual void BeginBlock() = 0;
    virtual void EndBlock() = 0;
    virtual void AssignVariable(QString var) = 0;
    virtual void EndAssignVariable(QString var) {}
    virtual void ApplyTerm() = 0;
    virtual void Number(QString n) = 0;
    virtual QString  String(QStringList s) = 0;
    virtual void BinOP(TokenType::Type t)=0;
    virtual void Poke(bool start) = 0;
    virtual void Peek(bool start) {}
    virtual void Term(QString s, bool write=false);
    virtual void Comment(QString s) {}
    void Term();
    virtual void Writeln() = 0;
    virtual void EndWriteln() = 0;
    virtual void WriteBuiltinWriteln() {}
    virtual void StartPrint() {}
    virtual void Variable(QString s, bool isByte) {}
    void Appendix(QString s, int l);
    virtual void LoadVariable(QString var) {}
    void Connect();
    virtual QString StoreInTempVar(QString name, QString type="byte")  { return name;}
    virtual void StartForLoop(QString a, QString b) {}
    virtual void EndForLoop(QString endVal) {}
    void Asm(QString s, QString comment="");
    void Label(QString s);
    virtual void Optimise() {}
    void ClearTerm() {
        m_term = "";
    }
};

#endif // ASSEMBLER_H
