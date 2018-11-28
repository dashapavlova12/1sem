#include <stdio.h>
#include "Stack.h"
#include <math.h>
#include <string.h>

enum errors 
{
	MEMORY_ERROR = -10,
	POINTER_ERROR,	
};

int END = 100500;

int MEMORY_SIZE = 128;

int LABELS_COUNT = 32;

int COMMAND_INIT = 128;
 
struct CPU
{
    double ax;
    double bx;
    double cx;
    double dx;
    double * memory;
    struct Stack * CPU_STACK;
};
 
int do_programm(struct CPU * MY_CPU, double * commands);
 
int initialize_CPU(struct CPU * MY_CPU);
 
int fsize(FILE * bytecode);
 
int mem_bytecod(FILE * bytecod, double * commands);
 
int ExecuteCom (int com, struct CPU * MY_CPU, double * commands, int * curpos);

int free_processor (double * commands, FILE * bytecod, struct CPU * MY_CPU);
 
int main (int argc, char * argv[])
{
    if (argc != 2)
	{
		printf ("Error!!! 1 file expected");
		return -1;
	}
    struct CPU MY_CPU;
    int check_return = 0;

    initialize_CPU(&MY_CPU);
    if (check_return != 0)
    {
    	printf("An error has occurred. Check the data.");
    	return POINTER_ERROR;
	}

    argv[1] = fopen ("bytecod.txt", "r");
    if (bytecod == NULL)
    {
    	printf("File not found. Check the data.");
    	return POINTER_ERROR;
	}

    int size = fsize(bytecod);
    if (size == POINTER_ERROR)
    {
    	printf("An error has occurred. Check the data.");
    	return POINTER_ERROR;
	}

    double * commands = (double *) calloc(size, sizeof(double));
    if (commands == NULL)
    {
    	printf("An error occurred while allocating memory.");
    	return MEMORY_ERROR;
	}

    check_return = mem_bytecod(bytecod, commands);
    if (check_return == POINTER_ERROR)
    {
    	printf("Incorrect data. Check the data.");
    	return POINTER_ERROR;
	}

    check_return = do_programm(&MY_CPU, commands);
    if (check_return == POINTER_ERROR)
    {
    	printf("An error has occurred. Check the data.");
    	return POINTER_ERROR;
	}
	int free = free_processor (commands, bytecod, &MY_CPU);
	if (free == -1)
	{
		printf ("Incorrect data. Check the data.");
		return MEMORY_ERROR;
	}
    return 0;
}
 
int do_programm(struct CPU * MY_CPU, double * commands)
{
	if (MY_CPU == NULL || commands == NULL)
	{
		return POINTER_ERROR;
	}
	
    int ret = 0;
    int curpos = 0;
    while( ret != END )
    {
        ret = ExecuteCom( commands[curpos], MY_CPU, commands, &curpos );
        if (ret == -1)
        {
             return ret;
		}
    }
    return 0;
}

int initialize_CPU(struct CPU * MY_CPU)
{
    if (MY_CPU == NULL)
    {
     	return POINTER_ERROR;
    }

    MY_CPU -> memory = (double *) calloc (MEMORY_SIZE, sizeof(double));
    
    if (MY_CPU -> memory == NULL)
    {
    	return MEMORY_ERROR;
    }
	
    MY_CPU -> ax = 0;
    MY_CPU -> bx = 0;
    MY_CPU -> cx = 0;
    MY_CPU -> dx = 0;
    MY_CPU -> CPU_STACK = init_stack();
    
 	return 0;
}

int fsize(FILE * bytecod)
{
    if (bytecod == NULL )
    {
        return POINTER_ERROR;
    }
 
    int size = 0;
    int curpos = 0;
    curpos = ftell(bytecod);
    fseek (bytecod, 0, SEEK_END);
    size = ftell(bytecod);
    fseek (bytecod, 0, curpos);
    
    return size;
}

int mem_bytecod(FILE * bytecod, double * commands)
{
    if ( bytecod == NULL || commands == NULL )
    {
        return POINTER_ERROR;
    }

    double curr_command[COMMAND_INIT] = " ";
    int current_index = 0;

    while(fscanf(bytecod, "%lf", curr_command) != EOF)
    {
        commands[current_index] = curr_command;
        current_index += 1;
    }
    fseek(bytecod, 0, SEEK_SET);
    return 0;
}

int ExecuteCom (int com, struct CPU * MY_CPU, double * commands, int * curpos)
{
	if (com <= 0 || MY_CPU == NULL || commands == NULL || curpos == NULL)
	{
	    return -1;
	}
	else
    {
		switch (com)
    	{
   			 #define DEF_CMD(name, num, CODE_ASM, CODE_CPU)  \
    			case(num):                                   \
        		{                                            \
             		CODE_CPU                                 \
        		}
    		 #include "commands.h"
    	}
	return -1;
    }
}

int free_processor (double * commands, FILE * bytecod, struct CPU * MY_CPU)
{
	if (commands == NULL || bytecod == NULL || MY_CPU == NULL)
	{
		return -1;
	}
	fclose (bytecod);
	free (commands);
	free (MY_CPU -> memory);
	return 0;
}
