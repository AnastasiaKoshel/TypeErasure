// Function.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>



void function()
{
	std::cout << 1 << std::endl;
}
struct Functor
{
	std::string String;
	void operator()()
	{
		std::cout << String << std::endl;
	}
};
class Action
{
private:
	struct Concept {//basic
		virtual ~Concept() {}
		virtual void operator()() = 0;
	};
	template<typename T>
	struct Model : Concept {//know actual type
		Model(T const & value) : x(value) {}
		void operator ()() override{
			x();
		}
		T x;
	};
	Concept *y;
public:
	template<typename T>
	Action(T && value) {
		*this = value;
	}
	template<typename T>
	Action& operator=(T&& value)
	{
		y = new Model <T>(value);
		return *this;
	}
	void operator()()
	{
		(*y)();
	}

};

int main()
{
	Action action = function;
	action();//1
	action = Functor{ "qqq" };
	action();//qqq
	Action action2 = action;
	action = Functor{ "www" };
	action2();//qqq
	action();//www
	return 0;
}