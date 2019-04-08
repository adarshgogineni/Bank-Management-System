//Adarsh Gogineni RUID:171003252
#include "StockAccount.h"
#include "BankAccounts.h"
#include"Accounts.h"
#include <iostream>
using namespace std;

bool invnumb(string &value)
{
    if (value.find_first_not_of("0123456789.") != string::npos) {
        return true;
    }
    else
        return false;
}

string up(string str) {
    string a = "";
    for (int i = 0; i < str.size(); i++) {
        a.append(1, toupper(str[i]));
    }
    return a;
}

void transhist(fstream &file)
{
    string line;
    file.clear();
    file.seekg(0, ios::beg);

    while (!file.eof())
    {
        getline(file, line);
        cout << "\n\t" << line;
    }
    cout << endl;
}

void sMenu(StockAccount &account, istream &input, fstream &stockTransaction) {
    int choice, quantity;
    string symbol, company;
    double price, currentPrice;
    string data;
    time_t now;
    tm* ltime;
    while (true) {
        cout << "\n\t 1. Display current price for a stock symbol" << endl;
        cout << "\t 2. Buy stock" << endl;
        cout << "\t 3. Sell stock" << endl;
        cout << "\t 4. Display current portfolio" << endl;
        cout << "\t 5. Display transactions history" << endl;
        cout << "\t 6. Return to main menu" << endl;
        cout << "\t Your selection: ";

        input >> data;
        if (invnumb(data))
        {
            cout << "\tInput is invalid." << endl;
            continue;
        }
        else
            choice = atoi(data.c_str());

        if (choice == 1) {
            cout << "\n\tEnter a stock to check the price: ";
            input >> symbol;
            symbol = up(symbol);
            currentPrice = account.getCurrPrice(symbol, company);
            if (company.empty()) {
                cout << "\n\tThe symbol is invalid.\n";
            }
            else
            {
                now = time(0);
                ltime = localtime(&now);
                cout << "\n\t" << symbol << "\t" << company << "\t$" << currentPrice << "\t" << ltime->tm_hour << ":" << ltime->tm_min << ":" << ltime->tm_sec << endl;
            }
        }

        else if (choice == 2) {
            cout << "\n\tEnter Details to Purchase Stock: ";
            input >> symbol;
            symbol = up(symbol);
            input >> data;

            if (!invnumb(data)) {
                quantity = atoi(data.c_str());
                input >> data;
                if (invnumb(data)) {
                    cout << "\n\tInvalid Transaction." << endl;
                    continue;
                }
                else {
                    price = atof(data.c_str());
                }
            }
            else {
                cout << "\n\tInvalid Transaction." << endl;
                continue;
            }

            if (account.buyStk(symbol, price, quantity)) {
                now = time(0);
                ltime = localtime(&now);
                stockTransaction.clear();
                stockTransaction.seekp(0, ios::end);
                stockTransaction << "\tBuy" << "\t\t" << symbol << "\t\t" << quantity << "\t\t$" << price << "\t\t";
                stockTransaction << ltime->tm_hour << ":" << ltime->tm_min << ":" << ltime->tm_sec << endl;
            }
        }

        else if (choice == 3) {
            cout << "\n\tEnter sell options: ";
            input >> symbol;
            symbol = up(symbol);

            input >> data;
            if (!invnumb(data)) {
                quantity = atoi(data.c_str());
                input >> data;
                if (invnumb(data)) {
                    cout << "\n\tCannot process transaction" << endl;
                    continue;
                }
                else {
                    price = atof(data.c_str());
                }
            }
            else {
                cout << "\n\tCannot process transaction!" << endl;
                continue;
            }

            if (account.sellStk(symbol, price, quantity)) {
                now = time(0);
                ltime = localtime(&now);
                stockTransaction.clear();
                stockTransaction.seekp(0, ios::end);
                stockTransaction << "\tSell" << "\t\t" << symbol << "\t\t" << quantity << "\t\t$" << price << "\t\t";
                stockTransaction << ltime->tm_hour << ":" << ltime->tm_min << ":" << ltime->tm_sec << endl;

            }
        }

        else if (choice == 4) {
            account.displayPortfolio();
        }

        else if (choice == 5) {
            transhist(stockTransaction);
        }

        else if (choice == 6) {
            return;
        }
        else {
            cout << "\t Invalid choice!\n";
        }

    }

}

void bMenu(StockAccount &account, istream &input, fstream &bankTransaction) {
    int choice;
    double amount;
    string data;
    time_t now;
    tm* ltime;

    while (true) {
        cout << "\n\t 1. View account balance" << endl;
        cout << "\t 2. Deposit money" << endl;
        cout << "\t 3. Withdraw money" << endl;
        cout << "\t 4. Display transactions history" << endl;
        cout << "\t 5. Return to previous menu" << endl;
        cout << "\t Your selection: ";
        input >> data;
        if (invnumb(data)) {
            cout << "\tInvalid input" << endl;
            continue;
        }
        else
            choice = atoi(data.c_str());

        if (choice == 1) {
            account.displayPortfolio();
        }
        else if (choice == 2) {
            cout << "\n\tEnter amount to deposit: ";
            do {
                input >> data;
                if (invnumb(data)) {
                    cout << "\tInvalid input" << endl;
                    continue;
                }
                else
                    amount = atof(data.c_str());

                if (amount <= 0)
                    cout << "\n\t Enter a positive number for amount " << endl;
                else
                    break;
            } while (true);


            account.deposit(amount);
            cout << "\n\tDeposit $" << amount << " to bank account" << endl;

            account.displayPortfolio();
            bankTransaction << "\tDeposit" << "\t\t$" << amount << "\t\t$" << account.getBankAccount().getBalance() << "\t\t\t";
            now = time(0);
            ltime = localtime(&now);

            bankTransaction << ltime->tm_mday << "/" << ltime->tm_mon << "/" << (1900 + ltime->tm_year) << "\t\t";
            bankTransaction << ltime->tm_hour << ":" << ltime->tm_min << ":" << ltime->tm_sec << endl;

        }
        else if (choice == 3) {
            cout << "\n\tEnter amount to withdraw: ";
            do {
                input >> data;
                if (invnumb(data)) {
                    cout << "\tInvalid input" << endl;
                    continue;
                }
                else
                    amount = atof(data.c_str());

                if (amount <= 0)
                    cout << "\n\t Enter a positive number for amount" <<endl ;
                else
                    break;
            } while (true);

            if (account.withdraw(amount)) {
                cout << "\n\tWithdraw $" << amount << " from bank account" << endl;

                account.displayPortfolio();
                bankTransaction << "\tWithdraw" << "\t$" << amount << "\t\t$" << account.getBankAccount().getBalance() << "\t\t";
                now = time(0);
                ltime = localtime(&now);
                bankTransaction << ltime->tm_mday << "/" << ltime->tm_mon << "/" << (1900 + ltime->tm_year) << "\t\t";
                bankTransaction << ltime->tm_hour << ":" << ltime->tm_min << ":" << ltime->tm_sec << endl;
            }
            else {
                cout << "\n\t Invalid input\n";
            }
        }

        else if (choice == 4) {
            transhist(bankTransaction);
        }

        else if (choice == 5) {
            return;
        }
        else {
            cout << "\t Invalid choice\n";
        }
    }
}

void mainMenu(StockAccount &account, istream &input) {
    fstream bankTransaction("bank_transaction_history.txt", ios::in | ios::out | ios::trunc);
    fstream stockTransaction("stocks_transaction_history.txt", ios::in | ios::out | ios::trunc);
    if (!bankTransaction.is_open() || !stockTransaction.is_open()) {
        cout << "\n\tError creating transaction files." << endl;
        exit(1);
    }

    stockTransaction << "\tAction \t\tSymbol \t\tShares \t\tPrice \t\tTime\n";
    bankTransaction << "\tAction\t\tAmount\t\tCash Balance\t\tDate\t\t\tTime\n";

    cout << "\nWelcome to the Accounts Management System.";

    string data;
    int choice;

    while (true) {
        cout << "\n\tPlease select an account to access" << endl;

        cout << "\t1. Stocks Portfolio Accounts" << endl;
        cout << "\t2. Bank Accounts" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tYour selection: ";
        input >> data;
        if (invnumb(data)) {
            cout << "\n\t Invalid input!";
            continue;
        }
        else
            choice = atoi(data.c_str());

        if (choice == 1)
            sMenu(account, input, stockTransaction);

        else if (choice == 2)
            bMenu(account, input, bankTransaction);

        else if (choice == 3) {
            stockTransaction.close();
            bankTransaction.close();
            account.close();
            break;
        }
        else
            cout << "\n\tInvalid choice !" << endl;;
    }
}




int main(int argc, char *argv[])
{
    //stocks vector is found in the Stocks.h file and defined in Stocks.cpp
    string files[] = {"stock1.txt","stock2.txt","stock3.txt","stock4.txt"};
    //The text files are put into the cmake-build-debug folder

    StockAccount account(10000, files, 4);
    if (argc<2)
        mainMenu(account, cin);
    else {
        ifstream input(argv[1]);
        if (argc>1 && !input.is_open()) {
            cout << "Error opening file : " << argv[1] << endl;
            return -1;
        }
        mainMenu(account, input);
    }
    cout << "\n\tProgram terminated." << endl;
    return 0;
}


