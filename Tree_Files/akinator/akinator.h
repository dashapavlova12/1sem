#include "tree.h"

node_t * read_database (FILE * database, node_t * parent);

int fsize(FILE * database);

int printf_file (node_t * node, FILE * database);
