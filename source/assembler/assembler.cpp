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


    int cnt = CountCycles(s);
    for (int i=0;i<m_cycleCounter.count();i++)
        m_cycleCounter[i] += cnt;

}

void Assembler::PushCounter()
{
    m_cycleCounter.append(0);
}

void Assembler::PopCounter(int ln)
{
    int i = m_cycleCounter.last();
    m_cycleCounter.removeLast();
    if (i>m_cycles[ln]) // Only count largest number
       m_cycles[ln] = i;
 //   return i;
}

int Assembler::CountCycles(QString s)
{
    QStringList lst = s.split("\n");
    int n=0;
    for (QString s : lst) {
//        s=s.remove("\t");
        s=s.trimmed();
        if (s=="") continue;
        if (s.startsWith(";")) continue;
        int i = s.indexOf(";");
        if (i!=-1) { // Remove all comments
            s = s.remove(i, s.length());
        }
        //if (s[0]!="\t") continue; // is label
        QStringList l = s.split(" ");
        if (l[0].count()==3) {
            //qDebug() << "Adding :" << s;
            int cnt = CountInstructionCycle(l);
            n+=cnt;
//            if (cnt!=0) {
  //              qDebug() << "Counted for : '" <<s <<"' : " <<cnt;
    //        }
        }

    }
    return n;

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
    // Connect with temp vars
    QStringList newSource;
    for (int i=0;i<m_varDeclEndsLineNumber;i++) {
        newSource<<m_source[i];
    }
    newSource << " ; Temp vars section";
    newSource<< m_tempVars;
    newSource << " ; Temp vars section ends";
    for (int i=m_varDeclEndsLineNumber;i<m_source.count(); i++) {
        newSource<<m_source[i];
    }
    m_source = newSource;

    m_source<<m_appendix;
    m_appendix.clear();
}



QString Stack::current() const
{
    return m_current;
}

