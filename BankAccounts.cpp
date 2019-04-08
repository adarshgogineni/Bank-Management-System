#include "BankAccounts.h"
#include <iostream>
using namespace std;

//This is to withdraw money from the bank account.

bool BankAccount::withdraw(float money) {
    if (money > getBalance()) {
        return false;
    }
    else {
        setBalance(getBalance() - money);
        return true;
    }
}


//This Deposits money into the bank account.

float BankAccount::deposit(float money) {
    setBalance(getBalance() + money);
    return getBalance();
}


