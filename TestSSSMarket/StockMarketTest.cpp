#include "StockMarket.h"

#include <ctime>

//CppUTest includes should be after your and system includes
#include "CppUTest/TestHarness.h"

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

TEST(StockMarket, GetNumberTrades)
{
	LONGS_EQUAL(0, stockMarket->GetMarketTradingNumber());
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
	LONGS_EQUAL(1, stockMarket->GetMarketTradingNumber());
}

TEST(StockMarket, CalculateVWSP)
{
	FAIL("VWSP");
}


