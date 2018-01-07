#ifndef BNA_H
#define BNA_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QMap>

enum BNABit{
    B_0 = 0x00,
    B_1 = 0x01
};

void BNAConvertHEXStringToVBool(QString &in, QVector<BNABit> &vars, int size);
void BNAConvertArrayToVBool(QByteArray &in, QVector<BNABit> &vars, int size);
QString BNAConvertVBoolHEXString(QVector<BNABit> &vars);

// -----------------------------------------------------------------

class BNAVar{
    public:
        BNAVar();
        QString name();
        void name(QString name);
        BNABit val();
        void val(BNABit bVal);
    private:
        BNABit m_bVal;
        QString m_sName;
};

// -----------------------------------------------------------------

class IBNAOper {
    public:
        virtual QString type() = 0;
        virtual BNABit calc(BNABit b1, BNABit b2) = 0;
};

// -----------------------------------------------------------------

class BNAOperXor : public IBNAOper{
    public:
        virtual QString type();
        virtual BNABit calc(BNABit b1, BNABit b2);
};

// -----------------------------------------------------------------

class BNAOperNotXor : public IBNAOper{
    public:
        virtual QString type();
        virtual BNABit calc(BNABit b1, BNABit b2);
};

// -----------------------------------------------------------------

class BNAOperAnd : public IBNAOper {
    public:
        virtual QString type();
        virtual BNABit calc(BNABit b1, BNABit b2);
};

// -----------------------------------------------------------------

class BNAOperOr : public IBNAOper {
    public:
        virtual QString type();
        virtual BNABit calc(BNABit b1, BNABit b2);
};

// -----------------------------------------------------------------

class BNAExpr{
    public:
        BNAExpr();
        void op1(BNAVar *pVar1);
        BNAVar *op1();
        void op2(BNAVar *pVar2);
        BNAVar *op2();
        void oper(IBNAOper *pOper);
        IBNAOper *oper();
        void out(BNAVar *pVarOut);
        BNAVar *out();
        void exec();

    private:
        BNAVar *m_pVar1;
        BNAVar *m_pVar2;
        BNAVar *m_pVarOut;
        IBNAOper *m_pOper;
};

// -----------------------------------------------------------------

class BNAItem{
    public:
        BNAItem(unsigned short x, unsigned short y, unsigned char t);
        BNAItem();
        unsigned short getX();
        unsigned short getY();
        unsigned char getT();

        void setX(unsigned short x);
        void setY(unsigned short y);
        void setT(unsigned char t);

        void readXYT(QDataStream &stream);
        void writeXYT(QDataStream &stream);

    private:
        unsigned short m_nX;
        unsigned short m_nY;
        unsigned char m_cT;
};

// -----------------------------------------------------------------

class BNA {
	public:
		BNA();
        ~BNA();
		bool load(QString filename);
		bool save(QString filename);
		void randomGenerate(int nInput, int nOutput, int nSize);
		bool exportToDot(QString filename, QString graphname);
		bool exportToCpp(QString filename, QString funcname);
        QByteArray exportToByteArray();
        void importFromByteArray(QByteArray data);
		QJsonObject toJson();
        void generateRandomMutations(int nRandomCicles);
        void appendRandomData(int nRandomCicles);
        BNABit calc(const QVector<BNABit> &vInputs, int nOutput);


        unsigned int inputCount();
        unsigned int outputCount();
        void compare(BNA &bna);
	private:

		unsigned int m_nInput;
		unsigned int m_nOutput;
        void readFromStream(QDataStream &stream);
        void writeToStream(QDataStream &stream);

        QVector<IBNAOper *> m_vOpers;
        int m_nOperSize;

        void clearResources();
        void normalize();
        QVector<BNAItem *> m_vItems;
        QVector<BNAExpr *> m_vCalcExprs;
        QVector<BNAVar *> m_vCalcVars;
        QVector<BNAVar *> m_vCalcOutVars;

};

// -----------------------------------------------------------------

class BNAMemoryItem {
    public:
        BNAMemoryItem();
        QByteArray input;
        QByteArray output;
        const QVector<BNABit> &inputToVectorBool();
        const QVector<BNABit> &outputToVectorBool();

    private:
        QVector<BNABit> m_vInput;
        QVector<BNABit> m_vOutput;
};

// -----------------------------------------------------------------

class BNAMemory {
    public:
        BNAMemory();
        void load(QString filename);
        void save(QString filename);
        int size();
        BNAMemoryItem at(int i);
        void printData();
        void generateData(int nCount);
        void dataFrom(const QVector<QString> &vStrigns);
    private:
        QString alphabet();
        QString generateRandomString();
        int m_nInputSize;
        int m_nOutputSize;
        QVector<BNAMemoryItem> m_vItems;
};

// -----------------------------------------------------------------

class BNAProject {

    public:
        BNAProject();
        bool open(QString sDirPath);

    private:
        QString m_sDirPath;
};


#endif // BNA_H