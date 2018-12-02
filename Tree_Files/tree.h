#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char elem_t;

struct Node
{
	elem_t * value;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
};

typedef struct Node node_t; 

node_t * Init_Node (elem_t * value, node_t * parent);

int Node_Ok (node_t * node, node_t * parent);

int Tree_Destruct(node_t * node);

int Tree_Printf(node_t * node);
