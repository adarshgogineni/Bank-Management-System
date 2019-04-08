#include "Accounts.h"
#include <iostream>
using namespace std;


//Sets the cash balance in the account and can be seen with the two functions below

Account::Account(double money) {

    cashbalance =  money;

}


// sets the balance

void Account::setBalance(double amount) {
    cashbalance = amount;
}

// so we can see the cash balance that is set
double Account::getBalance() {
    return cashbalance;
}

