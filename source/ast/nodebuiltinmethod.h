#ifndef NODEBUILTINMETHOD_H
#define NODEBUILTINMETHOD_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"

class NodeBuiltinMethod : public Node {
public:
    QString m_procName;
    QVector<Node*> m_params;
    static QMap<QString, bool> m_isInitialized;

    NodeBuiltinMethod(QString m, QVector<Node*> params) {
        m_procName = m;
        m_params = params;
    }

    void Delete() override {
        for (Node* n: m_params) {
            n->Delete();
            delete n;
        }
    }

    QString Build(Assembler *as) override;
    void Poke(Assembler* as);
    void Peek(Assembler* as);
    void MemCpy(Assembler* as);
    void Rand(Assembler* as);
    void MoveTo(Assembler* as);
    void PokeScreen(Assembler* as, int hiAddress);
    void Fill(Assembler* as);
    void PrintNumber(Assembler* as);
    void PrintString(Assembler* as);
    void Scroll(Assembler* as);
    void BitOp(Assembler* as, int type);
    PVar Execute(SymbolTable* symTab, uint lvl) override;

    void IncScreenX(Assembler* as);

    void LoadVar(Assembler* as, int paramNo, QString register);
    void LoadVar(Assembler* as, int paramNo);
    void SaveVar(Assembler* as, int paramNo, QString register);
    void SaveVar(Assembler* as, int paramNo);

    void VerifyInitialized(QString method, QString initmethod);


    // Initialize
    void InitRandom(Assembler* as);
    void InitSinusTable(Assembler* as);
    void InitMoveto(Assembler *as);
    void InitEightBitMul(Assembler* as);
    void InitPrintString(Assembler* as);


    void ExecuteSym(SymbolTable* symTab) override {

    }
};


#endif // NODEBUILTINMETHOD_H
