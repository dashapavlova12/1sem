#include "BDSL.h"
#include "diff.h"

DEF_FUNC(sin,   {
                    vertex* new_node = create_vertex(out_tree, NULL, NULL);
                    vertex* new_func = create_vertex(out_tree, NULL, NULL);
                    vertex* new_argument = make_copy(node->right_daughter, out_tree);
                    assert(new_node != NULL);
                    assert(new_func != NULL);
                    assert(new_argument != NULL);
                    new_node->left_son = new_func;
                    new_func->parent = new_node;
                    new_node->data->type = Operator;
                    new_node->data->oper_name = "*";
                    new_node->right_daughter = d(node->right_daughter, out_tree);
                    assert(new_node->right_daughter != NULL);
                    new_node->right_daughter->parent = new_node;

                    new_func->right_daughter = new_argument;
                    new_argument->parent = new_func;
                    new_func->data->type = Function;
                    new_func->data->func_name = put_info("cos");

                    return new_node;
                });
DEF_FUNC(cos,   {
                    vertex* new_node = create_vertex(out_tree, NULL, NULL);
                    vertex* new_func = create_vertex(out_tree, NULL, NULL);
                    vertex* sub = create_vertex(out_tree, NULL, NULL);
                    vertex* zero = create_vertex(out_tree, NULL, NULL);
                    vertex* new_argument = make_copy(node->right_daughter, out_tree);
                    assert(new_node != NULL);
                    assert(new_func != NULL);
                    assert(sub != NULL);
                    assert(zero != NULL);
                    assert(new_argument != NULL);
                    new_node->left_son = sub;
                    sub->parent = new_node;
                    new_node->data->type = Operator;
                    new_node->data->oper_name = "*";
                    new_node->right_daughter = d(node->right_daughter, out_tree);
                    assert(new_node->right_daughter != NULL);
                    new_node->right_daughter->parent = new_node;

                    sub->left_son = zero;
                    zero->parent = sub;
                    sub->data->type = Operator;
                    sub->data->oper_name = put_info("-");
                    sub->right_daughter = new_func;
                    new_func->parent = sub;

                    zero->data->type = Number;
                    zero->data->number = 0;

                    new_func->right_daughter = new_argument;
                    new_argument->parent = new_func;
                    new_func->data->type = Function;
                    new_func->data->func_name = put_info("sin");

                    return new_node;
                });
DEF_FUNC( ln,   {
                    vertex* new_node = CREATE;
                    vertex* copy_r = make_copy(node->right_daughter, out_tree);
                    vertex* diviation = CREATE;
                    vertex* one = CREATE;
                    assert(new_node != NULL);
                    assert(copy_r != NULL);
                    assert(diviation != NULL);
                    assert(one != NULL);
                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info("*");
                    new_node->left_son = diviation;
                    diviation->parent = new_node;
                    new_node->right_daughter = d(node->right_daughter, out_tree);
                    assert(new_node->right_daughter != NULL);
                    new_node->right_daughter->parent = new_node;

                    diviation->left_son = one;
                    one->parent = diviation;
                    diviation->data->type = Operator;
                    diviation->data->oper_name = put_info("/");
                    diviation->right_daughter = copy_r;
                    copy_r->parent = diviation;

                    one->data->type = Number;
                    one->data->number = 1;

                    return new_node;
                });
