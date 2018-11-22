#include <stdio.h>
#include <io.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
////--------------------------------------------------------------------------------------------------------

struct line
{
	char * linebeg;
	int sizeline;
};

////--------------------------------------------------------------------------------------------------------

int linestemper_alph (const void * x1, const void * x2);
int linestemper_revers (const void * x1, const void * x2);
int numlines ( char * data );
int linebegin ( struct line * pointers, char * data, int size );
int fsize (FILE * onegin);
int do_sorting(struct line * pointers, const int count, const int sort);
int repchar ( char * data, char a, char b );

////--------------------------------------------------------------------------------------------------------

/** 
	@function linestemper_alph 
	@brief comparator for qsort
	compares two strings of letters
*/
int linestemper_alph (const void * x1, const void * x2)
{
	char * s1 = (*(struct line *) x1).linebeg;
	char * s2 = (*(struct line *) x2).linebeg;
	int c1 = 0;
	int c2 = 0;
	//printf("%d %s\n", (*(struct line *) x1).sizeline, (*(struct line *) x1).linebeg);
	while ( s1[c1] != '\0' || s2[c2] != '\0' )
	{
		if ( isalpha(s1[c1]) && isalpha(s2[c2]) )
		{
			if ( (islower(s1[c1]) && islower(s2[c2])) || (isupper(s1[c1]) && isupper(s2[c2])) )
			{
				if ( s1[c1] != s2[c2] ) return ( s1[c1] - s2[c2] );
				else
				{   
					c1++;
			    	c2++;  
				}	
			}
			else
			{
				if ( tolower(s1[c1]) == tolower(s2[c2]) )
				{
					c1++;
					c2++;
				}
				else return ( tolower(s1[c1]) - tolower(s2[c2]) );
			}	
		}
		else if ( !isalpha(s1[c1]) && isalpha(s2[c2]) ) c1++;
		else if ( !isalpha(s2[c2]) && isalpha(s1[c1]) ) c2++;
		else if ( !isalpha(s2[c2]) && !isalpha(s1[c1]) )
		{
			c1++;
			c2++;
		}
	}
	return 0;
}
 
 ////--------------------------------------------------------------------------------------------------------

/** 
	@function linestemper_revers 
	@brief comparator for qsort
	compares two strings of letters in reverse
*/
int linestemper_revers (const void * x1, const void * x2)
{
	char * s1 = (*(struct line *) x1).linebeg;
	char * s2 = (*(struct line *) x2).linebeg;
	
	int c1 = (*(struct line *) x1).sizeline - 1;
	int c2 = (*(struct line *) x2).sizeline - 1;
	while ( c1 != -1 || c2 != -1 )
	{
		if ( isalpha(s1[c1]) && isalpha(s2[c2]) )
		{
			if ( (islower(s1[c1]) && islower(s2[c2])) || (isupper(s1[c1]) && isupper(s2[c2])) )
			{
				if ( s1[c1] != s2[c2] ) return ( s1[c1] - s2[c2] );
				else
				{   
					c1--;
			    	c2--;  
				}	
			}
			else
			{
				if ( tolower(s1[c1]) == tolower(s2[c2]) )
				{
					c1--;
					c2--;
				}
				else return ( tolower(s1[c1]) - tolower(s2[c2]) );
			}	
		}
		else if ( !isalpha(s1[c1]) && isalpha(s2[c2]) ) c1--;
		else if ( !isalpha(s2[c2]) && isalpha(s1[c1]) ) c2--;
		else if ( !isalpha(s2[c2]) && !isalpha(s1[c1]) )
		{
			c1--;
			c2--;
		}
	}
	return 0; 
}

////--------------------------------------------------------------------------------------------------------

/** 
	@function repchar
	@param char * data - array of onegin text
	@param a - replaceable character
	@param b - character to replace
	@brief counts quantity of '\n' in data
	quantity of '\n' =  quantity of lines
	replaces '\n' to '\0' in data
	returns count = quantity of lines
*/
int repchar ( char * data, char a, char b )
{
	if (data == NULL)
	{
		return -1;
	}
	
	int count = 1;
	int e = 0;
	while ( data[e] != '\0' )
	{
		if ( data[e] == b ) 
		{
			count ++;
			data[e] = a;
		}
		e++;
	}
	return count;
}

////--------------------------------------------------------------------------------------------------------

/** 
	@function linebegin
	@param char ** pointers - array of pointers to the beginning of the lines
	@param char * data - array of onegin text
	@param int size - size of file
	@brief writes the addresses of the started lines to an array of pointers to strings
*/
int linebegin ( struct line * pointers, char * data, const int size )
{
	if ( pointers == NULL || data == NULL || size < 0)
	{
		return -1;
	}
	
	int j = 0;
	int count = 0;
	pointers[0].linebeg = data;
	for ( int i = 0; i <= size; i++ )
	{
		count++;
		if (data[i] == '\0') 
		{
			pointers[j+1].linebeg = data + i + 1;
			pointers[j].sizeline = count;
			j += 1;
			count = 0;
		} 
	}
	pointers[j].linebeg = data + size + 1;
	return 0;
}

////--------------------------------------------------------------------------------------------------------

/** 
	@function fsize
	@param FILE * onegin - original file
	@brief counts size of file
	returns size
*/
int fsize(FILE * onegin)
{
	if ( onegin == NULL )
	{
		return -1;
	}
	
	int size = 0;
	int curpos = 0;
	curpos = ftell(onegin);
	fseek (onegin, 0, SEEK_END);
	size = ftell(onegin);
	fseek (onegin, 0, curpos);
	return size;
}

////--------------------------------------------------------------------------------------------------------

/**
	@function do_sorting
	for beginning of sorting
	@param char ** pointers - array of pointers to the beginning of the lines
	@param const int count - quantity of lines
	@param const int sort - selected sort
	@brief sorts file depending on the selected sort
	makes new sorted file
*/
int do_sorting(struct line * pointers, const int count, const int sort)
{
	if ( (sort != 1 && sort != 2) || pointers == NULL || count <= 0)
	{
		return -1;
	}
	
	if ( sort == 1 )
	{

		qsort ( pointers, count, sizeof (struct line ), linestemper_alph);  
		FILE * Oneginsort1 = fopen ("Oneginsort_alphabetically.txt", "w");
		if (Oneginsort1 == NULL)
		{
			printf ("fopen failure: returned NULL\n");
			return -1;
		}
		for (int i = 0; i < count; i++)                            
			fprintf (Oneginsort1, "%s\n", pointers[i].linebeg);
		fclose (Oneginsort1);
		printf ("file sorted\nname of new file sorted Oneginsort_alphabetically: Oneginsort_alphabetically.txt\n");
		return 0;											  
	}
	
	if ( sort == 2 )
	{
		qsort ( pointers, count, sizeof (struct line ), linestemper_revers);  
		FILE * Oneginsort2 = fopen ("Oneginsort_inreverse.txt", "w");
		for (int i = 0; i < count; i++)                            
			fprintf (Oneginsort2, "%s\n", pointers[i].linebeg);
		fclose (Oneginsort2);
		printf ("file sorted\nname of new file sorted in reverse: Oneginsort_inreverse.txt");
		return 0;											  
	}
}

////--------------------------------------------------------------------------------------------------------

/**
	@function complete_sorting
	@param FILE * onegin - original file
	@param int sort - selected sort
	@brief connects and tests functions
	creates the necessary parameters
*/
int complete_sorting ( FILE * onegin,  int sort )
{
	int size = fsize(onegin);                                    
	if ( size == -1 )
	{
		printf ("Error! incorrect size of file");
		return -1;
	}
	char * data = NULL;                                           
	data = (char *) calloc (size + 1, sizeof (char));
	fread ( data, sizeof(char), size, onegin);					                  
	int count = repchar ( data, '\0', '\n' );
	if ( count == -1 )
	{
		printf ("Error! incorrect file");
		return -1;
	}
	struct line * pointers = NULL;
	pointers = (struct line *) calloc (count + 1, sizeof (struct line ));
	int retlineb = linebegin ( pointers, data, size );  
	if (retlineb == -1) 
	{
		printf ("Error! incorrect arguments");
		return -1;
	}                       
	int dosorting = do_sorting( pointers, count, sort );
	if (dosorting == -1)
	{
		printf ("Error! incorrect arguments");
		return -1;
	}						   
	free (pointers);                                               
	free (data);
	fclose (onegin);  
}

////--------------------------------------------------------------------------------------------------------

/** 
	@function main
	@brief opens text file
	makes new sorted file in same directory
*/
int main ()
{
	printf ("Sort Onegin(in english)\nchoose sorting:\n1)alphabetically(enter 1)\n2)conversely(enter 2)\n");
	int sort = 0;												 
	scanf ("%d", &sort);
	if ( sort != 1 && sort != 2)
	{
		printf ("Error! please choose correct sorting,try again\n");
		return -1;
	}                                              
	FILE * onegin = fopen( "onegin.txt", "rb" );                         
	if (onegin == NULL)                                            
	{
		printf ("ERROR!!! incorrect file");
		return -1;
	}
	complete_sorting ( onegin, sort );                                                       
	return 0;
}
