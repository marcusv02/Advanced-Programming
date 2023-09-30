#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>
#include "Transaction.h"

using namespace std;

// Parent abstract class 'Account' is defined and to be inherited into 'Current' and 'Savings'
class Account
{
protected: // Only accessible to child classes
    int accountID;
    double balance;

    // Pure virtual functions defined
    virtual void deposit(string amount) = 0;
    virtual void toString() = 0;
    virtual void withdraw(string amount) = 0;
    virtual double Get_balance() = 0;
    virtual int Get_accountID() = 0;
};
