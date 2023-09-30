// All files to be included are defined at the top
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>
#pragma once
#include "Transaction.h"
#include "Account.h"
#include "Current.h"
#include "Savings.h"

using namespace std; // The standard namepace library is used to 'std::' doesn't have to be used when using the types, functions, or                    // variables of tbe library

// Function definitions
void options();
void errorMsg();
string round(string x);


int main()
{
    vector <string> parameters; // Will store the inputs
    string userCommand; // The first input
    vector <Current> Opened_currentAccount; // Stores the current account once it's created
    vector <Savings> Opened_savingsAccounts; // Contains all opened savings accounts

    int activeAccount = 0; // stores the ID of the active account
    int savingsIDCounter = 2; // Holds the integer that will be assigned as the saving's/ ISA's ID

    cout << "~~~ Welcome to LincBank! ~~~" << endl;
    options(); // List of valid inputs are listed

    // As long as the user doesn't type 'exit'
    while (userCommand != "exit")
    {
        parameters.clear(); // clear ready for next command
        cout << endl << ">>> ";

        getline(cin, userCommand);
        char* cstr = new char[userCommand.length() + 1];
        strcpy(cstr, userCommand.c_str());

        char* token;
        token = strtok(cstr, " ");

        while (token != NULL)
        {
            parameters.push_back(token);
            token = strtok(NULL, " ");
        }

        string command;

        // As long as the user has inputted something, the first value in the vector 'parameters' is the string value 'command'
        if (!parameters.empty())
        {
            command = parameters[0];
        }

        if (command.compare("options") == 0)
        {
            // all options are displayed to the user
            options();
        }
        else if (command.compare("open") == 0)
        {
            // current account will be created if the user types 'open 1'
            if (parameters[1] == "1")
            {

                if (Opened_currentAccount.size() == 0) // Current account only created if there are no current accounts made                                        // previously
                {
                    Current my_currentAccount(0, 1);
                    double command3 = ::atof(parameters[2].c_str());
                    bool goAhead = false;

                    if (parameters.size() == 3 && command3 > 0)
                    {
                        my_currentAccount.deposit(round(parameters[2]));
                        goAhead = true;
                    }
                    else if (parameters.size() == 2) // creates account with initial deposit of 0 if no amount is given by the user
                    {
                        my_currentAccount.deposit();
                        goAhead = true;
                    }
                    else
                    {
                        errorMsg();
                    }

                    if (goAhead)
                    {
                        Opened_currentAccount.push_back(my_currentAccount);
                        activeAccount = my_currentAccount.Get_accountID();
                    }
                }
                else
                {
                    cout << "You may only have one current account." << endl;
                }
            }
            else if (parameters[1] == "2") // Savings account made
            {
                Savings my_savingsAccount(false, 0.85, 0, savingsIDCounter);
                double command3;
                bool goAhead = false;

                if (parameters.size() == 3)
                {
                    command3 = ::atof(parameters[2].c_str());
                    if (command3 > 0)
                    {
                        my_savingsAccount.deposit(round(parameters[2]));
                        goAhead = true;
                    }
                }
                else if (parameters.size() == 2)
                {
                    my_savingsAccount.deposit();
                    goAhead = true;
                }
                else
                {
                    errorMsg();
                }

                if (goAhead)
                {
                    Opened_savingsAccounts.push_back(my_savingsAccount);
                    activeAccount = my_savingsAccount.Get_accountID();
                    savingsIDCounter += 1;
                }
            }
            else if (parameters[1] == "3") // ISA created only if the initial deposit is 1000 or more
            {
                if (parameters.size() == 3)
                {
                    double intitial_dep = ::atof(parameters[2].c_str());

                    if (intitial_dep >= 1000)
                    {
                        Savings my_savingsAccount(true, 1.15, 0, savingsIDCounter);
                        my_savingsAccount.deposit(round(parameters[2]));
                        Opened_savingsAccounts.push_back(my_savingsAccount);
                        activeAccount = my_savingsAccount.Get_accountID();
                        savingsIDCounter += 1;
                    }
                    else
                    {
                        errorMsg();
                    }
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command.compare("view") == 0)
        {
            // Users can view all acounts and their transaction history, or a specific account if no index is given
            if (parameters.size() == 1 && activeAccount != 0)
            {
                if (Opened_currentAccount.size() != 0)
                {
                    Opened_currentAccount[0].toString();
                }
                else
                {
                    cout << "You have no active Current account" << endl;
                }

                if (Opened_savingsAccounts.size() != 0)
                {
                    for (Savings i : Opened_savingsAccounts)
                    {
                        i.toString();
                    }
                }
                else
                {
                    cout << "You have no active Savings/ ISA accounts" << endl;
                }
            }
            else if (parameters.size() == 2)
            {
                int ID = ::atof(parameters[1].c_str());

                if (ID == 1)
                {
                    Opened_currentAccount[0].toString();
                    activeAccount = Opened_currentAccount[0].Get_accountID();
                }
                else if (ID >= 2 && ID <= (Opened_savingsAccounts.size()) + 1)
                {
                    Opened_savingsAccounts[ID - 2].toString();
                    activeAccount = Opened_savingsAccounts[ID - 2].Get_accountID();
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command.compare("withdraw") == 0)
        {
            // Users can withdraw funds from the most recently active account
            if (parameters.size() == 2 && activeAccount != 0)
            {
                double withdrawAmount = ::atof(parameters[1].c_str());

                if (withdrawAmount > 0)
                {
                    if (activeAccount == 1)
                    {
                        Opened_currentAccount[0].withdraw(round(parameters[1]));
                    }
                    else
                    {
                        Opened_savingsAccounts[activeAccount - 2].withdraw(round(parameters[1]));
                    }
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command.compare("deposit") == 0)
        {
            // User can deposit funds into the most recent account
            if (parameters.size() == 2 && activeAccount != 0)
            {
                double depositAmount = ::atof(parameters[1].c_str());

                if (depositAmount > 0)
                {
                    if (activeAccount == 1)
                    {
                        Opened_currentAccount[0].deposit(round(parameters[1]));
                    }
                    else
                    {
                        Opened_savingsAccounts[activeAccount - 2].deposit(round(parameters[1]));
                    }
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command.compare("transfer") == 0)
        {
            // User can transfer an amount from the first given account ID to another, only if the transaction is valid
            if (parameters.size() == 4 && Opened_currentAccount.size() != 0 && Opened_savingsAccounts.size() != 0)
            {
                double transferAmount = ::atof(parameters[3].c_str());
                int ID1 = ::atof(parameters[1].c_str());
                int ID2 = ::atof(parameters[2].c_str());
                double acc1Before;
                double acc2Before;

                if (transferAmount > 0)
                {
                    if (ID1 == 1 && ID2 > 1 && ID2 <= (Opened_savingsAccounts.size()) + 1)
                    {
                        acc1Before = Opened_currentAccount[0].Get_balance() + Opened_currentAccount[0].Get_overdraft();
                        acc2Before = Opened_savingsAccounts[ID2 - 2].Get_balance();

                        Opened_currentAccount[0].withdraw(round(parameters[3]));
                        if (acc1Before != Opened_currentAccount[0].Get_balance() + Opened_currentAccount[0].Get_overdraft())
                        {
                            Opened_savingsAccounts[ID2 - 2].deposit(round(parameters[3]));
                        }
                        else
                        {
                            errorMsg();
                        }
                    }
                    else if (ID1 > 1 && ID1 <= (Opened_savingsAccounts.size()) + 1 && ID2 == 1)
                    {
                        acc1Before = Opened_savingsAccounts[ID1 - 2].Get_balance();
                        acc2Before = Opened_currentAccount[0].Get_balance() + Opened_currentAccount[0].Get_overdraft();

                        Opened_savingsAccounts[ID1 - 2].withdraw(round(parameters[3]));
                        if (acc1Before != Opened_savingsAccounts[ID1 - 2].Get_balance())
                        {
                            Opened_currentAccount[0].deposit(round(parameters[3]));
                        }
                        else
                        {
                            errorMsg();
                        }
                    }
                    else
                    {
                        errorMsg();
                    }
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
                cout << "Please also make sure you have two open accounts to transfer between" << endl;
            }
        }
        else if (command.compare("project") == 0)
        {
            // User can project a savings account's compound interest however many years into the future they desire
            if (parameters.size() == 2)
            {
                if (activeAccount != 1 && activeAccount != 0)
                {
                    int years = ::atof(parameters[1].c_str());

                    if (years > 0)
                    {
                        Opened_savingsAccounts[activeAccount - 2].computeInterest(years);
                    }
                    else
                    {
                        errorMsg();
                    }
                }
                else
                {
                    errorMsg();
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command.compare("search") == 0)
        {
            // User can search through the account's transaction history by either an amount of money, or whether the
            // transaction was a deposit or a withdraw
            vector<Transaction> everyTransaction;

            for (Transaction i : Opened_currentAccount[0].history)
            {
                everyTransaction.push_back(i);
            }
            for (Savings j : Opened_savingsAccounts)
            {
                for (Transaction k : j.history)
                {
                    everyTransaction.push_back(k);
                }
            }
            cout << "Would you like to search by 'value' or 'type'?" << endl;
            string srchSelect;
            cin >> srchSelect;

            if (srchSelect.compare("value") == 0)
            {
                cout << "Please enter the amount you wish to search by:\n$";
                float srchValue;
                cin >> srchValue;

                for (Transaction k : everyTransaction)
                {
                    if (k.Get_value() == srchValue)
                    {
                        k.toString();
                    }
                }
            }
            else if (srchSelect.compare("type") == 0)
            {
                cout << "Please enter the type (e.g. 'Withdraw' or 'Deposit') you want to search for:\n";
                string srchType;
                cin >> srchType;

                for (Transaction k : everyTransaction)
                {
                    if (k.Get_desc() == srchType)
                    {
                        k.toString();
                    }
                }
            }
            else
            {
                errorMsg();
            }
        }
        else if (command != "exit")
        {
            // User told the input is wrong if it isn't one of the given  commands
            errorMsg();
        }
    }


    cout << "Press any key to quit...";
    getchar();

    return 0;
}

void options()
{
    // All available commands are outputted to the user
    cout << "Follow the inputs carefully to carry out the desired actions:" << endl;
    cout << endl;
    cout << "-- To open an account, type 'open', then either '1' (current account), '2' (savings account), or '3' (ISA). You can also put in an initial deposit too (ISAs require an initial deposit of £1000 minimum), or to have an initial deposit of £0, leave this area blank" << endl;
    cout << "-- To view account details, type 'view' to view all and 'view (ID)' for a specific account" << endl;
    cout << "-- To withdraw from most recently viewed account, type 'withdraw (amount)'. You can't withdraw nothing or a negative amount" << endl;
    cout << "-- To deposit from most recently viewed account, type 'deposit (amount)'. You can't deposit nothing or a negative amount" << endl;
    cout << "-- To transfer funds between accounts, type 'transfer (source) (destination) (amount)'. Amount can't be zero" << endl;
    cout << "-- To project balance forward in years for recently viewed account, type 'project (years)'" << endl;
    cout << "-- To search through transaction history, type 'search' and follow the instructions" << endl;
    cout << "-- To view the options again, type 'options'" << endl;
    cout << "-- To exit the application, type 'exit'" << endl;
    cout << endl;
    cout << "* All amounts of money will automatically be rounded down to 2 decimal places *" << endl;
}

void errorMsg()
{
    // User told their input is wrong
    cout << "Your input was incorrect.\n\
If you would like to see all available options, type 'options'." << endl;
}

string round(string x)
{
    // values are rounded down to two decimal places
    double input = ::atof(x.c_str());
    double value = (int)(input * 100);
    double doub_val = (double)value / 100;
    return to_string(doub_val);
}
