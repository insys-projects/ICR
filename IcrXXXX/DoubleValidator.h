#ifndef DBLVAL
#define DBLVAL

#include <QDoubleValidator>

class DoubleValidator : public QDoubleValidator
{
	double m_dMin;
	double m_dMax;
	int    m_nDec;
	int	   m_nPos;

public:
	DoubleValidator(double bottom, double top, int decimals, QObject *parent) : QDoubleValidator(bottom, top, decimals, parent)
	{
		m_dMin = bottom;
		m_dMax = top;
		m_nDec = decimals;
		m_nPos = -1;
	}

	virtual QValidator::State validate(QString &input, int &pos) const
	{
		bool   isOk;
		double dVal = input.toDouble(&isOk);
		
		if(input.isEmpty())
			return QValidator::Acceptable;

		if((m_dMin >= 0) && (m_dMax >= 0))
		{
			if(!isOk)
				return QValidator::Invalid;
			else if(dVal < 0)
				return QValidator::Invalid;
			else if(dVal > m_dMax)
				return QValidator::Invalid;
		}
		else if((m_dMin < 0) && (m_dMax < 0))
		{
			if((input != "-") && (!isOk))
				return QValidator::Invalid;
			else if((dVal >= 0) && (input != "-"))
				return QValidator::Invalid;
			else if(dVal < m_dMin)
				return QValidator::Invalid;
		}
		else if((m_dMin < 0) && (m_dMax >= 0))
		{
			if((input != "-") && (!isOk))
				return QValidator::Invalid;
			else if((dVal < 0) && (dVal < m_dMin))
				return QValidator::Invalid;
			else if((dVal > 0) && (dVal > m_dMax))
				return QValidator::Invalid;
		}

		if(input.indexOf(".") != -1)
			if(input.split(".")[1].size() > m_nDec)
				return QValidator::Invalid;
		
		return QValidator::Acceptable;
	}
};

#endif // DBLVAL