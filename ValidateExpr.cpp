
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Expression {

public:
	Expression() = default;
	void setExpression(string str) {
		expression = str;
	}
	void clearExpression() { expression = ""; };
	bool checkIfOpeningBrace(char);
	char getClosingBrace(char);
	bool evaluateExpression();
	void clearStack();

private:
	string expression;
	stack<char> evaluator;
	char top;
};

bool Expression::checkIfOpeningBrace(char pSymbol) {

	if (pSymbol == '(' || pSymbol == '[' || pSymbol == '{')
		return true;
	else
		return false;
}

char Expression::getClosingBrace(char pOpenBrace) {

	if (pOpenBrace == '(')
		return ')';
	else if (pOpenBrace == '[')
		return ']';
	else if (pOpenBrace == '{')
		return '}';
	else
		return '*';

}

void Expression::clearStack() {

	while (!evaluator.empty())
		evaluator.pop();
}

bool Expression::evaluateExpression() {

	for (size_t i = 0; i < expression.length(); i++) {
		if (checkIfOpeningBrace(expression[i])) {
			evaluator.push(expression[i]);
		}
		else {		
			if (evaluator.empty())
				return false;

			top = evaluator.top();
			evaluator.pop();
			if (getClosingBrace(top) != expression[i])
				return false;
		}
	}

	if (evaluator.empty())
		return true;
	else
		return false;
}

int main() {

	int tests;
	string elts = "";
	Expression object;

	cin >> tests;
	while (tests--) {

		cin >> elts;
		object.setExpression(elts);

		if (object.evaluateExpression())
			cout << "balanced" << endl;
		else
			cout << "not balanced" << endl;

		elts = "";
		object.clearExpression();
		object.clearStack();

	}

	return 0;
}