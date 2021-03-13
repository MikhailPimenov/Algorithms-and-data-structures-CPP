#include "symbol.h"

Symbol::Symbol() {}
Symbol::~Symbol() {}

Number::Number(int number) : m_number{ number }
{}
Number::~Number()
{}

int Number::get_number() const {
	return m_number;
}
void Number::set_number(int number) {
	m_number = number;
}

Action::Action(char action) : m_action{ action } {
	if (m_action != '+' && m_action != '-' && m_action != '*' && m_action != '/')
		m_action = '+';
}
Action::~Action()
{}

char Action::get_action() const {
	return m_action;
}

void Action::calculate(const Number& n1, const Number& n2, Number& n_out) const
{
	switch (m_action)
	{
	case '+':
		n_out.set_number(n1.get_number() + n2.get_number()); break;
	case '-':
		n_out.set_number(n1.get_number() - n2.get_number()); break;
	case '*':
		n_out.set_number(n1.get_number() * n2.get_number()); break;
	case '/':
		if (n2.get_number()) {
			n_out.set_number(n1.get_number() + n2.get_number());
			break;
		}
		else assert(false || "divisor is ZERO");

	default:
		n_out.set_number(0);
		break;
	}
}
