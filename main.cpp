
#include <iostream>



class Equation
{
protected:
	float a, b;
public:
	class Root
	{
		float x1;
		float x2;
		bool isQuadraticRoot = false;
	public:
		float getX() const { return x1; }
		float getX1() const { return x1; }
		float getX2() const { if (!isQuadraticRoot) throw Root{ 0, 0 }; return x2; }
		
		Root(float value) : x1(value), x2(0), isQuadraticRoot(false) {};
		Root(float value1, float value2) : x1(value1), x2(value2), isQuadraticRoot(true) {};
		friend std::ostream& operator<<(std::ostream& out, const Root& root)
		{
			out << root.x1;
			if (root.isQuadraticRoot)
			{
				out << " : " << root.x2;
			}
			return out;
		}
	};

	Equation(float pValueA, float pValueB) : a(pValueA), b(pValueB) {};
	virtual Equation::Root equationRoot() const = 0;
};

class LinearEquation : public Equation
{
public:
	LinearEquation(float pValueA, float pValueB) : Equation(pValueA, pValueB) {}
	Equation::Root equationRoot() const override final;
};


Equation::Root LinearEquation::equationRoot() const
{
	if (a < 0)
		throw Equation::Root{0, 0};
	return Equation::Root{-b / a};
}

class QuadraticEquation : public Equation
{
private:
	float c;
public:
	QuadraticEquation(float pValueA, float pValueB, float pValueC) : Equation(pValueA, pValueB), c(pValueC) {}
	float delta() const { return b * b - 4 * a * c; }
	Equation::Root equationRoot() const override final;
};

Equation::Root QuadraticEquation::equationRoot() const
{
	float d = delta();
	if (d < 0)
	{
		throw Equation::Root{ 0, 0 };
	}
	return Equation::Root{ (-b - sqrtf(d)) / (2 * a), (-b + sqrtf(d)) / (2 * a) };
}

int main()
{
	LinearEquation lEq(5, 2);
	std::cout << lEq.equationRoot().getX() << std::endl;

	try
	{
		std::cout << lEq.equationRoot().getX2() << std::endl;
	}
	catch (LinearEquation::Root)
	{
		std::cout << "Second root is not existe" << std::endl;
	}

	try
	{
		QuadraticEquation qEq(10, 3, 0);
		std::cout << qEq.equationRoot();
	}
	catch (QuadraticEquation::Root)
	{
		std::cout << "Root is not exist";
	}

	return 0;
}


