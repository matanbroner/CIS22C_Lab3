
#ifndef InputValidator_h
#define InputValidator_h
#include "Operator.h"

/*
 This method parses a string and esnures that the number of open parentheses is equal to the number of close parentheses.
 It also verifies that parentheses are formatted correctly, meaning that a open parentheses in a pair is not
 placed before the closing parentheses in the pair.
 Pre: string
 Post: none
 Return: bool
 */
bool parenthesesCounter(std::string);

/*
 This method takes a char input and checks whether it is a digit or not (ie. The char is in the range of '0' to '9')
 Pre: char
 Post: none
 Return: bool
 */
bool isOperand(char s);

/*
 This method takes a char input and checks whether it is an operator or not (ie. The char is '*', '/', '%', '+', '-', '(', or ')')
 Pre: char
 Post: none
 Return: bool
 */
bool isOperator(char s);

/*
 This method takes a char input and checks whether it is an opening parentheses (ie. The char is '(')
 Pre: char
 Post: none
 Return: bool
 */
bool isOpenParentheses(char s);

/*
This method takes a char input and checks whether it is an closing parentheses (ie. The char is ')')
Pre: char
Post: none
Return: bool
*/
bool isCloseParentheses(char s);

/*
 This method takes a char input and checks whether it is a space (ie. The char is ' ')
 Pre: char
 Post: none
 Return: bool
 */
bool isSpace(char s);

/*
 This method takes a string and returns a reversed version of its input. All parentheses are flipped (ex. ')' becomes '('),
 also all multi digit numbers are preserved in their correct order (ex. 21 does not become 12) through counting the number of digits
 and pushing the number accordingly.
 Pre: string
 Post: none
 Return: string
 */
std::string reverse(std::string s);

/*
                                               == InputValidator Class ==
 This class has the functionality to valiate the mathematical syntax of an inputed expression.
 It checks that only certain characters are part of the expression, and that parentheses are formatted correctly.
 */

class InputValidator
{
public:
    
    /*
     This method is an all encompaing validator of user inputed expressions. It verifies that the oprands and operators have been given correctly and formmated in a mathematically sound manner. If any aspect of the input is found to be invalid, the methods returns false in order to inform the user that working with the input is not advised.
     Pre: string
     Post: none
     Return: bool
     */
    static bool validate(std::string);
};

bool InputValidator::validate(std::string inputText)
{
    std::string inputStatement = "";
    for (int i = 0; i < inputText.length(); i++) // create new string with no spaces and $ char between numbers, to differentiate 2+ digit numbers
    {
        if (!isSpace(inputText[i])) // if the character at the index is not a space (spaces are not kept)
            inputStatement += inputText[i];
        if (isOperand(inputText[i])) // if the added character is a digit
        {
            while (isOperand(inputText[i+1])) // this allows for multi digit numbers to be added
            {   // while there is no space  or operator after current digit
                i++;
                inputStatement += inputText[i];
            }
            inputStatement += '$'; // places a '$' after each number to ensure that multi digit numbers are read properly later
        }
    }
    // example outcome of inputStatment: "3 + 42 - 9" results in inputStatement = "3$+42-9$"
    
    if (inputStatement.length() < 3) // input is meaningless [ex. "3 +"]
        return false;
    if (!parenthesesCounter(inputStatement)) // if parentheses are placed illegally [ex. )( , or do not match up ex. (3 + 4))]
        return false;
    if (isOperator(inputStatement[0]) && !isOpenParentheses(inputStatement[0])) // if the first character is anything but a number or (
        return false;
    if (isOperator(inputStatement[inputStatement.length()-1]) && !isCloseParentheses(inputStatement[inputStatement.length()-1]))
        // last index is operator, not )
        return false;
    
    for (int i = 0; i < inputStatement.length() - 1; i++)
    {
        if (i == inputStatement.length() - 1) // check the last digit individually, to avoid looking past string length
        {
            if (inputStatement[i] != '$' && !isCloseParentheses(inputStatement[i])) // if last input was not a number or closing parentheses
            return false;
        }
        
        if (!isOperand(inputStatement[i]) && !isOperator(inputStatement[i])) // if character inputed is neither a digit or operator (ex. '#')
            return false;
        
        if (isOperator(inputStatement[i])) // if character at index is a legal operator
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
            if (isOperand(inputStatement[i+1])) // if there is a number following a number without an operator in between them
                return false;
            if (isOpenParentheses(inputStatement[i+1])) // if number is followed directly by a ( without legal operator between them
                return false;
        }
    }
    return true;
}

bool parenthesesCounter(std::string eq)
{
    int openP = 0, closeP = 0; // counters for both open parentheses
    for (char c : eq)
    {
        if (isOpenParentheses(c))
            openP++;
        if (isCloseParentheses(c))
        {
            closeP++;
            if (closeP > openP) // if a closing parentheses was placed before its paired opening parentheses [ex. "3 + )3 -4("]
                return false;
        }
    }
    return (openP == closeP); // returns true if pairs of parentheses are valid and false otherwise
}

bool isOperand(char s) // determines if s is a digit
{
    if (s >= '0' && s  <= '9')
        return true;
    else return false;
}

bool isOperator(char s) // determines if s is a legal operator
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

bool isOpenParentheses(char s) // determines if s is equal to '('
{
    if (s == '(')
        return true;
    return false;
}

bool isCloseParentheses(char s) // determines if s is equal to ')'
{
    if (s == ')')
        return true;
    return false;
}
            
bool isSpace(char s) // determines if s is equal to ' '
{
    if (s == ' ')
        return true;
    return false;
}

std::string reverse(std::string s)
{
    std::string temp = ""; // string to be returned
    for (int i = int(s.length())-1; i >= 0; i--) // starts from the back of input
    {
        if (isSpace(s[i])) // skips spaces
            continue;
        if (isOpenParentheses(s[i]))
        {
            temp.append(")"); // adds an ')' to new string --> flips the parentheses
            continue; // breaks out of the current iteration
        }
        else if (isCloseParentheses(s[i]))
        {
             temp.append("("); // adds an '(' to new string --> flips the parentheses
            continue; // breaks out of the current iteration
        }
        else if (isOperand(s[i]))
        {
            std::string num; // creates a new string to hold the single/multi digit number
            num += s[i]; // adds first digit from the left
            while (i != 0 && isOperand(s[i-1])) // parses until character at index is no longer a digit or string has been completely parsed
            {
                i--;
                num = s[i] + num; // adds the next digit to the number string
            }
            temp.append(num); // appends the number to the string
            continue; // breaks out of the current iteration
        }
        else if (isOperator(s[i])) // if the character is an operator other than parentheses
        {
            temp += s[i]; // always added
            continue; // breaks out of the current iteration
        }

    }
    return temp; // returns revered input
}

#endif /* InputValidator_h */
