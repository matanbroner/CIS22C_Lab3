//
//  main.cpp
//  CIS22C_Lab3
//
//  Created by Matan Broner on 10/22/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#include <iostream>
#include "Calculator.h"

void clearInput();
void displayResults();
void manual();

Calculator userCalculator;

using namespace std;
int main(int argc, const char * argv[])
{
    int choice = 0;
    string userInput = "";
    
    while (choice != 4)
    {
        cout << "=== WELCOME TO THE PRE/POST FIX CALCULATOR ===" << endl;
        cout << "[1] - Enter an equation for conversion" << endl;
        cout << "[2] - View results of last conversion" << endl;
        cout << "[3] - Read user manual" << endl;
        cout << "[4] - Exit" << endl;
        cout << "-> ";
        cin >> choice;
        while (choice < 1 || choice > 4)
        {
            cout << "Invalid choice..." << endl;
            cout << "-> ";
            cin >> choice;
        }
        switch (choice)
        {
            case 1:
                clearInput();
                cout << "== ENTER EQUATION BELOW ==\n-> ";
                getline(cin,userInput);
                userCalculator.setRawInput(userInput);
                if (userCalculator.getPostfixExpression().length() >= 3)
                {
                    cout << endl;
                    displayResults();
                }
                break;
            case 2:
                if (userCalculator.getPostfixExpression().length() >= 3)
                {
                    cout << endl;
                    displayResults();
                }
                else cout << "*** expression was either not given or was not valid! ***" << endl;
                break;
            case 3:
                manual();
                break;
            case 4:
                break;
            default: cout << "Error occured with menu choice..." << endl;
        }
        cout << endl << endl;
        if (choice != 4) // Has user respond and clears console
        {
            cout << "Press ENTER to continue...";
            cin.get();
            system("clear");
        }
    }
     cout << "... system exiting, goodbye!" << endl;

    system("pause");
    return 0;
}

void clearInput()
{
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
}

void displayResults()
{
    cout << "[ORIGINAL EXPRESSION] : " << userCalculator.getRawInput() << endl;
    cout << "[POSTFIX EXPRESSION] : " << userCalculator.getPostfixExpression() << endl;
    cout << "--> result: " << userCalculator.getPostfixResult() << endl;
    cout << "[PREFIX EXPRESSION] : " << userCalculator.getPrefixExpression() << endl;
    cout << "--> result: " << userCalculator.getPrefixResult() << endl;
}

void manual()
{
    cout << "=== PRE/POST FIX CALCULATOR USER MANUAL ===" << endl;
    cout << "Valid operands: integers ranging 0-9, no decimal numbers" << endl;
    cout << "Valid operators: *, /, %, +, -, (, ), no unary operators are accepted" << endl;
    cout << "If input is invalid, user will be unable to use Option [2] on the Calculator menu" << endl;
}
