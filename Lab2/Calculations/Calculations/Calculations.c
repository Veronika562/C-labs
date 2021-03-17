#include "Calculations.h"
#include <stdio.h>

int main() {
	double x = 0.0;
	int n = 0;
	if (scanf("%lf %d", &x, &n) == 2) {
		printf("%.100lf\n", calc_eps(x, n));
	}
	double eps = 0.0;
	if (scanf("%lf", &eps)) {
		printf("%d\n", calc_n(x, eps));
	}
	return 0;
}

double calc_eps(double x, int n) {
	double right = 0;
	for (int i = 1; i <= n; i++) {
		double a = pow(-1.0, i - 1.0);
		double b = pow(x, 2.0 * i - 1);
		double c = calc_factorial(2 * i - 1);
		double s = sin(x);
		right += pow(-1.0, i - 1.0) * pow(x, 2.0 * i - 1) / calc_factorial(2 * i - 1);
	}
	double k = fabs(sin(x) - right);
	return fabs(sin(x) - right);
}

double calc_factorial(int n) {
	double result = 1;
	for (int i = 1; i <= n; i++) {
		result *= i;
	}
	return result;
}

int calc_n(double x, double eps) {
	double right = 0;
	int i = 0;
	do {
		i++;
		right += pow(-1.0, i - 1.0) * pow(x, 2.0 * i - 1) / calc_factorial(2 * i - 1);
	} while (fabs(sin(x) - right) >= eps);
	return i;
}
