#include "StockMarket.h"

#include <ctime>


//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

const double Value_Tolerance = 0.000001;

TEST_GROUP(StockMarket)
{
	StockMarket* stockMarket;

	void setup()
	{
		stockMarket = new StockMarket();
	}
	void teardown()
	{
		delete stockMarket;
	}
};

TEST(StockMarket, CreateStockMarketData)
{
	int stocks = stockMarket->CreateStockMarketData();
	LONGS_EQUAL(5, stocks);
}


TEST(StockMarket, RecordTrade)
{
	time_t timer;
	stockMarket->CreateStockMarketData();

	StockMarket::StockTrade* trade = new StockMarket::StockTrade("TEA", time(&timer), 200, StockMarket::BUY, 80);
	stockMarket->RecordTrade(trade);
	LONGS_EQUAL(1, stockMarket->GetMarketTradingNumber());

	trade = new StockMarket::StockTrade("ALE", time(&timer), 122, StockMarket::BUY, 49);
	stockMarket->RecordTrade(trade);
	LONGS_EQUAL(2, stockMarket->GetMarketTradingNumber());
}

TEST(StockMarket, StockTradeValid)
{
	time_t timer;

	// No stocks, no symbols
	StockMarket::StockTrade* trade = new StockMarket::StockTrade("TEA", time(&timer), 200, StockMarket::BUY, 80);
	stockMarket->RecordTrade(trade);
	LONGS_EQUAL(0, stockMarket->GetMarketTradingNumber());

	delete trade;

	stockMarket->CreateStockMarketData();

	// Invalid stock symbol
	trade = new StockMarket::StockTrade("ZZZ", time(&timer), 200, StockMarket::BUY, 80);
	stockMarket->RecordTrade(trade);
	LONGS_EQUAL(0, stockMarket->GetMarketTradingNumber());

	delete trade;

	// Valid stock symbol
	trade = new StockMarket::StockTrade("ALE", time(&timer), 200, StockMarket::BUY, 80);
	stockMarket->RecordTrade(trade);
	trade = new StockMarket::StockTrade("JOE", time(&timer), 200, StockMarket::BUY, 80);
	stockMarket->RecordTrade(trade);
	LONGS_EQUAL(2, stockMarket->GetMarketTradingNumber());
}

TEST(StockMarket, Calculate_VWSP)
{
	stockMarket->CreateStockMarketData();

	StockMarket::StockTrade* trade = new StockMarket::StockTrade("TEA", 1526570001, 20, StockMarket::BUY, 10);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("TEA", 1526570016, 30, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("GIN", 1526570017, 5, StockMarket::BUY, 15);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("JOE", 1526570018, 20, StockMarket::BUY, 20);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("JOE", 1526570019, 20, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("TEA", 1526570112, 2, StockMarket::BUY, 100);
	stockMarket->RecordTrade(trade);

	trade = new StockMarket::StockTrade("JOE", 1526570217, 5, StockMarket::BUY, 50);
	stockMarket->RecordTrade(trade);

	DOUBLES_EQUAL(10.9375, stockMarket->CalculateVWSP("TEA",1526570310,300), Value_Tolerance);
	DOUBLES_EQUAL(16.666666, stockMarket->CalculateVWSP("JOE",1526570300,300), Value_Tolerance);
	DOUBLES_EQUAL(15.0, stockMarket->CalculateVWSP("GIN",1526570300,300), Value_Tolerance);

	DOUBLES_EQUAL(10.576923, stockMarket->CalculateVWSP("TEA",0,0), Value_Tolerance);
}

TEST(StockMarket, All_Share_Index)
{
	stockMarket->CreateStockMarketData();

	// No trades so should equal zero
	DOUBLES_EQUAL(0, stockMarket->CalculateAllShareIndex(), Value_Tolerance);

	StockMarket::StockTrade* trade = new StockMarket::StockTrade("TEA", 1526570001, 10, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);
	trade = new StockMarket::StockTrade("TEA", 1526570016, 10, StockMarket::BUY, 10);
	stockMarket->RecordTrade(trade);
	trade = new StockMarket::StockTrade("TEA", 1526570017, 20, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);
	DOUBLES_EQUAL(6.25, stockMarket->CalculateAllShareIndex(), Value_Tolerance);


	trade = new StockMarket::StockTrade("GIN", 1526570001, 10, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);
	trade = new StockMarket::StockTrade("GIN", 1526570016, 10, StockMarket::BUY, 10);
	stockMarket->RecordTrade(trade);
	trade = new StockMarket::StockTrade("GIN", 1526570017, 20, StockMarket::BUY, 5);
	stockMarket->RecordTrade(trade);

	DOUBLES_EQUAL(6.25, stockMarket->CalculateAllShareIndex(), Value_Tolerance);
}

