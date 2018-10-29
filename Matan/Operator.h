//
//  Operator.h
//  CIS22C_Lab3
//
//  Created by Matan Broner on 10/25/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef Operator_h
#define Operator_h

enum operatorPriority
{
    CLOSE_PARENTHESES = 3,
    MULT_DIV_MOD = 2,
    ADD_SUB = 1,
    OPEN_PARENTHESES = 0
};

class Operator
{
public:
    static int operation(int, int, char);
    static int getPriority(char);
};

int Operator::getPriority(char text)
{
    switch(text)
    {
        case '(':
            return OPEN_PARENTHESES;
            break;
        case ')':
            return CLOSE_PARENTHESES;
            break;
        case '*':
        case '/':
        case '%':
           return MULT_DIV_MOD;
            break;
        case '+':
        case '-':
            return ADD_SUB;
            break;
        default: throw "invalid operator input";
    }
}


int Operator::operation(int num1, int num2, char op)
{
    switch (op)
    {
        case '*':
            return num1 * num2;
            break;
        case '/':
        try
        {
            if (num2 != 0)
            return num1 / num2;
            else throw ("DIVIDE BY ZERO ERROR");
        }
        catch (char const* errorStatement)
        {
            std::cout << errorStatement << std::endl;
            std::exit(0);
        }
            break;
        case '%':
            try
        {
            if (num2 != 0)
                return num1 % num2;
            else throw ("DIVIDE BY ZERO ERROR");
        }
            catch (char const* errorStatement)
        {
            std::cout << errorStatement << std::endl;
            std::exit(0);
        }
            break;
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num1 - num2;
            break;
    }
    throw "Bad operation attempt, examine input: " + op;
}



#endif /* Operator_h */
