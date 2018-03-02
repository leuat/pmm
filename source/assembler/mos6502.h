#ifndef MOS6502_H
#define MOS6502_H

#include "source/assembler/assembler.h"

class AsmMOS6502 : public Assembler
{
public:
    AsmMOS6502();

    QVector<int> m_removeLines;
    bool endTerm() {
        if (m_term.split(" ").count()==2)
            return true;
        return false;
    }
    QString byte = "dc.b";
    QString word = "dc.w";
    QString m_currentVar="";
//    QString m_currentLoopVar="";
    //int m_lblIdx = 0;
    QMap<QString, int> m_lblIdx;

    void Program(QString name) override;
    void EndProgram() override;
    void DeclareArray(QString name, QString type, int count, QStringList lst) override;


    void VarDeclHeader();
    void DeclareVariable(QString name, QString type) override;

    void BeginBlock() override;
    void EndBlock() override;
    void ApplyTerm() override;
    void Number(QString n) override;
    void String(QString s) override;
    void AssignVariable(QString v) override;
    void EndAssignVariable(QString variable) override;
    void BinOP(TokenType::Type t) override;
    void Poke(bool start) override;
    void Peek(bool start) override;

    void Writeln() override;
    void EndWriteln() override;
    void LoadVariable(QString var) override;

    void Variable(QString var) override;


    void WriteBuiltinWriteln();
    void StartPrint() override;


    void StartForLoop(QString a, QString b) override;
    void EndForLoop(QString endVal) override;

    void Optimise() override;
    void OptimisePassStaLda();
    QString getLine(int i);
    QString getNextLine(int i, int &j);
    QString getToken(QString, int t);
    void RemoveLines();
};


#endif // MOS6502_H
