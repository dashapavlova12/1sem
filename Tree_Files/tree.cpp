#include "tree.h"




/*
	Ïèñàòü êàê ñòåê òîëüêî äîáàâëÿòü 
	ôóíêöèè óäàëåíèÿ óçëà, äîáàâëåíèÿ óçëà,èçìåíåíèÿ value óçëà
	ïåðåõîäà ïî óçëàì, ïðîãðàììêà äëÿ ïå÷àòè äåðåâà
*/



node_t * Init_Node (elem_t * value, node_t * parent)
{
	node_t * node = (node_t *) calloc (1, sizeof(node_t));
	node -> left = NULL;
	node -> right = NULL;
	node -> parent = parent;
	node -> value = value;
	
	return node;
}

int Node_Ok (node_t * node, node_t * parent)
{
	if (node -> value == NULL || node -> parent != parent)
	{
		return -1;
	}
	
	return 0;
}

int Tree_Destruct(node_t * node)
{
	if (node != NULL)
	{
		Tree_Destruct(node -> left);
		Tree_Destruct(node -> right);
		free(node);
	}
	return 0;
}


int Tree_Printf(node_t * node)
{
	printf("{	");
	printf("%s\n", node -> value);
	if (node -> left)	Tree_Printf(node -> left);
	if (node -> right)	Tree_Printf(node -> right);
	printf("}\n");
	return 0;
}




/* 2 ôóíêöèè(äëÿ äåðåâà è óçëà) êîòîðûå âûâîäÿò èõ íà ýêðàí(èëè ïå÷àòàþò â êðàñèâîì ðåäàêòîðå)*/
