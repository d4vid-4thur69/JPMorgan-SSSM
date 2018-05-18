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

	// Setting all to same value
	static const int Maximum_Price_Input	= 100000000;
	static const int Maximum_Transaction_Input	= 100000000;
	static const int Maximum_Last_Dividend	= 100000000;

	// Numerator of a percentage
	static const int Maximum_Fixed_Dividend	= 100000000;
	static const int Maximum_Par_Value	= 100000000;

	enum StockType{COMMON, PREFERRED};
	Stocks(string symbol="", int type=COMMON, int ldividend=0, int fdividend=0, int pvalue=100);

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
