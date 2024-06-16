
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
		bool isQR;
		bool isC;
	public:
		float getX() const { if (isC) throw this;  return x1; }
		float getX1() const { if (isC) throw this;  return x1; }
		float getX2() const { if (!isQR || isC) throw Root{ 0, 0 }; return x2; }

		bool isQuadraticRoot() const { return isQR; }
		bool isClear() const { return isC; }
		
		Root() : x1(0), x2(0), isQR(false), isC(true) {};
		Root(float value) : x1(value), x2(0), isQR(false), isC(false) {};
		Root(float value1, float value2) : x1(value1), x2(value2), isQR(true), isC(false) {};
		friend std::ostream& operator<<(std::ostream& out, const Root& root)
		{
			if (root.isClear())
				return out << "[ None ]";

			out << '[' << root.x1;
			if (root.isQuadraticRoot())
				out << " : " << root.x2;
			return out << ']';
		}
	};

	Equation(float pValueA, float pValueB) : a(pValueA), b(pValueB) { if (pValueA == 0) throw std::invalid_argument("A can`t be 0"); };
	virtual Equation::Root equationRoot() const = 0;

	virtual std::ostream& print(std::ostream& out = std::cout) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const Equation& eq) { return eq.print(out); }
};

class LinearEquation : public Equation
{
public:
	LinearEquation(float pValueA, float pValueB) : Equation(pValueA, pValueB) {}
	Root equationRoot() const override final;

	std::ostream& print(std::ostream& out = std::cout) const override { return out << '(' << a << "x + " << b << ')'; }
};

Equation::Root LinearEquation::equationRoot() const
{
	return Root{-b / a};
}

class QuadraticEquation : public Equation
{
private:
	float c;
public:
	QuadraticEquation(float pValueA, float pValueB, float pValueC) : Equation(pValueA, pValueB), c(pValueC) {}
	float delta() const { return b * b - 4 * a * c; }
	Root equationRoot() const override final;

	std::ostream& print(std::ostream& out = std::cout) const override { return out << '(' << a << "x^2 + " << b << "x + " << c << ')'; }
};

Equation::Root QuadraticEquation::equationRoot() const
{
	float d = delta();
	if (d < 0)
		return Root{};
	float x1 = (-b - sqrtf(d)) / (2 * a);
	float x2 = (-b + sqrtf(d)) / (2 * a);
	return Root{ x1, x2  };
}

int main()
{
	LinearEquation lEq(5, 2);
	std::cout <<  lEq << " : " << lEq.equationRoot() << std::endl;
	try
	{
		lEq.equationRoot().getX2();
	}
	catch (Equation::Root)
	{
		std::cout << "X2 in root is not existe\n";
	}

	QuadraticEquation qeq{ 10, 3, 0 };
	std::cout << qeq << " : " << qeq.equationRoot() << std::endl;

	QuadraticEquation qeqError(10, 3, 30);
	std::cout << qeqError << " : " << qeqError.equationRoot() << std::endl;

	return 0;
}


