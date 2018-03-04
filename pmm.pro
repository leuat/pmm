#QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

TARGET = pmm
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    source\data_pmm.cpp \
    source\token.cpp \
    source\lexer.cpp \
    source\syntax.cpp \
    source\ast\ast.cpp \
    source\interpreter.cpp \
    source\symboltable.cpp \
    source\errorhandler.cpp \
    source\pvar.cpp \
    source\parser.cpp \
    source/ast/node.cpp \
    source/ast/nodebinop.cpp \
    source/ast/nodenumber.cpp \
    source/ast/nodestring.cpp \
    source/ast/nodeunaryop.cpp \
    source/ast/nodecompound.cpp \
    source/ast/nodevar.cpp \
    source/ast/nodeassign.cpp \
    source/ast/nodevardecl.cpp \
    source/ast/nodeblock.cpp \
    source/ast/nodeprogram.cpp \
    source/ast/nodevartype.cpp \
    source/ast/nodeproceduredecl.cpp \
    source/ast/nodeprocedure.cpp \
    source/ast/nodeconditional.cpp \
    source/ast/nodeforloop.cpp \
    source/ast/nodebuiltinmethod.cpp \
    source/assembler/mos6502.cpp \
    source/assembler/assembler.cpp \
    source/assembler/asmpascal.cpp \
    source/ast/nodewhileloop.cpp \
    source/ast/nodevararray.cpp \
    source/ast/nodeasm.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    source\data_pmm.h \
    source\token.h \
    source\lexer.h \
    source\syntax.h \
    source\ast\ast.h \
    source\interpreter.h \
    source\symboltable.h \
    source\errorhandler.h \
    source\pvar.h \
    source\parser.h \
    source/ast/node.h \
    source/ast/nodebinop.h \
    source/ast/nodenumber.h \
    source/ast/nodestring.h \
    source/ast/nodeunaryop.h \
    source/ast/nodecompound.h \
    source/ast/nodevar.h \
    source/ast/nodeassign.h \
    source/ast/nodevardecl.h \
    source/ast/nodeblock.h \
    source/ast/nodeprogram.h \
    source/ast/nodevartype.h \
    source/ast/nodeproceduredecl.h \
    source/ast/nodeprocedure.h \
    source/ast/nodeconditional.h \
    source/ast/nodeforloop.h \
    source/ast/nodebuiltinmethod.h \
    source/assembler/mos6502.h \
    source/assembler/assembler.h \
    source/assembler/asmpascal.h \
    source/ast/nodewhileloop.h \
    source/ast/nodevararray.h \
    source/ast/nodeasm.h
