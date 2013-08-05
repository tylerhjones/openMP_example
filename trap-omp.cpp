/**********************************************************************
* Program:
* Lab OpenMP
* Brother Jones, CS 345
* Author:
* Tyler Jones
* Summary:
* 	This prigram computes a trapezoidal approximation 
*		using integrals that are threaded with openMP.
* Conclusions:
* 	OpenMP is much simpler than pthreads. I feel like many examples 
*		found online could be made even simpler. This library needs easier
*		to access documentation. People going to openmp.org most likely 
*		are looking for OpenMP documentation, not news and stuff about 
*		the organization.
***********************************************************************/
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
/* Demo program for OpenMP: computes trapezoidal approximation to an 
integral*/
const double pi = 3.141592653589793238462643383079;

int main(int argc, char** argv) {
	/* Variables */
	double a = 0.0; /* limits of integration */
	double b = pi; 
	int n = 4194304; /* number of subdivisions = 2^22 */
	double h = (b - a) / n; /* width of subdivision */
	double integral; /* accumulates answer */
	int threadct = 1; /* number of threads to use */
	/* parse command-line arg for number of threads */
	if (argc > 1)
		threadct = atoi(argv[1]);
	double f(double x);
	#ifdef _OPENMP
		cout << "OMP defined, threadct = " << threadct << endl;
	#else
		cout << "OMP not defined" << endl;
	#endif
	integral = (f(a) + f(b))/2.0;
	int i;

	#pragma omp parallel for num_threads(threadct) \
		shared (a, n, h) private(i) reduction(+: integral)
	for(i = 1; i < n; i++) {
		integral += f(a+i*h);
	}
	integral = integral * h;
	cout << "With n = " << n << 
	" trapezoids, our estimate of the integral" <<
	" from " << a << " to " << b << " is " << integral << endl;
}


double f(double x) {
return sin(x);
}