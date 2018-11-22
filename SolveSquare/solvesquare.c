// programm solve square
// 1.10.2018


#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

const int INF_ROOTS = 100;

/**
	@function
	Display text for user to help write data 

*/

void InputClause ()
{
	printf ("SolveSquare. 1.10.2018\na*x^2+b*x+c\nEnter a, b, c\n");	
}


/**
	@function
	Solution of linear equation
	@param b, c 

*/


int SolveLinear (double b, double c, double * x1)
{
	assert (isfinite( b ));
	assert (isfinite( c ));
	if ( (fabs(b) < DBL_EPSILON) && (fabs(c) < DBL_EPSILON) ) 
	return 100;
	if ( (fabs(b) < DBL_EPSILON) && (fabs(c) > DBL_EPSILON) ) 
	return 0;
	if ( (fabs(b) > DBL_EPSILON) && (fabs (c) > DBL_EPSILON) ) 
	{
		*x1 = -c/b;
		return 1;
	}
}


/**
	@function
	Solution of square equation
	@param a, b, c, x1, x2 

*/


int SolveSquare (double a,double b,double c, double * x1, double * x2)
{
	assert (isfinite( a ));
	assert (isfinite( b ));
	assert (isfinite( c ));
	if ( fabs(a) < DBL_EPSILON ) 
	return SolveLinear (b, c, x1);
	else
	{
		double D = 0;
		D = (b*b - 4*a*c);
		if (D < 0) return 0;
		if (fabs(D) < DBL_EPSILON) 
		{	
			*x1 = -b/(2*a);
			return 1;
		}
		if (D > 0) 
		{
			*x1 = ( -b + sqrt(D) )/(2*a);
			*x2 = ( -b - sqrt(D) )/(2*a);
			return 2;
		}
	}
}


/**
	@function
	main function. Read and check data, brings other functions together

*/


int main ()
{
	double a = NAN, b = NAN, c = NAN, x1 = 0, x2 = 0; 
	InputClause (); 
	scanf ("%lg %lg %lg", &a, &b, &c);
	if ((a != a) || (b != b) || (c != c))
	{
		printf (" ERROR!!! incorrect data entered\n");
	}
	assert (isfinite( a ));
	assert (isfinite( b ));
	assert (isfinite( c ));
	
	int nroots = SolveSquare (a, b, c, &x1, &x2);
	
	assert (isfinite ( x1 ));
	assert (isfinite ( x2 ));
	
	switch ( nroots )
	{
		case INF_ROOTS: printf ("infinite number of roots");	break;
		case 0: printf ("no roots");	break;
		case 1: printf ("one root\n%lg", x1);	break;
		case 2: printf ("two roots\n%lg %lg", x1, x2);	break;
	}
}
