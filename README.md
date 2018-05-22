# JPMorgan SuperSimpleStockMarket Assignment

# Notes
## Build Details
### Operating System
Ubuntu 14.04 LTS
### IDE
Eclipse Version: Oxygen.2 Release (4.7.2)
### C++
gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04.4) 
### TDD CppUTest
Release 3.8

# Project Assumptions
## Data

### Symbol for Stock and Trade
C++ <string> no checking, assume UI will do this. Simply compare trade symbol with stocks symbols.
### Stock
Type, Last Dividend, Fixed Dividend and Par Value all Ints (4 bytes), with maxima and minima.
### Trade
Quantity, buy/sell and Price are all Ints (4 bytes), with maxima and minima.
Timestamp C++ <ctime> seconds since 1970.
### Calculations
Dividend Yield, P/E Ratio, Volume Weighted Stock Price and All Share Index are doubles.

# Projects
## CppUTest
Test harness include files and libraries.
## SSSMarket
Static library, Stocks and StockMarket classes.
## SSSMarketApplication
Simple command line test interface.
## TestSSSMarket
TDD framework, testing boundary values and exceptions.

# Notes
If using eclipse you have to manually import the four projects.
CppUTest need no compiling.

SSSMarket, SSSMarketApplication and TestSSSMarket require a refresh to create Debug folders.
Build SSSMarket first, then re-index SSSMarketApplication and TestSSSMarket before building.


