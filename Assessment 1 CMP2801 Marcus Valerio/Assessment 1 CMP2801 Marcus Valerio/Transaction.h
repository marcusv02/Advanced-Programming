#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <math.h>

using namespace std;

// Definition of the 'Transaction' class
class Transaction
{
private:
    // All variables made private
    string desc;
    time_t now = time(0);
    char* timestamp = ctime(&now);
    double value;

public:
    // Functions defined here, including accessors and mutators
    string Get_desc()
    {
        return desc;
    }
    void Set_desc(string x)
    {
        desc = x;
    }
    string Get_timestamp()
    {
        return timestamp;
    }
    double Get_value()
    {
        return value;
    }
    void Set_value(double x)
    {
        value = x;
    }
    void toString()
    {
        cout << "-- " << desc << " of $" << value << " at " << timestamp << endl;
    }
};