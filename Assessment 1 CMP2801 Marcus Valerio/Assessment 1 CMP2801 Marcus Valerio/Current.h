#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>
#include "Transaction.h"
#include "Account.h"

using namespace std;

// 'Current' class defined, inherits from the 'Account' abstract class
class Current : protected Account
{
private:
    double overdraft = 500;

public:
    vector <Transaction> history;

    // Constructor, overriden functions and accessors defined here
    Current(double bal, int ID)
    {
        balance = bal;
        accountID = ID;
    }
    void deposit(string amount = "0")
    {
        double doub_amount = ::atof(amount.c_str());
        bool goAhead = false;

        if (overdraft < 500)
        {
            if (overdraft + doub_amount > 500)
            {
                balance += (overdraft + doub_amount) - 500;
                overdraft = 500;
                goAhead = true;
            }
            else
            {
                overdraft += doub_amount;
                goAhead = true;
            }
        }
        else
        {
            balance += doub_amount;
            goAhead = true;
        }

        if (goAhead)
        {
            Transaction transaction1;
            transaction1.Set_desc("Deposit");
            transaction1.Set_value(doub_amount);
            history.push_back(transaction1);

            cout << "$" << doub_amount << " have been successfully deposited into your account with ID: " << accountID << endl;
        }
    }
    void toString()
    {
        cout << "Current account | account ID: " << accountID << " | Balance: $" << balance << " | Overdraft: $"
            << overdraft << endl;
        for (Transaction i : history)
        {
            i.toString();
        }
    }
    void withdraw(string amount)
    {
        double doub_amount = ::atof(amount.c_str());
        bool goAhead = false;

        if (balance - doub_amount >= 0)
        {
            balance -= doub_amount;
            goAhead = true;
        }
        else if (balance - doub_amount >= -500 && overdraft - doub_amount >= 0)
        {
            overdraft += balance - doub_amount;
            balance = 0;
            goAhead = true;
        }
        else
        {
            cout << "You have insufficient funds." << endl;
        }

        // Deposit will only go ahead if there are sufficient funds
        if (goAhead)
        {
            Transaction transaction1;
            transaction1.Set_desc("Withdraw");
            transaction1.Set_value(doub_amount);
            history.push_back(transaction1);

            cout << "$" << doub_amount << " have been successfully withdrawn from your account with ID: " << accountID << endl;
        }
    }
    double Get_balance()
    {
        return balance;
    }
    double Get_overdraft()
    {
        return overdraft;
    }
    int Get_accountID()
    {
        return accountID;
    }
};
