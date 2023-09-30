#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>
#include "Transaction.h"
#include "Account.h"

using namespace std;

// Interface definition to be implemented by the 'Savings' class to compute its compund interest
class InterestEarning
{
public:
    virtual void computeInterest(int years) = 0; // Pure virtual function
};

// 'Savings' account which inherits from 'Account' and 'InterestEarning' defined
class Savings : protected Account, public InterestEarning
{
private:
    float interestRate;
    bool isa;
    string accountType;

public:
    vector <Transaction> history;

    // Constructor, accessors and overriden functions defined here
    Savings(bool ISA, float intrRate, double bal, int ID)
    {
        isa = ISA;
        interestRate = intrRate;
        balance = bal;
        accountID = ID;
    }
    void computeInterest(int years) // Overrides the pure virtual function from 'InterestEarning'
    {
        float projection = balance;
        cout << "The projected earnings for this account at " + to_string(interestRate) + "% interest rate." << endl;

        for (int i = 1; i <= years; i++)
        {
            projection = projection * pow((1 + interestRate / 100), years);
        }
        cout << "Projected Balance: £" + to_string(projection) << endl;
    }
    void deposit(string amount = "0")
    {
        double doub_amount = ::atof(amount.c_str());
        balance += doub_amount;

        Transaction transaction1;
        transaction1.Set_desc("Deposit");
        transaction1.Set_value(doub_amount);
        history.push_back(transaction1);

        cout << "$" << doub_amount << " have been successfully deposited into your account with ID: " << accountID << endl;
    }
    void toString()
    {
        if (isa)
        {
            accountType = "ISA";
        }
        else
        {
            accountType = "Savings";
        }

        cout << accountType << " account | account ID: " << accountID << " | Balance: $" << balance << " | Interest rate: "
            << interestRate << "%" << endl;
        for (Transaction i : history)
        {
            i.toString();
        }
    }
    void withdraw(string amount)
    {
        double doub_amount = ::atof(amount.c_str());

        if (balance - doub_amount >= 0)
        {
            balance -= doub_amount;

            Transaction transaction1;
            transaction1.Set_desc("Withdraw");
            transaction1.Set_value(doub_amount);
            history.push_back(transaction1);

            cout << "$" << doub_amount << " have been successfully withdrawn from your account with ID: " << accountID << endl;
        }
        else
        {
            cout << "You have insufficient funds" << endl;
        }
    }
    double Get_balance()
    {
        return balance;
    }
    int Get_accountID()
    {
        return accountID;
    }
};
