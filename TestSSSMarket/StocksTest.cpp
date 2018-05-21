#include "Stocks.h"

#include <string>
#include <stdexcept>
#include <iostream>

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

using namespace std;

// Set test variables
const string Smb_Common = "ABC";
const int Comm_L_Dividend = 12;
const int Comm_F_Dividend = 0;
const int Comm_P_Value = 100;

const double Value_Tolerance = 0.000001;

const int Price_1 = 0;
const int Price_2 = -1;
const double Comm_Div_Yield_Special = 0.0;

const int Price_3 = 1;
const int Price_4 = Stocks::Maximum_Price_Input-1;
const int Price_5 = 10000000;
const int Price_6 = Stocks::Maximum_Price_Input;

const double Comm_Div_Yield_3	= (double)Comm_L_Dividend/Price_3;
const double Comm_Div_Yield_4	= (double)Comm_L_Dividend/Price_4;
const double Comm_Div_Yield_5= (double)Comm_L_Dividend/Price_5;
const double Comm_Div_Yield_6= (double)Comm_L_Dividend/Price_6;

const string Smb_Preferred = "XYZ";
const int Pref_L_Dividend = 23;
const int Pref_F_Dividend = 4;
const int Pref_P_Value = 20;

const double Pref_Numerator = ((double)Pref_F_Dividend/100) * (double)Pref_P_Value;
const double Pref_Div_Yield_Special = 0.0;
const double Pref_Div_Yield_3 = Pref_Numerator/(double)Price_3;
const double Pref_Div_Yield_4 = Pref_Numerator/(double)Price_4;
const double Pref_Div_Yield_5 = Pref_Numerator/(double)Price_5;
const double Pref_Div_Yield_6 = Pref_Numerator/(double)Price_6;

const int PE_Dividend_1 = 15;
const int PE_Price_1 = 87;
const int PE_Price_2 = 100;
const int PE_Price_3 = 120;

const double PE_Ratio_1 = (double)PE_Price_1/(double)PE_Dividend_1;
const double PE_Ratio_2 = (double)PE_Price_2/(double)PE_Dividend_1;
const double PE_Ratio_3 = (double)PE_Price_3/(double)PE_Dividend_1;

TEST_GROUP(Stocks_Create)
{
  void setup()
  {

  }
  void teardown()
  {

  }
};

///////////////////////////////////////////////////////////////////////////////
//
//  constructor arguments range check
//	Stocks(...)
//		Arguments		Range
//		string symbol 	- not used in calculations
//		int type		- 0-1
//		int ldividend	- 0-Maximum_Last_Dividend (100000000)
//		int fdividend	- 0-Maximum_Fixed_Dividend (100000000)
//		int pvalue		- 0-Maximum_Par_Value (100000000)
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Create, OutOfRange)
{
	// type:
	CHECK_THROWS(out_of_range, new Stocks("ALE", 2, 0, 0, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", -1, 0, 0, 0) );

	// ldividend
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, Stocks::Maximum_Last_Dividend+1, 0, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, -1, 100, 100) );

	// fdividend
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, Stocks::Maximum_Fixed_Dividend+1, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, -1, 100) );

	// pvalue
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, 0, Stocks::Maximum_Par_Value+1) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, 0, -1) );
}

///////////////////////////////////////////////////////////////////////////////
//
//  create common stock
//
//////////////////////////////////////////////////////////////////////////////
TEST_GROUP(Stocks_Common)
{
  Stocks* stocks;

  void setup()
  {
    stocks = new Stocks(Smb_Common, 0, Comm_L_Dividend, Comm_F_Dividend, Comm_P_Value);
  }
  void teardown()
  {
    delete stocks;
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//  test GetXXXX() values with those passed to constructor
//
///////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Common, CheckInstanceCreated)
{
	CHECK_EQUAL(Smb_Common, stocks->GetSymbol());
	CHECK_EQUAL(Stocks::COMMON, stocks->GetType());

	LONGS_EQUAL(Comm_L_Dividend, stocks->GetLastDividend());
	LONGS_EQUAL(Comm_F_Dividend, stocks->GetFixedDividend());
	LONGS_EQUAL(Comm_P_Value, stocks->GetParValue());
}

///////////////////////////////////////////////////////////////////////////////
//
//  test dividend yield function, common
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Common, CalculateDividendYield)
{
	// Price cannot be zero or less, or above maximum
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_2));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_6+1));

	// Check boundary and valid values
	DOUBLES_EQUAL(Comm_Div_Yield_3, stocks->CalculateDividendYield(Price_3), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_4, stocks->CalculateDividendYield(Price_4), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_5, stocks->CalculateDividendYield(Price_5), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_6, stocks->CalculateDividendYield(Price_6), Value_Tolerance);
}

///////////////////////////////////////////////////////////////////////////////
//
//  test p/e ratio function
//	nb _last_dividend is checked in constructor so cannot be zero
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Common, CalculatePERatio)
{
	CHECK_THROWS(out_of_range, stocks->CalculatePERatio(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculatePERatio(Price_2));

	DOUBLES_EQUAL(Comm_Div_Yield_3, stocks->CalculateDividendYield(Price_3), Value_Tolerance);
}


///////////////////////////////////////////////////////////////////////////////
//
//  create preferred stock
//
//////////////////////////////////////////////////////////////////////////////
TEST_GROUP(Stocks_Preferred)
{
  Stocks* stocks;

  void setup()
  {
    stocks = new Stocks(Smb_Preferred, 1, Pref_L_Dividend, Pref_F_Dividend, Pref_P_Value);
  }
  void teardown()
  {
    delete stocks;
  }
};

///////////////////////////////////////////////////////////////////////////////
//
//  Compare return values with those passed to constructor
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Preferred, CheckInstanceCreated)
{
	CHECK_EQUAL(Smb_Preferred, stocks->GetSymbol());
	CHECK_EQUAL(Stocks::PREFERRED, stocks->GetType());

	LONGS_EQUAL(Pref_L_Dividend, stocks->GetLastDividend());
	LONGS_EQUAL(Pref_F_Dividend, stocks->GetFixedDividend());
	LONGS_EQUAL(Pref_P_Value, stocks->GetParValue());
}

///////////////////////////////////////////////////////////////////////////////
//
//  test dividend yield function, preferred
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Preferred, CalculateDividendYield)
{
	// Price cannot be zero or less, or above maximum
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_2));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_6+1));

	// Check boundary and valid values
	DOUBLES_EQUAL(Pref_Div_Yield_3, stocks->CalculateDividendYield(Price_3), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_4, stocks->CalculateDividendYield(Price_4), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_5, stocks->CalculateDividendYield(Price_5), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_6, stocks->CalculateDividendYield(Price_6), Value_Tolerance);
}
