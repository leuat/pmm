#include "interpreter.h"

Interpreter::Interpreter(Parser* p)
{
    m_parser = p;
}

void Interpreter::Parse()
{
    m_tree = nullptr;
    qDebug() << "Parsing..";
    try {

        m_tree = m_parser->Parse();
    } catch (FatalErrorException e) {
        qDebug() << "ERROR parse " << e.message;
        HandleError(e, "Error during parsing:");
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

    }

}

bool Interpreter::Build(Interpreter::Type type, QString project_dir)
{
    if (m_tree==nullptr) {
        qDebug() << "Interpreter::Build : tree not parsed!";
        return false;
    }
    if (m_assembler)
        delete m_assembler;

    if (type==MOS6502)
        m_assembler = new AsmMOS6502();
    if (type==PASCAL)
        m_assembler = new AsmPascal();

    m_assembler->m_projectDir = project_dir;

    if (m_tree!=nullptr)
        try {
            m_tree->Build(m_assembler);
        } catch (FatalErrorException e) {
            HandleError(e,"Error during build");
            return false;
         }
        try {
           // m_tree->ExecuteSym(m_assembler->m_symTab);
        } catch (FatalErrorException e) {
            HandleError(e,"Error during symbolic check");
            return false;
    }
    m_assembler->Connect();
    m_assembler->Optimise();
    return true;

}

void Interpreter::SaveBuild(QString filename)
{
    if (!m_assembler)
        return;
    m_assembler->Save(filename);
}

void Interpreter::HandleError(FatalErrorException fe, QString e)
{
    QString msg = "";
    QString line = "on line: " + QString::number(fe.linenr+1);
    msg +="\nFatal error " + line;
    if (fe.linenr<m_parser->m_lexer->m_lines.count())
        msg+="\nSource: " + m_parser->m_lexer->m_lines[fe.linenr];
    msg+="\n\nMessage: ";
    Pmm::Data::d.lineNumber = fe.linenr+1;

    ErrorHandler::e.CatchError(fe, e + msg);

}
