#include "StockAccount.h"
#include "BankAccounts.h"
#include "Accounts.h"
using namespace std;
#include <iostream>


StockAccount::StockAccount(float initial, string priceFileNames[], int n) :Account(initial)
{
    bank = BankAccount(initial);

    list = vector<Stocks>();

    fileprice(priceFileNames, n);
}

void StockAccount::setBalance(float amount)
{
    Account::setBalance(amount);

    bank.setBalance(amount);
}

bool StockAccount::sellStk(string symbol, double sellPrice, int quantity) {
    int idx = find(symbol);
    string name;
    double price;
    if (idx == -1) {
        cout << "\n\tCannot process transaction. No shares of " << symbol << " in portfolio." << endl << endl;
        return false;
    }
    if (list[idx].getQuant() < quantity) {
        cout << "\n\tCannot process transaction. Not enough shares of " << symbol << " in portfolio." << endl << endl;
        return false;
    }
    else {
        price = getCurrPrice(symbol, name);
        if (sellPrice > price) {
            cout << "\n\tCannot process transaction. Sell price  $" << sellPrice << " is greater than current price $" << price << endl << endl;
            return false;
        }
        else {
            double total = sellPrice * quantity;
            list[idx].setQuant(list[idx].getQuant() - quantity);
            setBalance(getBalance() + total);
            if (list[idx].getQuant() == 0) {
                dltstock(symbol);
            }
            return true;
        }
    }
}




void StockAccount::displayPortfolio() {
    double price, total, grandTotal = 0;
    string name;
    int qty;


    cout << "\n\tCash balance = $" << fixed << setprecision(2) << getBalance() << endl;
    cout << "\n\tSymbol\t\tCompany\t\t\t\t\tNumber\t\tPrice\t\tTotal" << endl << endl;


    for (int i = 0; i<list.size(); i++)
    {
        price = getCurrPrice(list[i].getSymbol(), name);
        qty = list[i].getQuant();
        total = price * qty;

        cout << "\t" << list[i].getSymbol() << "\t\t";
        cout.width(30);
        cout << left << name << "\t\t" << qty << "\t\t$" << price << "\t\t$" << total << endl;

        grandTotal += total;
    }


    grandTotal += getBalance();

    cout << "\n\n\tTotal value is: $" << grandTotal << endl;

}


bool StockAccount::buyStk(string symbol, double buyPrice, int quantity)
{
    string name;
    double price = getCurrPrice(symbol, name);
    double total = buyPrice * quantity;

    if (name.empty())
    {
        cout << "\n\tNo symbol found. Transaction unavailable. " << symbol << endl << endl;
        return false;
    }
    else if (buyPrice < price)
    {
        cout << "\n\tInvalid Transaction. Insufficient funds. " << endl;
        return false;
    }
    else if (total > getBalance())
    {
        cout << "\n\t Invalid transaction. Insufficient Funds" << endl << endl;
        return false;
    }
    else
        {
        add(symbol, quantity);
        setBalance(getBalance() - total);
        return true;
    }
}



void StockAccount::add(string symbol, int quantity) {
    int a = find(symbol);
    if (a == -1) {
        cout << " " << endl;
        Stocks s = Stocks(symbol, quantity);
        list.push_back(s);
    }
    else {
        list[a].setQuant(list[a].getQuant() + quantity);
    }
}

bool StockAccount::stockh(string symbol) {
    for (int i = 0; i<list.size(); i++) {
        if (list[i].getSymbol() == symbol) {
            return true;
        }
    }
    return false;
}

int StockAccount::find(string symbol){
    for (int i = 0; i<list.size(); i++) {
        if (list[i].getSymbol() == symbol) {
            return i;
        }
    }
    return -1;
}


bool StockAccount::dltstock(string symbol) {
    for (vector<Stocks>::iterator it = list.begin(); it != list.end(); ++it)
    {
        if ((*it).getSymbol() == symbol)
        {
            list.erase(it);

            return true;
        }
    }
    return false;
}

BankAccount StockAccount::getBankAccount()
{
    return bank;
}

double StockAccount::getCurrPrice(string symbol, string &name)
{
    int randomselection = rand() % files;

    return search(priceFiles[randomselection], symbol, name);

}


double StockAccount::search(ifstream &file, string symbol, string &name) {
    string sym;
    float price;
    string company;
    string line, token;

    file.clear();
    file.seekg(0, ios::beg);
    while (file >> sym)
    {
        if (sym != symbol)
            continue;

        company = "";

        while (file >> token)
        {
            if (token.find_first_not_of("0123456789.") != string::npos)
                company += " " + token;

            else
                {

                name = company;
                price = atof(token.c_str());
                return price;
            }
        }
    }
    name = "";
    return 0;
}

void StockAccount::fileprice(string *filenames, int a)
{
    files = a;
    srand(time(NULL));
    for (int i = 0; i<a; i++) {
        priceFiles[i].open(filenames[i].c_str());
        if (!priceFiles[i].is_open()) {
            cout << "\n\tError File" << filenames[i] << endl << endl;
            exit(1);
        }
    }
}

void StockAccount::close()
{
    for (int i = 0; i<files; i++) {
        priceFiles[i].close();
    }
}

void StockAccount::deposit(float money)
{
    setBalance(getBalance() + money);
}

bool StockAccount::withdraw(float money)
{
    if (bank.withdraw(money))
    {
        Account::setBalance(bank.getBalance());
        return true;
    }

    else {
        return false;
    }
}


Stocks::Stocks(string sym, int qnty)
{
    symbol = sym;
    quantity = qnty;
}

void Stocks::setQuant(int quant)
{

    quantity = quant;

}//function to set the quantity of the stock

int Stocks::getQuant() {

    return  quantity;

}//returns the quantity


std::string Stocks::getSymbol() {

    return symbol;

}//returns the symbol of the stock

void Stocks::setSymbol(std::string sym) {

    symbol = sym;

}//sets symbol