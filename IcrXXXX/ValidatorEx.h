#ifndef HEXVAL
#define HEXVAL

#include <QIntValidator>

class ValidatorEx : public QIntValidator
{
	int m_nBase;

public:
	ValidatorEx(int nMin, int nMax, int nBase, QObject *parent) : QIntValidator(nMin, nMax, parent)
	{
		m_nBase = nBase;
	}

	virtual QValidator::State validate(QString &input, int &pos) const
	{
		bool isOk;
		int nVal = input.toInt(&isOk, m_nBase);
		QString sVal;

		if(input.indexOf(" ") != -1)
			return QValidator::Invalid;

		if(m_nBase == 10)
			return QIntValidator::validate(input, pos);

		if(input.isEmpty())
			return QValidator::Intermediate;

		if(!isOk)
		{
			if((m_nBase == 16) && (input == "0x"))
				return QValidator::Intermediate;
			else
				return QValidator::Invalid;
		}
		
		sVal.setNum(nVal);

		return QValidator::Acceptable;
	}
};

#endif // HEXVAL