#include "Stocks.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//  constructor
//
///////////////////////////////////////////////////////////////////////////////
Stocks::Stocks(string symbol, int type, int ldividend, int fdividend, int pvalue)
{
	if(type>PREFERRED || type<0)
	{
		throw out_of_range("_stock_type out of range");
	}

	if(ldividend>Maximum_Last_Dividend || ldividend<0)
	{
		throw out_of_range("_last_dividend out of range");
	}

	if(fdividend>Maximum_Fixed_Dividend || fdividend<0)
	{
		throw out_of_range("_fixed_dividend out of range");
	}

	if(pvalue>Maximum_Par_Value || pvalue<0)
	{
		throw out_of_range("_par_value out of range");
	}

	_symbol=symbol;

	switch(type)
	{
	case 0: _stock_type = COMMON; break;
	case 1: _stock_type = PREFERRED; break;
	}

	_last_dividend=ldividend;
	_fixed_dividend=fdividend;
	_par_value=pvalue;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return stock symbol
//
///////////////////////////////////////////////////////////////////////////////
string Stocks::GetSymbol(void) const
{
	return _symbol;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return stock type
//
///////////////////////////////////////////////////////////////////////////////
Stocks::StockType Stocks::GetType(void) const
{
	return _stock_type;
}

int Stocks::GetLastDividend(void) const
{
	return _last_dividend;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return stock fixed dividend
//
///////////////////////////////////////////////////////////////////////////////
int Stocks::GetFixedDividend(void) const
{
	return _fixed_dividend;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return stock par value
//
///////////////////////////////////////////////////////////////////////////////
int Stocks::GetParValue(void) const
{
	return _par_value;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Two calculation for dividend yield
//
///////////////////////////////////////////////////////////////////////////////
double Stocks::CalculateDividendYield(int price)
{
	double dy = 0.0;

	if( price<1 || (price>Maximum_Price_Input))
	{
		throw out_of_range("CalculateDividendYield price");
	}

	switch(_stock_type)
	{
		case COMMON: dy = (double)_last_dividend/price; break;
		case PREFERRED:
			dy = (double)_fixed_dividend/100;
			dy  =(double)dy*_par_value;
			dy = (double)dy/price;
			break;
		default: break;
	}

	return dy;
}

///////////////////////////////////////////////////////////////////////////////
//
//  Return PE ratio
//
///////////////////////////////////////////////////////////////////////////////
double Stocks::CalculatePERatio(int price)
{
	double pe = 0.0;

	if( price<1 || (price>Maximum_Price_Input))
	{
		throw out_of_range("CalculateDividendYield price");
	}

	pe = price/_last_dividend;


	return pe;
}

