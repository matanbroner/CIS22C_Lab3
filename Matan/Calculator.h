//
//  Calculator.h
//  CIS22C_Lab3
//
//  Created by Matan Broner on 10/26/18.
//  Copyright © 2018 Matan Broner. All rights reserved.
//

#ifndef Calculator_h
#define Calculator_h

#include <iostream>
#include <string>
#include <math.h>
#include "Stack.h"
#include "InputValidator.h"


#endif /* Calculator_h */

class Calculator
{
private:
    Stack<int> numbers;
    Stack<char> operators;
    
    const static InputValidator VALIDATOR;
    std::string rawInput;
    std::string postfixExpression;
    std::string prefixExpression;
    int postfixResult = 0;
    int prefixResult = 0;
    
    std::string toPostfixNoEval(std::string);
    
    void operateAndPushResult(int mode = 1);
    void operatorPush(char);
    
    void convert_POSTFIX();
    void convert_PREFIX();
    
public:
    Calculator(std::string);
    Calculator();
    void setRawInput(std::string);
    
    std::string getPostfixExpression();
    std::string getPrefixExpression();
    std::string getRawInput();
    int getPostfixResult();
    int getPrefixResult();
    
};

Calculator::Calculator(std::string userInput)
{
    if (VALIDATOR.validate(userInput))
    {
        this->postfixExpression = "";
        this->prefixExpression = "";
        this->rawInput = userInput;
        
        this->convert_POSTFIX();
        this->convert_PREFIX();
    }
    else
        std::cout << "invalid input";
}

Calculator::Calculator()
{
    this->rawInput = "";
    this->postfixExpression = "";
    this->prefixExpression = "";
}

void Calculator::setRawInput(std::string userInput)
{
    if (VALIDATOR.validate(userInput))
    {
        this->postfixExpression = "";
        this->prefixExpression = "";
        this->rawInput = userInput;
        
        this->convert_POSTFIX();
        this->convert_PREFIX();
    }
    else
        std::cout << "invalid input";
}

void Calculator::convert_POSTFIX()
{
    for (int i = 0; i < this->rawInput.length(); i++)
    {
        if (isOperand(this->rawInput[i]))
        {
            std::string numHold = "";
            numHold += this->rawInput[i];
            while(isOperand(this->rawInput[i+1]))
            {
                i++;
                numHold += this->rawInput[i];
            }
            this->numbers.push(std::stoi(numHold));
            this->postfixExpression += numHold;
        }
        else if (isOperator(this->rawInput[i]))
        {
            switch (this->rawInput[i])
            {
                case '(':
                    this->operators.push('(');
                    break;
                case '*':
                case '/':
                case '%':
                case '+':
                case '-':
                    this->operatorPush(this->rawInput[i]);
                    break;
                case ')':
                    while (this->operators.rear() != '(')
                        this->operateAndPushResult();
                    this->operators.pop();
                    
            }
        }
    }
    while(!this->operators.isEmpty())
    {
        operateAndPushResult();
    }
    
    this->postfixResult = this->numbers.pop();
}

void Calculator::convert_PREFIX()
{
    std::string revRawInput = reverse(this->rawInput);
    revRawInput = toPostfixNoEval(revRawInput);
    this->prefixExpression = reverse(revRawInput);
    for (int i = 0; i < int(revRawInput.length()); i++)
    {
        if (isOperand(revRawInput[i]))
        {
            std::string numHold = "";
            numHold += revRawInput[i];
            while(isOperand(revRawInput[i+1]))
            {
                i++;
                numHold += revRawInput[i];
            }
            this->numbers.push(std::stoi(numHold));
        }
        else if (isOperator(revRawInput[i]))
        {
            this->operators.push(revRawInput[i]);
            this->operateAndPushResult(2);
        }
    }
    this->prefixResult = this->numbers.pop();
}

void Calculator::operatorPush(char op)
{
        if (this->operators.getStackCount() == 0 )
            this->operators.push(op);
        else if (Operator::getPriority(this->operators.rear()) < Operator::getPriority(op))
            this->operators.push(op);
        else
        {
            while (this->operators.getStackCount() > 0 && Operator::getPriority(op) <= Operator::getPriority(this->operators.rear()))
                this->operateAndPushResult();
            this->operators.push(op);
        }
    
}

void Calculator::operateAndPushResult(int mode)
{
    int op1, op2;
    if (mode == 1)
    {
        op2 = this->numbers.pop();
        op1 = this->numbers.pop();
        
        char operate = this->operators.pop();
        int resultOfOp = Operator::operation(op1, op2, operate);
        this->numbers.push(resultOfOp);
        this->postfixExpression += operate;
    }
    else if (mode == 2)
    {
        op1 = this->numbers.pop();
        op2 = this->numbers.pop();
        
        char operate = this->operators.pop();
        int resultOfOp = Operator::operation(op1, op2, operate);
        this->numbers.push(resultOfOp);
    }
    else
        throw "MODE VALUE INVALID FOR OPERATION";
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

std::string Calculator::toPostfixNoEval(std::string eq)
{
    std::string post = "";
    for (int i = 0; i < eq.length(); i++)
    {
        if (isOperand(eq[i]))
        {
            std::string numHold = "";
            numHold += eq[i];
            while(isOperand(eq[i+1]))
            {
                i++;
                numHold += eq[i];
            }
            post += numHold;
            post.append("$");
        }
        else if (isOperator(eq[i]))
        {
            switch (eq[i])
            {
                case '(':
                    this->operators.push('(');
                    break;
                case '*':
                case '/':
                case '%':
                case '+':
                case '-':
                    if (this->operators.getStackCount() == 0)
                        this->operators.push(eq[i]);
                    else
                    {
                        if (Operator::getPriority(this->operators.rear()) <= Operator::getPriority(eq[i]))
                            this->operators.push(eq[i]);
                        else
                        {
                            while (this->operators.getStackCount() > 0 && Operator::getPriority(eq[i]) < Operator::getPriority(this->operators.rear()))
                                post += this->operators.pop();
                            this->operators.push(eq[i]);
                        }
                    }
                    break;
                case ')':
                    while (this->operators.rear() != '(')
                        post += this->operators.pop();
                    this->operators.pop();
                    
            }
        }
    }
    while(!this->operators.isEmpty())
    {
        post += this->operators.pop();
    }

    return post;
}
