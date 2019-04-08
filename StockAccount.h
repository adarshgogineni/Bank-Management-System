#ifndef PROJECT2_STOCKSACCOUNT_H
#define PROJECT2_STOCKSACCOUNT_H
#include "StockAccount.h"
#include "Accounts.h"
#include "BankAccounts.h"

//Class for stocks, allowing for finding the quantity as well as the symbol of the stock.

class Stocks {

public:

    Stocks() { symbol = ""; quantity = 0; }

    Stocks(string sym, int qnty);

    int getQuant();

    void setQuant (int quant);


    string getSymbol();
    void setSymbol(string symbol);



// Private variables for the stock symbol as well as the stock quanitity so they cannot be changed outside.
private:
    string symbol;

    int quantity;


};





class StockAccount : public Account {

public:

    StockAccount(float initial, string priceFileNames[], int n) ;

    void displayPortfolio() ;

    bool buyStk(string symbol, double buyPrice, int quantity) ;

    bool sellStk(string symbol, double sellPrice, int quantity) ;

    BankAccount getBankAccount();

    double getCurrPrice (string symbol, string &name) ;

    void close() ;

    bool withdraw(float money) ;

    void deposit(float money) ;

private:
    BankAccount bank;

    vector<Stocks> list;

    ifstream priceFiles[4];

    int files;

    double search (ifstream &file, string symbol, string &name) ;

    void add (string symbol, int quantity);

    bool dltstock(string symbol);

    int find(string symbol);

    bool stockh(string symbol);

    void fileprice(string *filenames, int a);

    void setBalance(float amount);




};








#endif //PROJECT2_STOCKSACCOUNT_H
