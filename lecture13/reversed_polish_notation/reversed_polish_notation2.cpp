#include "reversed_polish_notation2.h"

int reversed_polish_notation2(const std::vector<Symbol*>& array)
{
	std::stack <Number> stack;
	for (const auto& element : array) {
		Action* action = dynamic_cast<Action*>(element);
		if (action) {
			Number number2 = stack.top();
			stack.pop();
			Number number1 = stack.top();
			stack.pop();
			Number result(0);
			action->calculate(number1, number2, result);
			stack.push(result);
		}
		else stack.push(*(dynamic_cast<Number*>(element)));
	}
	return stack.top().get_number();
}
