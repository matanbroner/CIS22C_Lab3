//
//  InputValidator.h
//  CIS22C_Lab3
//
//  Created by Matan Broner on 10/25/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef InputValidator_h
#define InputValidator_h
#include "Operator.h"

bool parenthesesCounter(std::string);
bool isOperand(char s);
bool isOperator(char s);
bool isOpenParentheses(char s);
bool isCloseParentheses(char s);
bool isSpace(char s);
std::string reverse(std::string s);

class InputValidator
{
public:
    static bool validate(std::string);
};

bool InputValidator::validate(std::string inputText)
{
    std::string inputStatement = "";
    for (int i = 0; i < inputText.length(); i++) // create new string with no spaces and $ char between numbers, to differentiate 2+ digit numbers
    {
        if (!isSpace(inputText[i]))
            inputStatement += inputText[i];
        if (isOperand(inputText[i]))
        {
            while (isOperand(inputText[i+1]))
            {   // while there is no space  or operator after current digit
                i++;
                inputStatement += inputText[i];
            }
            inputStatement += '$';
        }
    }
    
    if (inputStatement.length() < 3) // input is meaningless ex. 3 +
        return false;
    if (!parenthesesCounter(inputStatement)) // if parentheses are placed illegally ex. )( , or do not match up ex. (3 + 4))
        return false;
    if (isOperator(inputStatement[0]) && !isOpenParentheses(inputStatement[0])) // if the first character is anything but a number or (
        return false;
    if (isOperator(inputStatement[inputStatement.length()-1]) && !isCloseParentheses(inputStatement[inputStatement.length()-1])) // last index is operator, not )
        return false;
    
    for (int i = 0; i < inputStatement.length() - 1; i++)
    {
        if (i == inputStatement.length() - 1) // check the last digit individually, to avoid looking past string length
        {
            if (inputStatement[i] != '$' && !isCloseParentheses(inputStatement[i])) // if last input was not a number
            return false;
        }
        
        if (!isOperand(inputStatement[i]) && !isOperator(inputStatement[i]))
            return false;
        
        if (isOperator(inputStatement[i]))
        {
            // if parentheses without numbers ex. ()
            if (isOpenParentheses(inputStatement[i]) && isCloseParentheses(inputStatement[i+1]))
                return false;
            
            // parentheses with operator right after ex. (+
            if (isOpenParentheses(inputStatement[i]) && isOperator(inputStatement[i+1]) && !isOpenParentheses(inputStatement[i+1]))
                return false;
            
            // if both current and next index are non-parentheses operators
            if ((!isOpenParentheses(inputStatement[i]) && !isCloseParentheses(inputStatement[i])) && isOperator(inputStatement[i+1]))
            {
                if ((!isOpenParentheses(inputStatement[i+1]) && !isCloseParentheses(inputStatement[i+1])))
                return false;
            }
        }
        
        if (isOperand(inputStatement[i]))
        {
            while (inputStatement[i] != '$') // find the last digit of the number
                i++;
            if (isOperand(inputStatement[i+1])) // if there is a number following a number without an operator
                return false;
            if (isOpenParentheses(inputStatement[i+1])) // if number is followed directly by a (
                return false;
        }
    }
    return true;
}

bool parenthesesCounter(std::string eq)
{
    int openP = 0, closeP = 0;
    for (char c : eq)
    {
        if (c == '(')
            openP++;
        if (c == ')')
        {
            closeP++;
            if (closeP > openP)
                return false;
        }
    }
    return (openP == closeP);
}

bool isOperand(char s)
{
    if (s >= '0' && s  <= '9')
        return true;
    else return false;
}

bool isOperator(char s)
{
    switch(s)
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '(':
        case ')':
            return true;
            break;
        default: return false;
    }
}

bool isOpenParentheses(char s)
{
    if (s == '(')
        return true;
    return false;
}

bool isCloseParentheses(char s)
{
    if (s == ')')
        return true;
    return false;
}
            
bool isSpace(char s)
{
    if (s == ' ')
        return true;
    return false;
}

std::string reverse(std::string s)
{
    std::string temp = "";
    int tempLength = 0;
    for (int i = int(s.length())-1; i >= 0; i--)
    {
        if (isSpace(s[i]))
            continue;
        if (isOpenParentheses(s[i]))
        {
            temp.append(")");
            continue;
        }
        else if (isCloseParentheses(s[i]))
        {
             temp.append("(");
            continue;
        }
        else if (isOperand(s[i]))
        {
            std::string num;
            num += s[i];
            tempLength++;
            while (i != 0 && isOperand(s[i-1]))
            {
                i--;
                num = s[i] + num;
            }
            temp.append(num);
            continue;
        }
        else if (isOperator(s[i]))
        {
            temp += s[i];
            continue;
        }

    }
    return temp;
}

#endif /* InputValidator_h */
