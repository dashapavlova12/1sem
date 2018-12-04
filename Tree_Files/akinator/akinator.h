#include "tree.h"

node_t * read_database (FILE * database, node_t * parent);

int fsize(FILE * database);

int printf_file (node_t * node, FILE * database);

int get_character (node_t * parent);

int do_play (node_t * node);

int questions (node_t * node);

int graphviz (node_t * root);

int print_dot(FILE * file, node_t * node);
