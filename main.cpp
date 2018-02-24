#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>

#include "interpreter.h"
#include "lexer.h"
#include "ast.h"
#include <QFile>
#include <QTextStream>

void TestSingleLine() {
    QTextStream s(stdin);
    QString text = "";
    while (text!="q") {
        text = s.readLine();
        QStringList lst;
        Lexer lexer = Lexer(text, lst);
        Parser parser = Parser(lexer);

        Interpreter interpreter = Interpreter(parser);

        int result = interpreter.Interpret();
        qDebug() << result;
    }

}

QString ReadFile(QString fileName, QStringList& lst) {
    if (!QFile::exists(fileName)) {
        qDebug() << "Cannot open file: " << fileName;
        exit(1);
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QString text = "";
    while(!in.atEnd()) {
        QString t = in.readLine();
        text += t;
        lst<<t;
    }

    file.close();
    return text;

}


void ParseFile(QString fileName) {
    QStringList lst;
    QString text = ReadFile(fileName, lst);
    Lexer lexer = Lexer(text, lst);
    Parser parser = Parser(lexer);
    Interpreter interpreter = Interpreter(parser);
    float result = interpreter.Interpret();
    qDebug() << result;
    qDebug() <<" a: " << Syntax::s.globals["a"];
    qDebug() <<" b: " << Syntax::s.globals["b"];
    qDebug() <<" c: " << Syntax::s.globals["y"];

}

int main(int argc, char *argv[])
{
    ParseFile("..\\test.pmm");

}
