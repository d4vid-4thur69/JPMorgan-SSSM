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

const int Price_3 = 123;
const int Price_4 = 2334234;
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
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Create, OutOfRange)
{
	CHECK_THROWS(out_of_range, new Stocks("ALE", 2, 0, 0, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", -1, 0, 0, 0) );

	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, Stocks::Maximum_Last_Dividend+1, 0, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, -1, 100, 100) );

	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, Stocks::Maximum_Fixed_Dividend+1, 0) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, -1, 100) );

	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, 0, Stocks::Maximum_Par_Value+1) );
	CHECK_THROWS(out_of_range, new Stocks("ALE", 0, 0, 0, -1) );
}

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
//  test return values with those passed to constructor
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
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_2));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_6+1));

	DOUBLES_EQUAL(Comm_Div_Yield_3, stocks->CalculateDividendYield(Price_3), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_4, stocks->CalculateDividendYield(Price_4), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_5, stocks->CalculateDividendYield(Price_5), Value_Tolerance);
	DOUBLES_EQUAL(Comm_Div_Yield_6, stocks->CalculateDividendYield(Price_6), Value_Tolerance);
}

///////////////////////////////////////////////////////////////////////////////
//
//  test pe ratio function
//
//////////////////////////////////////////////////////////////////////////////
TEST(Stocks_Common, CalculatePERatio)
{
	CHECK_THROWS(out_of_range, stocks->CalculatePERatio(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculatePERatio(Price_2));
}

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
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_1));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_2));
	CHECK_THROWS(out_of_range, stocks->CalculateDividendYield(Price_6+1));

	DOUBLES_EQUAL(Pref_Div_Yield_3, stocks->CalculateDividendYield(Price_3), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_4, stocks->CalculateDividendYield(Price_4), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_5, stocks->CalculateDividendYield(Price_5), Value_Tolerance);
	DOUBLES_EQUAL(Pref_Div_Yield_6, stocks->CalculateDividendYield(Price_6), Value_Tolerance);
}
