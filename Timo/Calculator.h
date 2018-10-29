// File: Calculator.h
// Last edit: 10/28/2018

#ifndef Calculator_h
#define Calculator_h

#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"

class Calculator
{
private:
	std::string infix;

	std::string reverse(std::string s);
	int opWeight(char c);
	bool isOperator(char c);
	bool isOperand(char c);
	bool isOpeningParenthesis(char c);
	bool isClosingParenthesis(char c);

	// return true if a <= b
	bool hasSameOrHigherPrecedence(char a, char b);

	bool isValidExpression(std::string infix);

public:
	Calculator();
	~Calculator();

	// prompt user for infix expression until expression passes isValidExperssion test
	// no negation in infix expression allowed but multidigit integer operands are accepted
	std::string promptInfix();

	// user should call isValidExpression before converting infix
	std::string infixToPostfix(std::string infix);
	std::string infixToPrefix(std::string infix);

	// evaluates and returns result of postfix, returns infix if it is an invalid expression
	int evaluatePostfix(std::string postfix);

	// evaluates and returns result of prefix, returns infix if it is an invalid expression
	int evaluatePrefix(std::string prefix);

	std::string getInfix() { return infix; }
};

#endif
