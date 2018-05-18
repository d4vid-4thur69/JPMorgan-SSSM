#include "StockMarket.h"

#include <iostream>
#include <ctime>
#include <numeric>
#include <cmath>

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
//  print trades
//
///////////////////////////////////////////////////////////////////////////////
void StockMarket::PrintSubsettradesToConsole(vector<StockTrade*>* sub)
{
	cout<<endl;
	for(unsigned i=0; i<_market_trading.size(); i++)
	{
		cout<<sub->at(i)->_sym << "\t";
		cout<<sub->at(i)->_time << "\t";
		cout<<sub->at(i)->_quantity << "\t";
		cout<<sub->at(i)->_kind << "\t";
		cout<<sub->at(i)->_price<<endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
//
//  return volume weighted stock price for selected stock and time window
//	use requested_time=0 for all trades
//
///////////////////////////////////////////////////////////////////////////////
double StockMarket::CalculateVWSP(string symbol, time_t request_time, int period)
{
	double VWSP = 0;
	int sum_trade_by_quantity = 0;
	int sum_quantity = 1;
	vector<StockTrade*> trading_by_symbol;
	vector<StockTrade*>::iterator it_market_trading =  _market_trading.begin();

	while(it_market_trading != _market_trading.end())
	{
		if( request_time != 0 )
		{
			if( (symbol== ((StockTrade*) *it_market_trading)->_sym)
				&& (request_time -((StockTrade*) *it_market_trading)->_time) < period )
			{
				trading_by_symbol.push_back((StockTrade*) *it_market_trading);
			}
		}
		else
		{
			if( (symbol== ((StockTrade*) *it_market_trading)->_sym) )
			{
				trading_by_symbol.push_back((StockTrade*) *it_market_trading);
			}
		}
		it_market_trading++;
	}

	unsigned symbol_trades = trading_by_symbol.size();

	if(symbol_trades>0)
	{
		sum_quantity = 0;

		for(unsigned i=0; i<symbol_trades; i++)
		{
			sum_trade_by_quantity += (trading_by_symbol.at(i)->_price * trading_by_symbol.at(i)->_quantity);
			sum_quantity += trading_by_symbol.at(i)->_quantity;
		}

		if( sum_trade_by_quantity > 0 )
		{
			VWSP = (double)sum_trade_by_quantity/sum_quantity;
		}
	}

	return VWSP;
}

///////////////////////////////////////////////////////////////////////////////
//
//  return all share index, uses all trades
//
///////////////////////////////////////////////////////////////////////////////
double StockMarket::CalculateAllShareIndex(void)
{
	double all_share_index = 0.0;
	string stock_symbol;

	vector<double> volume_weighted_sp;

	vector<Stocks*>::iterator it_stocks =  _stock_market_data.begin();

	// For each valid stock symbol, calculate Volume Weighted Stock Price
	while(it_stocks != _stock_market_data.end())
	{
		stock_symbol = ((Stocks*) *it_stocks)->GetSymbol();

		// All trades of stock type are factored into calculation when second argument is zero.
		double stock_vwsp = CalculateVWSP(stock_symbol, 0, 0);

		if(stock_vwsp!=0)
		{
			volume_weighted_sp.push_back(stock_vwsp);
		}

		it_stocks++;
	}

	// Require at least two Volume Weighted Stock Prices for accumulate()
	if(volume_weighted_sp.size()>1)
	{
		all_share_index = accumulate(volume_weighted_sp.begin(), volume_weighted_sp.end(), 1.0, multiplies<double>());
		all_share_index = pow(all_share_index, 1.0/volume_weighted_sp.size());
	}
	else if (volume_weighted_sp.size()==1)
	{
		all_share_index = volume_weighted_sp.at(0);
	}

	return all_share_index;
}
