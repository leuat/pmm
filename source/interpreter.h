#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"
#include "source/assembler/mos6502.h"
#include "source/assembler/asmpascal.h"

class Interpreter
{
public:
    Node* m_tree = nullptr;
    enum Type{PASCAL, MOS6502};
    Assembler* m_assembler = nullptr;
    Parser m_parser;
    Interpreter(Parser p);
    void Parse();
    void Visit(Node* n);
    void Interpret();
    bool Build(Type);
    void SaveBuild(QString filename);
    void HandleError(FatalErrorException fe, QString se);
};

#endif // INTERPRETER_H
