
/*
                                                == Operator Class ==
Used to determine operator priority and perform operations safely on operands
 */

#ifndef Operator_h
#define Operator_h

// Used to numerically express the operator priorities of the symbols inputed by the user
enum operatorPriority
{
    CLOSE_PARENTHESES = 3, // ')'
    MULT_DIV_MOD = 2, // '*', '/', '%'
    ADD_SUB = 1, // '+', '-'
    OPEN_PARENTHESES = 0 // '('
};

class Operator
{
public:
    /*
     This method takes two operands (integers) and a symbol used for operating on them.
     If the symbol is valid, the method returns the result of the operation.
     Pre: int, int, char
     Post: none
     Return: int or exception thrown
     */
    static int operation(int, int, char);
    
    /*
     This method takes a char and uses the enumerated type 'operatorPriority' to determine its priority in order of operations.
     Pre: char
     Post: none
     Return: int or exception thrown
     */
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
        default: throw "invalid operator input"; // the inputed char was not an operator
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
            if (num2 != 0)
            return num1 / num2;
            else throw ("DIVIDE BY ZERO ERROR");
            // if the second operand 2 is zero, we cannot divide by it according to the division by zero principle of mathematics
            break;
        case '%':
            if (num2 != 0)
                return num1 % num2;
            else throw ("DIVIDE BY ZERO ERROR");
            // if the second operand 2 is zero, we cannot divide by it according to the division by zero principle of mathematics
            break;
        case '+':
            return num1 + num2;
            break;
        case '-':
            return num1 - num2;
            break;
    }
    throw "Bad operation attempt, examine input: " + op;
    // if char was not an operator, we cannot use it. This should not occur in Calculator after input validation.
}



#endif /* Operator_h */
