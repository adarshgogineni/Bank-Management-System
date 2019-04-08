#ifndef PROJECT2_BANKACCOUNTS_H
#define PROJECT2_BANKACCOUNTS_H
#include "Accounts.h"

class BankAccount : public Account {

private:

public:

    BankAccount(float amount) :Account(amount) {};

    BankAccount() :Account() {};

    float deposit(float money);

    bool withdraw(float money);



};





#endif //PROJECT2_BANKACCOUNTS_H
