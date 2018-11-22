
#include "SSwithoutmain.h"

#define UNIT_TEST_SL(what, op, ref)      \
{                                         \
	int result = (what);				  \
	if (result op ref) printf (#what " passed\n"); \
	else printf (#what " is not correct\n"); \
}


#define UNIT_TEST_SS(what, op, ref)		\
{										\
	int result = (what);				  \
	if (result op ref) printf (#what " passed\n"); \
	else printf (#what " is not correct\n"); \
}


int main ()
{
	double x1 = 0;
	double x2 = 0;
	
	UNIT_TEST_SL(SolveLinear (NAN, NAN, NULL), ==, -1);
	
	UNIT_TEST_SL(SolveLinear (0, 0, &x1), ==, INF_ROOTS);
	
	UNIT_TEST_SL(SolveLinear (0, -1, &x1), ==, 0);
	
	UNIT_TEST_SL(SolveLinear (2, 3, &x1), ==, 1);
	
	UNIT_TEST_SS(SolveSquare (NAN, NAN, NAN, NULL, NULL), ==, -1);
	
	UNIT_TEST_SS(SolveSquare (1, 1, 1, &x1, &x2), ==, 0);
	
	UNIT_TEST_SS(SolveSquare (1, 2, 1, &x1, &x2), ==, 1);
	
	UNIT_TEST_SS(SolveSquare (1, 20, 1, &x1, &x2), ==, 2);
}
