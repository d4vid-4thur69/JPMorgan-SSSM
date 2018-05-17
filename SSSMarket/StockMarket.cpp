#include "StockMarket.h"

#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
//  constructor
//
///////////////////////////////////////////////////////////////////////////////
StockMarket::StockMarket()
{
}

///////////////////////////////////////////////////////////////////////////////
//
//  clean up stocks and trades
//
///////////////////////////////////////////////////////////////////////////////
StockMarket::~StockMarket()
{
	for(unsigned i=0; i< _stock_market_data.size(); i++)
	{
		delete _stock_market_data[i];
	}
	_stock_market_data.clear();

	for(unsigned i=0; i< _market_trading.size(); i++)
	{
		delete _market_trading[i];
	}
	_market_trading.clear();
}

///////////////////////////////////////////////////////////////////////////////
//
//  create some stocks
//
///////////////////////////////////////////////////////////////////////////////
int StockMarket::CreateStockMarketData(void)
{
	_stock_market_data.push_back(new Stocks("TEA", Stocks::COMMON, 0, 0, 100));
	_stock_market_data.push_back(new Stocks("POP", Stocks::COMMON, 8, 0, 100));
	_stock_market_data.push_back(new Stocks("ALE", Stocks::COMMON, 23, 0, 60));
	_stock_market_data.push_back(new Stocks("GIN", Stocks::PREFERRED, 8, 2, 100));
	_stock_market_data.push_back(new Stocks("JOE", Stocks::COMMON, 13, 0, 250));

	return _stock_market_data.size();
}

///////////////////////////////////////////////////////////////////////////////
//
//  return number of trades
//
///////////////////////////////////////////////////////////////////////////////
int StockMarket::GetMarketTradingNumber(void)
{
	return _market_trading.size();
}

///////////////////////////////////////////////////////////////////////////////
//
//  store a valid trade
//
///////////////////////////////////////////////////////////////////////////////
void StockMarket::RecordTrade(StockMarket::StockTrade* trade)
{
	if (trade != NULL)
	{
		if(StockTradeValid(trade))
		{
			_market_trading.push_back(trade);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//  check trade is valid
//
///////////////////////////////////////////////////////////////////////////////
bool StockMarket::StockTradeValid(StockTrade* trade)
{
	bool trade_valid = false;

	vector<Stocks*>::iterator it_stocks =  _stock_market_data.begin();

	while(it_stocks != _stock_market_data.end())
	{
		// de-referrence iterator to check symbol string
		if( trade->_sym == ((Stocks*) *it_stocks)->GetSymbol() )
		{
			trade_valid = true;
			break;
		}
		it_stocks++;
	}

	return trade_valid;
}

///////////////////////////////////////////////////////////////////////////////
//
//  print trades
//
///////////////////////////////////////////////////////////////////////////////
void StockMarket::PrintAllTradesToConsole(void)
{
	cout<<endl;
	for(unsigned i=0; i<_market_trading.size(); i++)
	{
		cout<<_market_trading.at(i)->_sym << "\t";
		cout<<_market_trading.at(i)->_time << "\t";
		cout<<_market_trading.at(i)->_quantity << "\t";
		cout<<_market_trading.at(i)->_kind << "\t";
		cout<<_market_trading.at(i)->_price<<endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//  a biggie
//
///////////////////////////////////////////////////////////////////////////////
double CalcluateVolumeWeightedStockPrice()
{
	double volumeWSP = 0.0;

	return volumeWSP;
}

