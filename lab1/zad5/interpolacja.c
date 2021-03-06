//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

void interp(double x[10], double y[10], const gsl_interp_type *type, FILE *file){
	double xi, yi;
	gsl_interp_accel *acc 
		= gsl_interp_accel_alloc ();
	gsl_spline *spline 
		= gsl_spline_alloc (type, 10);

	gsl_spline_init (spline, x, y, 10);

	for (xi = x[0]; xi < x[9]; xi += 0.01)
	{
		yi = gsl_spline_eval (spline, xi, acc);
		fprintf (file,"%g %g\n", xi, yi);
	}
	gsl_spline_free (spline);
	gsl_interp_accel_free(acc);
}


int main (void){
	int i;
	double x[10], y[10];
	FILE *input, *output1, *output2, *output3;
	input=fopen("wartosci.txt","w");
	output1=fopen("inter1.txt","w");
	output2=fopen("inter2.txt","w");
	output3=fopen("inter3.txt","w");
	//  printf ("#m=0,S=2\n");

	for (i = 0; i < 10; i++)
	{
		x[i] = i + 0.5 * sin (i);
		y[i] = i + cos (i * i);
		fprintf (input,"%g %g\n", x[i], y[i]);
	}

	//  printf ("#m=1,S=0\n");
	interp(x, y, gsl_interp_polynomial, output1);
	interp(x, y, gsl_interp_cspline, output2);
	interp(x, y, gsl_interp_akima, output3);

	return 0;
}


