#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum errors
{
	MEMORY_ERROR = -10,
	POINTER_ERROR,
};

int LABELS_COUNT = 32;

int INITIAL_LINE = 128;

int COMMAND = 128;
 
int checkcom (char * line, FILE * bytecod, FILE * commands, int * labels);

int mem_labels(FILE * commands, int * labels);

int initialize_array(int * labels);
 
int main (int argc, char * argv[])
{
	if (argc != 3)
	{
		printf ("Error!!! Incorrect number of files!");
		return -1;
	}
	int return_check = 0;
    argv[1] = fopen ("commands.txt", "r");
    argv[2] = fopen ("bytecod.txt", "w");
    if(commands == NULL && bytecod == NULL)
    {
    	printf("Error opening files. Check the data.");
    	return POINTER_ERROR;
	}
	
    char * line = (char *)calloc(INITIAL_LINE, sizeof(char));
    int * labels = (int *) calloc(LABELS_COUNT, sizeof(int));
    if (line == NULL && labels == NULL)
    {
    	printf("Error allocating memory.");
    	return MEMORY_ERROR;
	}
	
    return_check = mem_labels(commands, labels); 
    if (return_check == -1)
    {
    	printf("Error. Check the data.");
    	return POINTER_ERROR;
	}
	
    while (fscanf (commands, "%s", line) != EOF)
    {
        return_check = checkcom (line, bytecod, commands, labels);
        if (return_check == -1)
        {
        	printf("Error. Check the data.");
        	return POINTER_ERROR;
    	}
    }
    return 0;
}
 
int mem_labels(FILE * commands, int * labels)
{
    if ( commands == NULL || labels == NULL )
    {
        return -1;
    }
    
    int check_return = 0;
    
    check_return = initialize_array(labels);
    if (check_return == -1)
    {
    	return -1;
	}
	
    char curr_command[COMMAND] = " ";
    int current_index = 0;
    int label = 0;
 	
    while(fscanf(commands, "%s", curr_command) != EOF)
    {
        if (strcmp(curr_command, ":") == 0)
        {
            fscanf(commands, "%d", &label);
            labels[label] = current_index;
        }
        else
        {
            current_index += 1;
        }
        
    }
    fseek(commands, 0, SEEK_SET);
    return 0;
}
 
int initialize_array(int * labels)
{
    if (labels == NULL)
    {
        return -1;
    }
    for (int i = 0; i < LABELS_COUNT; i++)
        labels[i] = -1;
    return 0;
}
 
int checkcom (char * line, FILE * bytecod, FILE * commands, int * labels)
{
	int arg = 0;
	if 0;
    #define DEF_CMD(name, num, CODE_ASM, CODE_CPU)      \
    else if (strcmp(line, name) == 0)                   \
    {                                                   \
        CODE_ASM            							\ 
    }
    #include "commands.h"
}
