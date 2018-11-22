#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <float.h>

const int INF_ROOTS = 100;

int SolveLinear (double b, double c, double * x1);

int SolveSquare (double a,double b,double c, double * x1, double * x2);

/**
	@function
	Solution of linear equation
	@param b - coefficient at x
	@param c - free member
	@param x1 -  pointer to root of linear equation
	@brief compares coefficients to 0
	returns 0,1 or INF_ROOTS depending on the result
*/


int SolveLinear (double b, double c, double * x1)
{
	if ( !isfinite(b) || !isfinite(c) || !isfinite(* x1) )
	{
		printf ("Error! incorrect data,try again\n");
		return -1;
	}
	if ( (fabs(b) < DBL_EPSILON) && (fabs(c) < DBL_EPSILON) ) 
	return INF_ROOTS;
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
	@param a - coefficient at x
	@param b - coefficient at x
	@param c - free member
	@param x1 - pointer to root of square equation
	@param x2 - pointer to root of square equation
	@brief compares a to 0
	if a > 0 calculates D(discriminant of the equation) 
	compares D to 0
	returns 0,1 or 2 depending on the result
*/


int SolveSquare (double a,double b,double c, double * x1, double * x2)
{
	if ( !isfinite(a) || !isfinite(b) || !isfinite(c) || !isfinite(* x1) || !isfinite(* x2) )
	{
		printf ("Error! incorrect data,try again\n");
		return -1;
	}
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

