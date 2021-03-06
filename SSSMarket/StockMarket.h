#ifndef D_StockMarket_H
#define D_StockMarket_H

#include <vector>
#include <string>
#include <ctime>

#include "Stocks.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//  StockMarket is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////

class StockMarket
{
public:
	StockMarket();
	virtual ~StockMarket();

	enum TradeKind {BUY, SELL, LAST};
	struct StockTrade
	{
		string _sym;
		time_t _time;
		int _quantity;
		int _kind;
		int _price;

		StockTrade(string sym,time_t time,int quantity,int kind,int price)
		{
			 _sym=sym;
			 _time=time;
			 _quantity=quantity;
			 _kind=kind;
			 _price=price;
		}
	};

private:
	vector<Stocks*> _stock_market_data;
	vector<StockTrade*> _market_trading;

	bool StockTradeValid(StockTrade* trade);

public:
	int CreateStockMarketData(void);
	int GetMarketTradingNumber(void);
	void RecordTrade(StockTrade* trade);
	double CalculateVWSP(string symbol, time_t request_time, int period=300);
	double CalculateAllShareIndex(void);

	void PrintAllTradesToConsole(void);
	void PrintSubsettradesToConsole(vector<StockTrade*>* sub);
};

#endif  // D_StockMarket_H
