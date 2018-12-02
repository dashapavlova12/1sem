#include "akinator.h"

int fsize(FILE * database)
{
    if (database == NULL )
    {
        return -1;
    }
 
    int size = 0;
    int curpos = 0;
    curpos = ftell(database);
    fseek (database, 0, SEEK_END);
    size = ftell(database);
    fseek (database, 0, curpos);
    
    return size;
}

node_t * read_database (FILE * database, node_t * parent)
{
	char buf[512] = " ";
	fscanf (database, "%s", buf);
	if (strcmp (buf, "{") != 0)
		return NULL;
	fscanf (database, "%[^{}]", buf);
	node_t * node = Init_Node(buf, parent);
	node -> left = read_database(database, node);
	node -> right = read_database(database, node);
	fscanf (database, "%c", buf);
	if (strcmp (buf, "}") != 0)
		return NULL;	
	return node;
}

int printf_file (node_t * node, FILE * database)
{
	if (!node || database == NULL)
		return -1;
	fprintf (database, "{ %s\n", node -> value);
	printf_file (node -> left, database);
	printf_file (node -> right, database);
	fprintf (database, "}\n");
	return 0;
}
