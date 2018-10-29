/*
                                    == CIS22C LAB 3 - INFIX CONVERSION AND EVALUATION ==
 Driver program to demonstrate the functionality of Calculator class and its supporting classes for conversion and evaluation of infix expressions
 
 Date: 10/29/2018
 Partners: Matan Broner and Timo Bitterli
 Matan Partner Rating for Timo: 0
 */


#include <iostream>
#include "Calculator.h"

void clearInput(); // used to prevent getline from being skipped by leftover newline character from cin
void displayResults(); // prints the original, prefix, and postfix expressions and their results
void manual(); // prints "user manual" paragraph

Calculator userCalculator; // global Calculator instance variable

using namespace std;
int main(int argc, const char * argv[])
{
    int choice = 0; // used for user menu choice
    string userInput = ""; // used to hold user inputed expressions
    
    while (choice != 4) // 4 is the exit choice
    {
        cout << "=== WELCOME TO THE PRE/POST FIX CALCULATOR ===" << endl;
        cout << "[1] - Enter an equation for conversion" << endl;
        cout << "[2] - View results of last legal conversion" << endl;
        cout << "[3] - Read user manual" << endl;
        cout << "[4] - Exit" << endl;
        cout << "-> ";
        cin >> choice;
        while (cin.fail()||choice < 1 || choice > 4) // ensures valid input
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid choice..." << endl;
            cout << "-> ";
            cin >> choice;
        }
        switch (choice)
        {
            case 1: // user wishes to input and evaulate a new expression
                clearInput();
                cout << "== ENTER EQUATION BELOW ==\n-> ";
                getline(cin,userInput);
                userCalculator.setRawInput(userInput);
                if (userCalculator.getPostfixExpression() != "") // if the last input was indeed valid
                {
                    cout << endl;
                    displayResults(); // prints the original, prefix, and postfix expressions and their results
                }
                break;
            case 2: // gives result of last legal expression conversion and evaulation
                if (userCalculator.getPostfixExpression() != "") // if the last input was indeed valid / actually given
                {
                    cout << endl;
                    displayResults(); // prints the original, prefix, and postfix expressions and their results
                }
                else cout << "*** expression was either not given or was not valid! ***" << endl;
                break;
            case 3:
                manual(); // prints "user manual" paragraph
                break;
            case 4:
                break; // nothing happens, exits the loop
            default: cout << "Error occured with menu choice..." << endl; // should not occur
        }
        cout << endl << endl;
        if (choice != 4) // has user respond and clears console
        {
            cout << "Press ENTER to continue...";
            cin.get();
            system("cls");
        }
    }
     cout << "... system exiting, goodbye!" << endl;

    system("pause");
    return 0;
}

void clearInput() // used to prevent getline from being skipped by leftover newline character from cin
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
