#include "diff.h"

int main() 
{
    int input = open(way_to_in, O_RDONLY|O_BINARY);
    assert(input >= 0);
    Tree* in_tree = Tree_construct();
    in_tree = read_expression(input);
    assert(in_tree != NULL);
    print_expression(in_tree);

    Tree* out_tree = Tree_construct();
    out_tree = differenciation(in_tree);

    assert(out_tree != NULL);
    printf("\n");
    print_expression(out_tree);
    printf("\n");
    to_be_simple(out_tree);
    print_expression(out_tree);
    Tree_distruct(&in_tree);
    return 0;
}
