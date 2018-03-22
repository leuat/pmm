#ifndef NODENUMBER_H
#define NODENUMBER_H


#include "source/token.h"
#include "source/pvar.h"
#include "source/symboltable.h"
#include "source/errorhandler.h"
#include "source/ast/node.h"


class NodeNumber : public Node {
public:
    float m_val;
    NodeNumber(Token op, int val) {
        m_op = op;
        m_val = val;
        if (m_op.m_type!=TokenType::ADDRESS)
            m_op.m_type = TokenType::INTEGER_CONST;

    }
    PVar Execute(SymbolTable* symTab, uint lvl) override;
    void ExecuteSym(SymbolTable* symTab) override {
    }

    bool isPureNumeric() override {
        return true;
    }

    void LoadVariable(Assembler* as) override {
        as->ClearTerm();
        as->Term("lda ");
        Build(as);
        as->Term();
    }

    QString HexValue() {
        return "$" + QString::number((int)m_val,16);
    }

    bool DataEquals(Node *other) override {
        NodeNumber* var = dynamic_cast<NodeNumber*>(other);
        if (var==nullptr)
            return false;
        return var->m_val == m_val;
    }



    QString StringValue() {
        QString val;
        if (m_op.m_type==TokenType::BYTE)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER_CONST)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::ADDRESS) {
            val = "$" + QString::number((int)m_val,16);
        }
        return val;
    }

    QString Build(Assembler *as) override {
        QString val = "";

        if (as->m_symTab->m_constants.contains(m_op.m_value)) {
            m_val = as->m_symTab->m_constants[m_op.m_value]->m_value->m_fVal;
        }


        if (m_op.m_type==TokenType::BYTE)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::INTEGER_CONST)
            val = "#"+QString::number((int)m_val);
        if (m_op.m_type==TokenType::ADDRESS) {

            val = "$" + QString::number((int)m_val,16);
        }

        if (m_op.m_type==TokenType::INTEGER_CONST && m_val>255) {
            as->Comment("Integer constant assigning");
            int hiBit = ((int)m_val)>>8;
            int loBit = ((int)m_val)&0xff;
            as->Asm("ldy #" + QString::number(hiBit) );
//            as->Asm("tax");
            as->Asm("lda #" + QString::number(loBit) );
            return val;

            //qDebug() << m_op.m_value <<":" << m_val << " : " << hiBit << "  , " << loBit;
            //exit(1);
        }

        if (as->m_term=="")
            as->Term("lda " + val);
        else
            as->Term(val);
        return val;
    }


};

#endif // NODENUMBER_H
