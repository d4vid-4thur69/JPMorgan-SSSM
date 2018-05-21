#include "StockMarket.h"

#include <ctime>
#include <stdexcept>

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

TEST(StockMarket, RecordTrade_Invalid)
{
	time_t timer;

	// No stocks created so stock symbols
	StockMarket::StockTrade* trade = new StockMarket::StockTrade("TEA", time(&timer), 200, StockMarket::BUY, 80);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Create stocks
	stockMarket->CreateStockMarketData();

	// Invalid stock symbol
	trade = new StockMarket::StockTrade("ZZZ", time(&timer), 200, StockMarket::BUY, 80);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid quantity Stocks::Minimum_General_Input-1 (0)
	trade = new StockMarket::StockTrade("TEA", time(&timer), Stocks::Minimum_General_Input-1, StockMarket::BUY, 20);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid quantity Stocks::Maximum_Transaction_Input+1
	trade = new StockMarket::StockTrade("TEA", time(&timer), (Stocks::Maximum_Transaction_Input+1), StockMarket::BUY, 20);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid price StockMarket::BUY, Stocks::Minimum_General_Input-1 (0)
	trade = new StockMarket::StockTrade("ALE", time(&timer), 200, StockMarket::BUY, Stocks::Minimum_General_Input-1);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid price  Stocks::Maximum_Price_Input+1
	trade = new StockMarket::StockTrade("ALE", time(&timer), 200, StockMarket::BUY, Stocks::Maximum_Price_Input+1);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid TradeKind _kind < BUY
	trade = new StockMarket::StockTrade("GIN", time(&timer), 200, -1, Stocks::Maximum_Price_Input+1);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;

	// Invalid TradeKind _kind > SELL
	trade = new StockMarket::StockTrade("GIN", time(&timer), 200, 2, Stocks::Maximum_Price_Input+1);
	CHECK_THROWS(out_of_range, stockMarket->RecordTrade(trade));
	delete trade;
}

TEST(StockMarket, RecordTrade_Valid)
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


// NB any trade record entered with a quantity zero in invalid.
// See StockTradeInvalid tests
TEST(StockMarket, CalculateVWSP)
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

	// Calculate for all TEA irrespective of timestamp
	DOUBLES_EQUAL(10.576923, stockMarket->CalculateVWSP("TEA",0,0), Value_Tolerance);
}

TEST(StockMarket, CalculateAllShareIndex)
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
