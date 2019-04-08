#ifndef PROJECT2_ACCOUNT_H
#define PROJECT2_ACCOUNT_H

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <cctype>

//Create a class for the account


class Account {

public:
    Account() { cashbalance = 0; }
    Account(double money);

    // functions for the balance in the account.
    double getBalance();
    void setBalance(double amount);

// Private variable so that it cannot be changed outside of scope.
private:
    double cashbalance;



};

#endif //PROJECT2_ACCOUNT_H
