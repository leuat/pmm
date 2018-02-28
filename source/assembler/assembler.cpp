#include "assembler.h"

Assembler::Assembler()
{
    m_symTab = new SymbolTable();
}

void Assembler::Save(QString filename) {
    if (QFile::exists(filename))
        QFile::remove(filename);

    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        for (QString& s: m_source)
            stream<< s<< "\n";
    }
    file.close();
}

void Assembler::Nl()
{
    m_source << "";
}

void Assembler::Write(QString str, int level)
{
    QString s ="";
    for (int i=0;i<level;i++)
        s+="\t";
    s+=str;
    m_source.append(s);
}

void Assembler::Asm(QString s)
{
    Write(s,1);
}

void Assembler::Label(QString s)
{
    Write(s,0);
}

void Assembler::Term(QString s, bool write)
{
    m_term+=s;
    if (write) {
        Asm(m_term);
        ClearTerm();

    }
}

void Assembler::Term()
{
    Asm(m_term);
    ClearTerm();
}



QString Stack::current() const
{
    return m_current;
}

