#include "reversed_polish_notation4.h"

int reversed_polish_notation4(const std::vector<Symbol*>& sequence) {
    std::stack<Number> stack;

    for (const auto symbol : sequence) {
        const auto* action = dynamic_cast<Action*>(symbol);
        if (action) {
            Number n2 = stack.top();
            stack.pop();
            Number n1 = stack.top();
            stack.pop();

            Number result(0);
            action->calculate(n1, n2, result);

            stack.push(result);
        }
        else stack.push(*dynamic_cast<Number*>(symbol));
    }

    return stack.top().get_number();
}
