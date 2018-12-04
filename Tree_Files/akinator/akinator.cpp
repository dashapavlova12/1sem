#include "akinator.h"

const int BUF = 512;

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
	char symbol = ' ';
	char buf[BUF] = " ";
	fscanf (database, "%s", buf);
	if (strcmp (buf, "{") != 0 || strcmp(buf, "{}") == 0)
		return NULL;
	fscanf (database, "%[ ]", buf);
	fscanf (database, "%[^'{}]", buf);
	fscanf (database, "%c", &symbol);
	node_t * node = Init_Node(buf, parent);
	node -> left = read_database(database, node);
	node -> right = read_database(database, node);
	fscanf (database, "%s", buf);
	if (strcmp (buf, "}") != 0)
	{
		return NULL;
	}
	return node;
}

int printf_file (node_t * node, FILE * database)
{
	if (!node || database == NULL)
		return -1;
	fprintf (database, " { %s'", node -> value);
	
	if (node -> left != NULL) printf_file (node -> left, database);
	else fprintf(database, "{}");
	
	if (node -> right != NULL) printf_file (node -> right, database);
	else fprintf(database, " {}");
	
	fprintf (database, " }");
	return 0;
}

int graphviz (node_t * root)
{
	FILE * file = fopen ("tree.gv", "w");
	fprintf(file, "digraph G {\n");
	print_dot(file, root);
	fprintf(file, "}");
	fclose(file);
	return 0;
}

int print_dot(FILE * file, node_t * node)
{
	if (node == NULL || file == NULL)
	{
		printf("Error");
		return 0;
	}
	

	if (node -> left)
	{
		fprintf(file, "\"%p\" -> \"%p\"\n", node -> value, node -> left -> value);
		print_dot(file, node -> left);
	}
	
	if (node -> right)
	{
		fprintf(file, "\"%p\" -> \"%p\"\n", node -> value, node -> right -> value);
		print_dot(file, node -> right);
	}
	
	return 0;
}

int get_character (node_t * parent, char side)
{
	if (parent == NULL || (side != 'r' && side != 'l'))
	{
		return -1;
	}
	char name[BUF] = " ";
	char differ[BUF] = " ";
	printf ("Who is it?\n");
	scanf ("%*[\n]%[^\n]", name);
	
	printf ("What's the difference?\n");
	scanf ("%*[\n]%[^\n]", differ);
	node_t * description = Init_Node(differ, parent);
	node_t * caracter = Init_Node (name, description);
	if (side == 'r')
	{
		description -> left = parent -> right;
		description -> right = caracter;
		parent -> right = description;
	}
	else 
	{
		description -> left = parent -> left;
		description -> right = caracter;
		parent -> left = description;
	}
	return 0;
}

int do_play (node_t * node)
{
	printf ("Do you want to play?\nyes/no\n");
	char ans[BUF] = " ";
	scanf ("%s", ans);
	if (strcmp(ans,"no") == 0)
	{
		printf ("Nu ladno");
		return -1;
	}
	if (strcmp(ans,"no") !=0 && strcmp(ans,"yes") !=0)
	{
		printf ("Vvedite yes ili no\n");
		return -1;
	}	
	if (strcmp(ans,"yes") == 0)
	{
		questions (node);
	}
	return 0;
}

int questions (node_t * node)
{
	char ans[BUF] = " ";
	printf ("%s?\nyes/no\n", node -> value);
	scanf ("%s", ans);
	if (strcmp (ans, "yes") == 0)
	{
		if (node -> right == NULL)
		{
			printf ("I'm right!!!!");
			return 0;
		}
		questions (node -> right);
	}
	else if (strcmp (ans, "no") == 0)
	{
		if (node -> left == NULL)
		{
			char side;
			if (node -> parent != NULL)
				if (node == node -> parent -> left)
					side = 'l';
				else side = 'r';
			
			get_character(node -> parent, side);
			return 0;
		}
		questions (node -> left);
	}
	else
	{
		printf ("Vvedite yes ili no\n");
		questions (node);
	}
}
