#include "interpreter.h"

Interpreter::Interpreter(Parser p)
{
    m_parser = p;
}

void Interpreter::Parse()
{
    m_tree = nullptr;
    try {
        m_tree = m_parser.Parse();
    } catch (FatalErrorException e) {
        ErrorHandler::e.CatchError(e, "Error during parsing:");
    }

}

void Interpreter::Visit(Node* n)
{
    n->Execute(nullptr, 0);
}

void Interpreter::Interpret()
{
    if (m_tree!=nullptr)
        try {
        Visit(m_tree);
    } catch (FatalErrorException e) {
        ErrorHandler::e.CatchError(e, "Error during interpreting");
    }

}

void Interpreter::Build(Interpreter::Type type)
{
    if (m_tree==nullptr) {
        qDebug() << "Interpreter::Build : tree not parsed!";
        return;
    }
    if (m_assembler)
        delete m_assembler;

    if (type==MOS6502)
        m_assembler = new AsmMOS6502();
    if (type==PASCAL)
        m_assembler = new AsmPascal();

    if (m_tree!=nullptr)
        try {
        m_tree->Build(m_assembler);
    } catch (FatalErrorException e) {
        ErrorHandler::e.CatchError(e, "Error during interpreting");
    }

}

void Interpreter::SaveBuild(QString filename)
{
    if (!m_assembler)
        return;
    m_assembler->Save(filename);
}
