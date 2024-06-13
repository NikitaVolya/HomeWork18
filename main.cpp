
#include <iostream>

class Equation
{
protected:
	float a, b;
public:
	Equation(float pValueA, float pValueB) : a(pValueA), b(pValueB) {};
	virtual float equationRoot() const = 0;
};

class LinearEquation : public Equation
{
public:
	LinearEquation(float pValueA, float pValueB) : Equation(pValueA, pValueB) {}
	float equationRoot() const override final { return -b / a; }
};

class QuadraticEquation : public Equation
{
private:
	float c;
public:
	QuadraticEquation(float pValueA, float pValueB, float pValueC) : Equation(pValueA, pValueB), c(pValueC) {}
	float delta() const { return b * b - 4 * a * c; }
	float equationRoot() const override final { return (-b - sqrtf(delta())) / (2 * a); }
};

int main()
{
	LinearEquation lEq(5, 2);
	std::cout << lEq.equationRoot() << std::endl;

	QuadraticEquation qEq(10, 3, -8);
	std::cout << qEq.equationRoot();

	return 0;
}