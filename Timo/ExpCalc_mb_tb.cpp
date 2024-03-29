// File: ExpCalc_mb_tb.cpp
// Last edit: 10/28/2018

#include "Calculator.h"

int main()
{
	try {
		Calculator calc;

		std::string infix = calc.getInfix();
		std::string postfix = calc.infixToPostfix(infix);
		std::string prefix = calc.infixToPrefix(infix);

		std::cout << std::endl;
		std::cout << "Postfix: " << postfix << std::endl;
		std::cout << "Evaluated Postfix: " << calc.evaluatePostfix(postfix) << std::endl;

		std::cout << std::endl;
		std::cout << "Prefix: " << prefix << std::endl;
		std::cout << "Evaluated Prefix: " << calc.evaluatePrefix(prefix) << std::endl;

		std::cout << std::endl;

	} catch (std::string msg) {
		std::cout << "Error: " << msg << std::endl;
	}

    return EXIT_SUCCESS;
}

