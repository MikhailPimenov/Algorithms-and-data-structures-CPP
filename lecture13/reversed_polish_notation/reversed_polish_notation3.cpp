#include "reversed_polish_notation3.h"

int reversed_polish_notation3(const std::vector<Symbol*>& v)
{
	std::stack < int > stack;
	for (const auto& element : v) {
		auto action = dynamic_cast <Action*>(element);
		if (action) {
			int second = stack.top();
			stack.pop();
			int first = stack.top();
			stack.pop();

			Number result(0);
			action->calculate(Number(first), Number(second), result);
			stack.push(result.get_number());
			continue;
		}
		stack.push(dynamic_cast<Number*>(element)->get_number());
	}
	return stack.top();
}
