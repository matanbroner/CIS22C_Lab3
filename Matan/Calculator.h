
#ifndef Calculator_h
#define Calculator_h

#include <iostream>
#include <string>
#include <math.h>
#include "Stack.h"
#include "InputValidator.h"


#endif /* Calculator_h */

/*
                                                == Calculator Class ==
 This class has the functionality to accept infix expressions in its constructor, validate the mathemtical expression for correct notation,
 and then form the postfix and prefix notations for the expression. It then also validates the newly formed expressions.
 If input is not validated, the class's members variables remain empty/0.
 */

class Calculator
{
private:
    Stack<int> numbers; // used to hold all integers in input string
    Stack<char> operators; // used to hold all legal operators in input string
    
    const static InputValidator VALIDATOR; // static variable to verify input
    std::string rawInput; // user inputed string (if verified)
    std::string postfixExpression; // resultant postfix expression
    std::string prefixExpression; // resultant prefix expression
    int postfixResult = 0; // evaluation result of postfix expression
    int prefixResult = 0; // evaluation result of prefix expression
    
    /*
     This method takes a string and returns a postfix notation version of the string with the PREFIX rules of operator priority,
     without modifying Calculator class member variables.
     THIS METHOD SHOULD NOT BE USED TO CREATE POSTFIX EXPRESSIONS! IT FOLLOWS PREFIX RULES OF OPERATOR PRIORITY!
     Pre: string
     Post: none
     Return: string
     */
    std::string toPostfixNoEval(std::string);
    
    /*
     This method pops two numbers from the 'numbers' member variable and one operator from the 'operators' member variable.
     It uses the Operator class's 'operation' method to operate accordingly on the two popped numbers.
     If the mode argument is equal to 1, then the popped operator is added to 'postfixExpression', if it is 2, then not.
     If anything other than 1 or two is given for 'mode', an exception is thrown.
     Pre: int (mode)
     Post: one operator popped from 'operators', two numbers popped from 'numbers' and result pushed to 'numbers'.
            --> if mode == 1, then 'postfixExpression' is appended with popped operator
     Return: none
     */
    void operateAndPushResult(int mode = 1);
    
    /*
     This method safely pushed an operator to the 'operators' member variable according to postifx notation and priortiy of operators.
     If needed, operators will be popped and operations on numbers will ensue, otherwise the operator input is pushed to the stack.
     Pre: char
     Post: 'operators' Stack is modified to hold the operator input properly, operations may ensue and 'numbers' may be modified according to the use
            of the method 'operateAndPushResult'.
     Return: none
     */
    void operatorPush(char);
    
    /*
     This method takes the validated user input and uses the other class methods to properly change 'postifxExpression' accordingly.
     If the current index being parsed through is an operand, the method enusres that multi digit numbers are preserved correctly.
     The method ensures that operator prioriy is followed, and if needed uses 'operaterPush' and 'operateAndPushResult' to both modify the class's
     'postfixExpression' and 'postfixResult'. The proper postfix result is the last number on the 'numbers' Stack'  after emptying out the
     'operators' stack post-parse.
     Pre: none
     Post: 'postfixExpression' and 'postfixResult' are modified
     Return: none
     */
    void convert_POSTFIX();
    
    /*
     This method takes the validated user input and uses the other class methods to properly change 'prefixExpression' accordingly.
     The method first reverses the 'rawInput' member variable using the inputValidator class's 'reverse' method,
     then uses 'toPostfixNoEval' to obtain a postfix notation of the reversed string, and then
     sets the class's 'prefixExpression' to the reversed version of the resultant string.
     After that, the pre-reversed 'prefixExpression' is parsed through from right to left, numbers are pushed to the 'numbers' Stack with assurance
     that multidigit numbers are preserved. Operators are pushed to 'operators' Stack and 'operateAndPushResult' is used with mode = 2 if needed.
     The class's 'prefixResult' is equal to the last number left on the 'numbers' Stack after emptying out the 'operators' stack post-parse.
     Pre: none
     Post: 'prefixExpression' and 'prefixResult' are modified
     Return: none
     */
    void convert_PREFIX();
    
public:
    Calculator(std::string); // constructor with given input
    Calculator(); // constructor with no given input
    
    /*
     This method allows Calculator instance variables without initial input to perfrom calculations, or to evaulate new expressions
     with the same instance.
     The inputValidator member variable is used to validate input, and if valid then 'convert_POSTFIX' and 'convert_PREFIX' are encated
     similar to the way done in the contructor with given input.
     Pre: string
     Post: 'prefixExpression', 'postfixExpression', 'prefixResult', 'postfixResult' all modified
     */
    void setRawInput(std::string);
    
    std::string getPostfixExpression(); // returns 'postfixExpression'
    std::string getPrefixExpression(); // returns 'prefixExpression'
    std::string getRawInput(); // returns validated user input, invalid input will not be saved to 'rawInput'
    int getPostfixResult(); // returns 'postifxResult'
    int getPrefixResult(); // returns 'postifxResult'
    
};

Calculator::Calculator(std::string userInput)
{
    // sets the string member variables to empty strings, pre evaluation
    this->postfixExpression = "";
    this->prefixExpression = "";
    this->rawInput = "";
    if (VALIDATOR.validate(userInput)) // if the user input is valid according to 'validate' method
    {
        this->rawInput = userInput; // accepts the user input into 'rawInput'
        
        this->convert_POSTFIX(); // converts user input to postfix and modifies relevant member variables
        this->convert_PREFIX(); // converts user input to prefix and modifies relevant member variables
    }
    else
        std::cout << "invalid input"; // if input is invalid, user is informed as such
}

Calculator::Calculator()
{
    // sets the string member variables to empty strings
    this->rawInput = "";
    this->postfixExpression = "";
    this->prefixExpression = "";
}

void Calculator::setRawInput(std::string userInput)
{
    if (VALIDATOR.validate(userInput)) // if new user input is valid according to 'validate' method
    {
        // sets the string member variables to empty strings, pre evaluation
        this->postfixExpression = "";
        this->prefixExpression = "";
        this->rawInput = userInput; // accepts the user input into 'rawInput'
        
        this->convert_POSTFIX(); // converts user input to postfix and modifies relevant member variables
        this->convert_PREFIX(); // converts user input to prefix and modifies relevant member variables
    }
    else
        std::cout << "invalid input"; // if input is invalid, user is informed as such
}

void Calculator::convert_POSTFIX()
{
    for (int i = 0; i < this->rawInput.length(); i++) // parses through 'rawInput' from right to left
    {
        if (isOperand(this->rawInput[i])) // if current index holds a digit
        {
            std::string numHold = ""; // string to hold multi digit numbers
            numHold += this->rawInput[i]; // adds current index digit
            while(isOperand(this->rawInput[i+1])) // while the next index also holds a digit
            {
                i++; // increments index
                numHold += this->rawInput[i]; // adds new digit to the number holding string
            }
            this->numbers.push(std::stoi(numHold)); // pushed the single/multi digit number to the 'numbers' Stack
            this->postfixExpression += numHold; // appends the single/multi digit number to 'postfixExpression'
        }
        else if (isOperator(this->rawInput[i])) // if current index holds an operator
        {
            switch (this->rawInput[i])
            {
                case '(':
                    this->operators.push('('); // open parentheses are always pushed to the Stack
                    break;
                case '*':
                case '/':
                case '%':
                case '+':
                case '-':
                    this->operatorPush(this->rawInput[i]); // safely pushed operators according to operator priority
                    break;
                case ')': // never actually pushed to 'operators' Stack
                    while (this->operators.rear() != '(') // while the opening parentheses in the pair is not reached
                        this->operateAndPushResult(); // uses all operators inside parentheses to operate on the numbers inside the parentheses
                    this->operators.pop(); // pops the opening parentheses in the pair
                    
            }
        }
    }
    while(!this->operators.isEmpty()) // while there are operators left in the 'operators' Stack
    {
        operateAndPushResult(); // uses these operators to perform operations on numbers in the 'numbers' stack
    }
    
    this->postfixResult = this->numbers.pop(); // last number left on the Stack should be the result of the expression
}

void Calculator::convert_PREFIX()
{
    std::string revRawInput = reverse(this->rawInput); // correctly reverses the validated 'rawInput' to a new string
    revRawInput = toPostfixNoEval(revRawInput); // converts the string to postfix notation without actually evaluating the postfix expression
    this->prefixExpression = reverse(revRawInput); // reverses the resultant postfix expression and sets 'prefixExpression'
    for (int i = 0; i < int(revRawInput.length()); i++)
        // parses through the pre-reversed 'prefixExpression' from left to right --> identical to parsing through 'prefixExpression' from right to left
    {
        if (isOperand(this->rawInput[i])) // if current index holds a digit
        {
            std::string numHold = ""; // string to hold multi digit numbers
            numHold += this->rawInput[i]; // adds current index digit
            while(isOperand(this->rawInput[i+1])) // while the next index also holds a digit
            {
                i++; // increments index
                numHold += this->rawInput[i]; // adds new digit to the number holding string
            }
            this->numbers.push(std::stoi(numHold)); // pushed the single/multi digit number to the 'numbers' Stack
        }
        else if (isOperator(revRawInput[i])) // if current index holds an operator
        {
            this->operators.push(revRawInput[i]); // pushed the operator to the 'operators' Stack
            this->operateAndPushResult(2); // then uses this newly pushed operator to peform correct operations on 'numbers' Stack (mode = 2)
        }
    }
    this->prefixResult = this->numbers.pop(); // last number left on the Stack should be the result of the expression
}

// THIS METHOD FOLLOWS POSTFIX RULES FOR OPERATOR PRIORITY
void Calculator::operatorPush(char op) // used to safely push operators to the 'operators' Stack
{
        if (this->operators.getStackCount() == 0 ) // if 'operators' Stack is empty
            this->operators.push(op); // always pushed
        else if (Operator::getPriority(this->operators.rear()) < Operator::getPriority(op))
            // if operator priority of 'operators' rear has a lower priority than the input operator
            this->operators.push(op);
        else
        {
            while (this->operators.getStackCount() > 0 && Operator::getPriority(op) <= Operator::getPriority(this->operators.rear()))
                this->operateAndPushResult();
            // while the 'operators' rear has an equal or greater priority than the input operator
            this->operators.push(op);
        }
    
}

void Calculator::operateAndPushResult(int mode) // used to perform operations on two operands and a legal operator
{
    try
    {
        int op1, op2;
        op2 = this->numbers.pop();
        op1 = this->numbers.pop();
        // pops two operands from 'numbers' Stack
        
        char operate = this->operators.pop(); // pops operation operator from 'operators' Stack
        int resultOfOp = Operator::operation(op1, op2, operate);
        // uses Operator class to perfrom operation, which throws an exception with either illegal operators or dividing by zero
        this->numbers.push(resultOfOp); // pushed operation result to 'numbers' Stack
        if (mode == 1) // if using this method for postfix notation conversion
            this->postfixExpression += operate; // 'postfixExpression' appeneded with operator popped
        else
            throw "MODE VALUE INVALID FOR OPERATION";  // if mode is neither 1 or 2, exception is thrown for misuse of method
    }
    catch (char const* errorMessage) // if the operator popped is not a legal operator, or dividing by zero is the operation in question
    {
        std::cout << errorMessage << std::endl;
        std::cout << "PROGRAM WILL NOW QUIT..." << std::endl;
        std::exit(1); // ends program completely
    }
}

std::string Calculator::getPostfixExpression()
{
    return this->postfixExpression;
}

std::string Calculator::getPrefixExpression()
{
    return this->prefixExpression;
}

std::string Calculator::getRawInput()
{
    return this->rawInput;
}

int Calculator::getPostfixResult()
{
    return this->postfixResult;
}

int Calculator::getPrefixResult()
{
    return this->prefixResult;
}

// FOLLOWS PREFIX RULES FOR PUSHING OPERATORS TO STACK, DO NOT USE TO FORM POSTFIX EXPRESSIONS IN GENERAL
std::string Calculator::toPostfixNoEval(std::string eq)
{
    std::string post = ""; // string to be returned
    for (int i = 0; i < eq.length(); i++) // parses the input from left to right
    {
        if (isOperand(eq[i])) // if current index holds a digit
        {
            std::string numHold = ""; // string to hold multi digit numbers
            numHold += this->rawInput[i]; // adds current index digit
            while(isOperand(this->rawInput[i+1])) // while the next index also holds a digit
            {
                i++; // increments index
                numHold += this->rawInput[i]; // adds new digit to the number holding string
            }
            post += numHold; // appends the number holding string to the postfix string
            post.append("$"); // adds '$' seperation between numbers to be able to properly reverse again after
        }
        else if (isOperator(eq[i])) // if current index holds an operator
        {
            switch (eq[i])
            {
                case '(':
                    this->operators.push('('); // always pushed
                    break;
                case '*':
                case '/':
                case '%':
                case '+':
                case '-':
                    if (this->operators.getStackCount() == 0) // if operator stack is empty
                        this->operators.push(eq[i]); // always pushed
                    else
                    {
                        // if 'operators' rear priority is less than or equal to the operator at index
                        if (Operator::getPriority(this->operators.rear()) <= Operator::getPriority(eq[i]))
                            this->operators.push(eq[i]);
                        else
                        {
                            // while the 'operators' stack is not empty and the priority of operator at index is less than 'operators' rear
                            while (this->operators.getStackCount() > 0 && Operator::getPriority(eq[i]) < Operator::getPriority(this->operators.rear()))
                                post += this->operators.pop(); // pops the 'operators' stack and appends to postfix string
                            this->operators.push(eq[i]); // pushes new operator to Stack
                        }
                    }
                    break;
                case ')':
                    while (this->operators.rear() != '(') // while opening parentheses in pair is not found at 'operators' rear
                        post += this->operators.pop(); // pops the 'operators' stack and appends to postfix string
                    this->operators.pop(); // pops opening parentheses
                    
            }
        }
    }
    while(!this->operators.isEmpty()) // pops the remaining operators in the stack and appends to postfix string
    {
        post += this->operators.pop();
    }

    return post; // returns postfix string
}
