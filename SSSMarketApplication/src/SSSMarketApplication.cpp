//============================================================================
// Name        : SSSMarketApplication.cpp
// Author      : David Ashford
// Version     :
//============================================================================
#include "StockMarket.h"

#include <string>
#include <iostream>
using namespace std;

void DisplayOptions();
void AddTrade(StockMarket* market);

int main()
{
	bool exit = false;
	int option;
	time_t market_timer;
	struct tm* timeinfo;

	StockMarket* market = new StockMarket();
	market->CreateStockMarketData();

	DisplayOptions();

	while(!exit)
	{
		cin >> option;

		switch(option)
		{
		case 0: exit = true; break;
		case 1: AddTrade(market); break;
		case 2: exit = true; break;
		case 3: exit = true; break;
		case 4: exit = true; break;
		}

		time(&market_timer);
		timeinfo = localtime (&market_timer);
		cout << timeinfo->tm_hour<< timeinfo->tm_min <<timeinfo->tm_sec;
	}

	return 0;
}

void DisplayOptions()
{
	cout << endl;
	cout << "Main Menu\n";
	cout << "Select option\n";
	cout << "0 - exit\n";
	cout << "1 - Add Trade\n";
	cout << "2 - View trades\n";
	cout << "3 - Display Dividend Yield\n";
	cout << "4 - Display P/E Ratio\n";
	cout << "5 - Display Volume Weighted Stock Price\n";
	cout << "6 - Display All share Index\n";
	cout << endl;
}

void AddTrade(StockMarket* market)
{
	string symbol;
	time_t timer;
	int quantity=0;
	int buysell;
	int price=0;

	cout << "Add Trade Menu\n";
	cout << "Enter Stock Symbol: "; cin >> symbol;
	cout << "Enter Quantity: "; cin >> quantity;
	cout << "Enter Trade Buy-0 Sell-1: "; cin >> buysell;
	cout << "Enter Price: "; cin >> price;

	StockMarket::TradeKind trade_type;
	switch(buysell)
	{
		case 0: trade_type = StockMarket::BUY; break;
		case 1: trade_type = StockMarket::SELL; break;
	}

	StockMarket::StockTrade* trade = new StockMarket::StockTrade(symbol, time(&timer), quantity, trade_type, price);
	market->RecordTrade(trade);

	market->PrintAllTradesToConsole();

	DisplayOptions();
}