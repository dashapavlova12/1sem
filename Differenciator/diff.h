#ifndef DIFFERENCIATOR_DIFF_H
#define DIFFERENCIATOR_DIFF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <fcntl.h>
#include <assert.h>


#define _DEBUG
#define FASTEST_PROGA

#ifdef _DEBUG
#define ASSERT( x ) assert((x))
#else
#ifdef FASTEST_PROGA
        #define ASSERT( x )
    #else
        #define ASSERT( x ) x
    #endif
#endif

#define sassert( x )                                                                                                    \
{                                                                                                                       \
    if (!(x))                                                                                                           \
    {                                                                                                                   \
        printf("Syntax error in %d line in %s", __LINE__, __PRETTY_FUNCTION__);                                         \
        if (pos != NULL)                                                                                        \
            printf(" symbol is %c", *pos);                                                                         \
        abort();                                                                                                        \
    }                                                                                                                   \
}

#define CHECK_LEN( x ) \
{                                                                                                                       \
    if ((x) == pos)                                                                                                \
    {                                                                                                                   \
        printf("Errorororo I began cleaning your laptop\n");                                                            \
        printf("P.s. Don't panic, it was joke(maybe)))). Length = 0 in %s in %d line\n", __PRETTY_FUNCTION__, __LINE__);\
        if (pos != NULL)                                                                                        \
            printf(" symbol is %c", *pos);                                                                         \
        abort();                                                                                                        \
    }                                                                                                                   \
}

typedef char data_t;

//----------------------------------------------------------------------------------------------------------------------
const int Poison_for_counter = 5051;
const char way_to_in[] = "C:\\Users\\Darya\\Desktop\\diff\\Expression.txt";
const char way_to_out[] = "C:\\Users\\Darya\\Desktop\\diff\\Answer.txt";

enum{
    Memory_error  = -1,
    Link_error    = 24,
    Root_error    = 42,
    Counter_error = 256,
    Delete_error  = -5,
    Syntax_error  = 34
};

enum type_of_data
{
    Operator = 30,
    Variable = 40,
    Number = 50,
    Function = 60,
};

struct mystring
{
    char*  String;
    size_t len;
};

struct data_for_rec_tree
{
    type_of_data type;
    char*        oper_name;
    char*        func_name;
    int          number;
    char*        var_name;
};

struct vertex
{
    data_for_rec_tree* data;
    vertex* parent;
    vertex* left_son;
    vertex* right_daughter;
};

struct Tree
{
    vertex* root;
    size_t  counter;
    int     error;
};

struct counters
{
    int integer;
    size_t size;
};

//----------------------------------------------------------------------------------------------------------------------

long int calcSize(const char* inFile);
char* fillBuff(int inFile);

Tree* Tree_construct();

bool Tree_distruct(Tree** myTree);

vertex* create_left_son(Tree* myTree, vertex* new_parent, data_t* info);

vertex* create_right_daughter(Tree* myTree, vertex* new_parent, data_t* info);

bool delete_branch(Tree* myTree, vertex* Judah);

vertex* root_create(Tree* myTree);

bool Tree_ok(Tree* myTree);

vertex* create_empty_elem(Tree* myTree);

vertex* create_vertex(Tree* myTree, vertex* left_vertex, vertex* right_vertex);

data_t* put_info(char* info);

bool Linkers_ok(vertex* node);

bool check_links(vertex* node);

int delete_data(data_for_rec_tree** old_data);

Tree* GetG(Tree* mytree, char* start);

vertex* GetOp(Tree* mytree);

vertex* GetM(Tree* mytree);

vertex* GetP(Tree* mytree);

vertex* GetN(Tree* mytree);

char* give_name();

bool isfunc(char* string);

int print_node(vertex* node);

int print_expression(Tree* mytree);

Tree* read_expression(int input);

vertex* d(vertex* node, Tree* out_tree);

Tree* differenciation(Tree* in_tree);

int copy(vertex* to, vertex* from, Tree* mytree);

vertex* make_copy(vertex* from, Tree* mytree);

int simple(vertex* node, Tree* mytree);

int to_be_simple(Tree* mytree);

void print_mode(vertex* pos, FILE* dot_out);

void create_tree(vertex* pos, FILE* dot_out);

void tree_dot(Tree* nameTree, char* dot_out);

#endif
