#ifndef HEXVAL
#define HEXVAL

#include <QIntValidator>

class HexValidator : public QIntValidator
{
public:
	HexValidator(int nMin, int nMax, QObject *parent) : QIntValidator(nMin, nMax, parent)
	{
	}

	virtual QValidator::State validate(QString &input, int &pos) const
	{
		bool isOk;
		int nVal = input.toInt(&isOk, 16);
		QString sVal;

		if(input.isEmpty())
			return QValidator::Acceptable;

		if(!isOk)
			return QValidator::Invalid;
		
		sVal.setNum(nVal);

		return QIntValidator::validate(sVal, pos);
	}
};

#endif // HEXVAL