#include <iostream>
using namespace std;
#define PI 3.14159265

// расчет ln(x) в интервале x > 1/2
unsigned __stdcall Func1(void* x) {
	long long maxIteration = 800000000;
	double a = (*(double*)x - 1)/(*(double*)x);
	double result = a;
	for (int n = 0; n < maxIteration; n++)
	{
		a *= ((*(double*)x - 1) * (n + 1)) / ((n + 2) * (*(double*)x));
		result += a;
	}
	cout << "Результат функции 1: " << result << endl;
	return 0;
}
// расчет ln(x) в интервале 0 < x <= 2
unsigned __stdcall Func2(void* x) {
	long long maxIteration = 800000000;
	double a = *(double*)x - 1;
	double result = a;
	for (int n = 0; n < maxIteration; n++)
	{
		a *= (-1 * (*(double*)x - 1) * (n + 1)) / (n + 2);
		result += a;
	}
	cout << "Результат функции 2: " << result << endl;
	return 0;
}
// расчет arctg(x) в интервале x < -1
unsigned __stdcall Func3(void* x) {
	long long maxIteration = 600000000;
	double a = (-1 / (*(double*)x));
	double result = a;
	for (int n = 1; n < maxIteration; n++)
	{
		a *= -1 * (2 * n + 1) / ((2 * n + 3) * ((*(double*)x) * (*(double*)x)));
		result += a;
	}
	result += -PI / 2;
	cout << "Результат функции 3: " << result << endl;
	return 0;
}