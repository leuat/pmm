#include "assembler.h"

//QMap<QString, bool> LabelStack::sNumbersUsed;

Assembler::Assembler()
{
  //  LabelStack::sNumbersUsed.clear();
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

void Assembler::Asm(QString s, QString comment)
{
    QString c = "\t;" + comment;
    if (comment=="") c="";
    Write(s+c ,1);
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

void Assembler::Appendix(QString str, int level)
{
    QString s ="";
    for (int i=0;i<level;i++)
        s+="\t";
    s+=str;
    m_appendix.append(s);

}

void Assembler::Connect()
{
    m_source<<m_appendix;
    m_appendix.clear();
}



QString Stack::current() const
{
    return m_current;
}

