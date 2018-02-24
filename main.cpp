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

        Lexer lexer = Lexer(text);
        Parser parser = Parser(lexer);

        Interpreter interpreter = Interpreter(parser);

        int result = interpreter.Interpret();
        qDebug() << result;
    }

}

QString ReadFile(QString fileName) {
    if (!QFile::exists(fileName)) {
        qDebug() << "Cannot open file: " << fileName;
        exit(1);
    }
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QString text = "";
    while(!in.atEnd()) {
        text += in.readLine() + "\n";
    }

    file.close();
    return text;

}


void ParseFile(QString fileName) {
    QString text = ReadFile(fileName);
    Lexer lexer = Lexer(text);
    Parser parser = Parser(lexer);
    Interpreter interpreter = Interpreter(parser);
    float result = interpreter.Interpret();
    qDebug() << result;
    qDebug() <<" a: " << Syntax::s.globals["a"];
    qDebug() <<" b: " << Syntax::s.globals["b"];
    qDebug() <<" c: " << Syntax::s.globals["c"];

}

int main(int argc, char *argv[])
{
    ParseFile("..\\test.pmm");

}
