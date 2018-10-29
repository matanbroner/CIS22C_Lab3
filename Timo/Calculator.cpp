// File: Calculator.cpp
// Last edit: 10/28/2018
#include "Calculator.h"

Calculator::Calculator()
{
	infix = promptInfix();
}


Calculator::~Calculator()
{
}

std::string Calculator::promptInfix()
{
	std::string expression;
	bool valid = false;
	
	while (valid == false) {
		std::cout << std::endl << "Enter infix expression:" << std::endl;
		try {
			std::cin >> expression;
			//std::getline(std::cin, expression);
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw std::string("Invalid expression.\n");
			}
			else {
				valid = isValidExpression(expression);
			}
		} catch (std::string msg) {
			std::cout << "Error: " << msg << std::endl;
		}
	}

	return std::string(expression);
}

std::string Calculator::infixToPostfix(std::string infix)
{
	Stack<char> ops;
	std::string postfix = "";
	int n = infix.size();

	infix += ")";
	ops.push('(');

	for (int i = 0; i < n; i++) {
		if (infix[i] >= '0' && infix[i] <= '9') {
			//postfix += infix[i];
			//postfix += " ";

			int counter = 0;
			bool isInt = true;
			// loop while isInt to grab mutli-digit numbers
			for (int j = i; isInt == true; j++) {
				if (isOperand(infix[j])) {
					postfix += infix[j];
				} else {
					isInt = false;
				}
				counter++;
			}
			postfix += ' ';
			i += counter-2;
		}
		else {
			if (isOperator(infix[i])) {
				while (!ops.isEmpty() && ops.top() != '(' && hasSameOrHigherPrecedence(infix[i], ops.top())) {
					postfix += ops.pop();
					postfix += " ";
				}
				ops.push(infix[i]);
			}
			if (infix[i] == '(')
				ops.push(infix[i]);

			if (infix[i] == ')') {
				while (!ops.isEmpty() && ops.top() != '(') {
					postfix += ops.pop();
					postfix += " ";
				}
				if (!ops.isEmpty())
					ops.pop();
			}
		}

	}
	while (!ops.isEmpty()) {
		if (ops.top() == '(') {
			ops.pop();
		}
		else {
			postfix += ops.pop();
			postfix += " ";
		}
	}

	if (postfix[postfix.size()-1] == ' ')
		postfix.resize(postfix.size() - 1);

	return postfix;
}

std::string Calculator::infixToPrefix(std::string infix)
{
	// safety check: prevent invalid expression--user SHOULD have called isValidExpression()
	try {
		if (!isValidExpression(infix)) {
			std::cout << "Error: invalid expression passed, expression not converted." << std::endl;
		}
	} catch (std::string msg) {
		std::cout << "Error: " << msg << std::endl;
		return infix;
	}

	int size = infix.size();

	// reverse infix
	infix = reverse(infix);

	// flip parenthesis
	for (unsigned int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(') infix[i] = ')';
		else if (infix[i] == ')') infix[i] = '(';
	}
		
	std::string prefix = infixToPostfix(infix);

	// reverse postfix
	prefix = reverse(prefix);

	return prefix;
}

int Calculator::evaluatePostfix(std::string postfix)
{
	Stack<int> stack;
	Queue<char> queue;

	int a, b;
	int count = 0;
	int size = postfix.size();

	std::string integer = "";

	// enqueue postfix
	for (int i = 0; i < size; i++)
		queue.enqueue(postfix[i]);

	while (count < size) {
		// grab digits until whitespace
		if (isOperand(queue.front())) {
			while (isOperand(queue.front())) {
				integer += queue.dequeue();
				count++;
			}
		}
		// convert to int and push integer
		if (integer != "") {
			stack.push(stoi(integer));
			integer = "";
		}

		// after grabbing all digits: double check isOperator, else delete whitespace
		if (isOperator(queue.front())) {  // is operator
			// pop first two integers to evaluate with operator
			b = stack.top();
			stack.pop();
			a = stack.top();
			stack.pop();

			// find operator, evaluate, and push answer
			switch (queue.dequeue()) {  // dequeue both returns operator and removes it from queue
			case '+':
				stack.push(a+b);
				break;
			case '-':
				stack.push(a-b);
				break;
			case '*':
				stack.push(a*b);
				break;
			case '/':
				if (b == 0)
					throw std::string("Integer division by zero.");
				else
					stack.push(a/b);
				break;
			case '%':
				stack.push(a%b);
				break;
			}
		}
		else {  // is ' ' so we remove this whitespace
			queue.dequeue();
		}
		count++;
	}

	// last remaining item in stack will be the answer
	return stack.top();
}

int Calculator::evaluatePrefix(std::string prefix)
{
	Stack<char> stack;

	int length = prefix.size();
	std::string integer = "";
	int a, b;

	while (length >= 0) {
		if (isOperand(prefix[length])) {
			while (isOperand(prefix[length])) {
				integer += prefix[length];
				length--;
			}
			// convert to int and push integer
			integer = reverse(integer);
			stack.push(stoi(integer));
			integer = "";
		} else {
			if (stack.stackCount()>1 && prefix[length] != ' ') {
				a = stack.top();  // a first instead of b
				stack.pop();
				b = stack.top();
				stack.pop();
				switch (prefix[length])	{
				case '+':
					stack.push(a+b);
					break;
				case '-':
					stack.push(a-b);
					break;
				case '*':
					stack.push(a*b);
					break;
				case '/':
					if (b == 0)
						throw std::string("Integer division by zero.");
					else
						stack.push(a/b);
					break;
				case '%':
					stack.push(a%b);
					break;
				}
			}
		}
		length--;
	}
	return stack.top();
}

std::string Calculator::reverse(std::string s)
{
	int length = s.size();
	Queue<char> queue;

	for (int i = 0; i < length; i++)
		queue.enqueue(s[i]);

	for (int i = length; i > 0; i--)
		s[i-1] = queue.dequeue();
	return s;
}

int Calculator::opWeight(char c)
{
	if (c == '+' || c == '-') {
		return 1;
	}
	else
		return 2;
}

bool Calculator::isOperator(char c)
{
	switch (c) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool Calculator::isOperand(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool Calculator::isValidExpression(std::string infix)
{
	// check (), disallow sequential operators, disallow decimals, disallow alpha

	int length = infix.size();
	int operands = 0;
	std::string integer;

	if (length < 1) {
		throw std::string("No expression input.");
		return false;
	}

	Stack<char> stack;
	Queue<char> queue;

	for (int i = 0; i < length; i++)
		queue.enqueue(infix[i]);

	if (!isOperand(queue.front())) {
		if (!isOpeningParenthesis(queue.front())) {
			std::cout << queue.front() << std::endl;
			throw std::string("Expression must start with an integer or opening parenthesis.");
			return false;
		}
	}
	
	while (!queue.queueEmpty()) {
		if (isOperand(queue.front())) {
			while (!queue.queueEmpty() && isOperand(queue.front())) {
				integer += queue.dequeue();  // dequeue as many digits are in number into integer
			}
			if (integer != "") {
				operands++;  // if operands < 2 by the end of the loop: invalid
				integer == "";  // clear integer for next operand
			}
		} else if (!queue.queueEmpty()) {  // when not operand, expect operator
			if (queue.front() == '(' || queue.front() == ')') {
				stack.push(queue.dequeue());  // save parenthesis to check validity after
			} else if (isOperator(queue.front())) {
				queue.dequeue();  // is operator, but not parenthesis, so remove

				// check if next is operator (disallow sequential operators)
				if (!queue.queueEmpty() && isOperator(queue.front())) {
					throw std::string("Expression cannot contain two sequential operators.");
					return false;
				}
			} else {
				// if queue.front() is not an operand or an operator: invalid
				throw std::string("Expression contains invalid characters.");
				return false;
			}
		}
	}

	if (operands < 2) {
		throw std::string("Expression must contain at least two operands.");
		return false;
	}

	// parenthesis validifier
	if (stack.isEmpty())
		return true;  // if no parenthesis: valid

	int close = 0;

	while (!stack.isEmpty()) {
		if (stack.pop() == ')') {
			close++;
		} else {
			if (close == 0) {  // if we have a ( but there is no ) to match: invalid
				throw std::string("Expression contains invalid parenthesis.");
				return false;
			}
			close--;
		}
	}

	if (close != 0) {  // if there are any ) not paired with (: invalid
		throw std::string("Expression contains invalid parenthesis.");
		return false;
	}

	return true;
}

bool Calculator::isOpeningParenthesis(char c)
{
	if (c == '(')
		return true;
	return false;
}

bool Calculator::isClosingParenthesis(char c)
{
	if (c == ')')
		return true;
	return false;
}

bool Calculator::hasSameOrHigherPrecedence(char a, char b)
{
	int one = opWeight(a);
	int two = opWeight(b);

	if (one == two)
		return true;
	if (one < two)
		return true;
	return false;
}
