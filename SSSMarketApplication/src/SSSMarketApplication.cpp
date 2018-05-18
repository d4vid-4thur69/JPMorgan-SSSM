//============================================================================
// Name        : SSSMarketApplication.cpp
// Author      : David Ashford
// Version     :
//============================================================================
#include "StockMarket.h"

#include <string>
#include <iostream>
using namespace std;

void DisplayOptions(void);
void AddTrade(StockMarket* market);
void DisplayVWSP(StockMarket* market);
void ViewTrades(StockMarket* market);
void DisplayAllShareIndex(StockMarket* market);

int main(void)
{
	bool exit = false;
	int option;

	StockMarket* market = new StockMarket();
	market->CreateStockMarketData();

	DisplayOptions();

	while(!exit)
	{
		cout<<"Option: ";
		cin >> option;

		switch(option)
		{
		case 0: exit = true; break;
		case 1: AddTrade(market); break;
		case 2: ViewTrades(market); break;
		case 3: DisplayVWSP(market); break;
		case 4: DisplayAllShareIndex(market); break;
		}
	}

	return 0;
}

void DisplayOptions(void)
{
	cout << endl;
	cout << "Main Menu\n";
	cout << "Select option\n";
	cout << "0 - exit\n";
	cout << "1 - Add Trade\n";
	cout << "2 - View trades\n";
	cout << "3 - Display Volume Weighted Stock Price\n";
	cout << "4 - Display All share Index\n";
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

void DisplayVWSP(StockMarket* market)
{
	string symbol;
	int seconds;
	time_t timer;

	cout << "Volume Weighted Stock Price Menu\n";
	cout << "Enter Stock Symbol: "; cin >> symbol;
	cout << "Enter Window (Seconds): "; cin >> seconds;

	double VWSP = market->CalculateVWSP(symbol, time(&timer), seconds);

	cout << "Currently: " << VWSP << endl;

	DisplayOptions();
}

void ViewTrades(StockMarket* market)
{
	market->PrintAllTradesToConsole();

	DisplayOptions();
}

void DisplayAllShareIndex(StockMarket* market)
{

	cout << "All share Index Menu\n";

	double asi = market->CalculateAllShareIndex();

	cout << "Currently: " << asi << endl;

	DisplayOptions();
}
