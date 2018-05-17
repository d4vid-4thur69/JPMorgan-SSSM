#ifndef D_Stocks_H
#define D_Stocks_H

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//  Stocks is responsible for defining required market stock's parameters
//
///////////////////////////////////////////////////////////////////////////////
class Stocks
{
public:
	static const int Maximum_Price	= 2147483647;
	enum StockType{COMMON, PREFERRED, LAST};
	Stocks(string symbol="", StockType type=COMMON, int ldividend=0, int fdividend=0, int pvalue=100);

private:
	string _symbol;
	StockType _stock_type;
	int _last_dividend;
	int _fixed_dividend;
	int _par_value;

public:
	string GetSymbol(void) const;
	StockType GetType(void) const;
	int GetLastDividend(void) const;
	int GetFixedDividend(void) const;
	int GetParValue(void) const;

	double CalculateDividendYield(int price);
	double CalculatePERatio(int price);
};

#endif  // D_Stocks_H
