#include <iostream>
#include <functional>
#include<vector>
#include<string>
#include "Array.hpp"

void foo() {
	std::cout << "foo()";
}

void poo() {
	std::cout << "poo()";
}

double sum(double num1, double num2) {
	return num1 + num2;
}

double multiply(double num1, double num2) {
	return num1 * num2;
}

double divide(double num1, double num2) {
	return num1 / num2;
}

double sumAB(double A, double B) {
	if (A > B) std::swap(A, B);
	double result = 0.;
	for (double i = 0; i <= B; ++i)
		result += i;
	return result;
}

void do_every(std::vector<std::function<double(double, double)>> funcs, double num1, double num2) {
	for (size_t i = 0; i < funcs.size(); ++i)
		std::cout << i + 1 << ". " << funcs[i](num1, num2) << std::endl;
}

int main() {
	setlocale(LC_ALL, "russian");
	int n;
	//class std::function
	
	std::function<void()> f1;
	f1 = foo;
	f1();
	std::cout << std::endl;
	f1 = poo;
	f1();
	std::cout << std::endl;

	std::function<double(double, double)> f2;
	f2 = sum;
	std::cout << "1. f2(5, 2) = " << f2(5, 2) << std::endl;
	f2 = multiply;
	std::cout << "2. f2(5, 2) = " << f2(5, 2) << std::endl;

	//Массив функций

	do_every({sum, multiply, divide, sumAB}, 10, 2);

	//Лямбда-функции / Лямбда-выражения / Анонимные(безымянные) функции
	std::function<void(std::string)> f3(
		[](std::string name) {
		std::cout << "Hi, " << name << "!\n";
		}
	);
	f3("Valentin");

	n = 2;
	std::function<bool(double)> f4(
		[&n](double num) {
			return num > n;
		}
	);

	if (f4(1))
		std::cout << "More then n\n";
	else
		std::cout << "Not more then n\n";

	//Callback-функции
	Array<int> arr{10, 7, 5, 6, 1, 0, 14 };
	std::cout << arr << std::endl;
	
	std::cout << arr.every([](const int& el) {
		if(el % 2 == 0)
		return el;
		return 0;
		}) << std::endl;
	
	
	
	
	arr.for_each([](int& el) {
		if (el % 2 == 0)
			el = 0;
		});
	std::cout << arr << std::endl;

	Array<int> filtered_arr = arr.filter([](const int& el) {
		static int counter = 0;
		return ++counter <= 3;
		});

	std::cout << filtered_arr << std::endl;

	return 0;
}