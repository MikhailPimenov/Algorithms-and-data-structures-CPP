#pragma once

#include <cassert>

class Symbol
{
protected:
	Symbol();
	virtual ~Symbol();
};

class Number : public Symbol
{
private:
	int m_number;
public:
	Number(int number);
	virtual ~Number() override;

	int get_number() const;
	void set_number(int number);
};

class Action : public Symbol
{
private:
	char m_action;
public:
	Action(char action);
	virtual ~Action() override;

	char get_action() const;
	void calculate(const Number& n1, const Number& n2, Number& n_out) const;
};