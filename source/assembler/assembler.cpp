#include "assembler.h"

Assembler::Assembler()
{

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



QString Stack::current() const
{
    return m_current;
}

