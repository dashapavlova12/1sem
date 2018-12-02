#include "akinator.h"
#include <errno.h>

int main ()
{
	FILE * database = fopen ("database.txt", "r");
	if (database == NULL)
	{
		perror ("database");
		exit(-1);
	}
	node_t * root = read_database (database, NULL);
	Tree_Printf (root);
}
