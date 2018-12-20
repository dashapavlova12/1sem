#include "diff.h"
#include "BDSL.h"

Tree* read_expression(int input)
{
    char* expression = fillBuff(input);
    assert(expression != NULL);

    Tree* mytree = (Tree*) calloc(1, sizeof(*mytree));
    assert(mytree != NULL);

    root_create(mytree);
    mytree = GetG(mytree, expression);
    if (Tree_ok(mytree) == false)
    {
        printf("Bad tree");
        if (mytree != NULL)
            printf("\n Error = %d", mytree->error);
        return NULL;
    }

    free(expression);
    return mytree;
}

Tree* GetG(Tree* mytree, char* start)
{
    assert(mytree != NULL);
    assert(start != NULL);

    pos = start;
    mytree->root = GetOp(mytree);

    CHECK_LEN(start);
    sassert(*pos == '\0');
    return  mytree;
}

vertex* GetOp(Tree* mytree)
{
    char* start = pos;

    vertex* new_child = GetM(mytree);
    vertex* new_node = NULL;
    assert(new_child != NULL);

    if (start == pos && *pos == '-' && *(pos - 1) == '(')
    {
        new_child = create_vertex(mytree, NULL, NULL);
        new_child->data->type = Number;
        new_child->data->number = 0;
    }
    else
        CHECK_LEN(start);


    if (*pos == '+' || *pos == '-')
    {
        new_node = create_vertex(mytree, NULL, NULL);
        assert(new_node != NULL);
        new_node->left_son = new_child;
        new_child->parent  = new_node;

        new_node->data->type = Operator;
        if (*pos == '+')
            new_node->data->oper_name = put_info("+");
        else
            new_node->data->oper_name = put_info("-");
        pos++;

        start = pos;
        new_node->right_daughter = GetM(mytree);
        assert(new_node->right_daughter != NULL);
        new_node->right_daughter->parent = new_node;

        CHECK_LEN(start);
    }
    if ((*pos == '+' || *pos == '-')) //&& *(pos - 1) != '+' && *(pos - 1) != '-')
    {
        RESTRUCT_OPER

        new_node->data->type = Operator;
        if (*pos == '+')
            new_node->data->oper_name = put_info("+");
        else
            new_node->data->oper_name = put_info("-");
        pos++;

        start = pos;
        new_node->right_daughter = GetOp(mytree);
        assert(new_node->right_daughter != NULL);
        new_node->right_daughter->parent = new_node;

        CHECK_LEN(start);
    }

    if (new_node != NULL)
        return new_node;
    else
        return new_child;
}

vertex* GetM(Tree* mytree)
{
    assert(mytree != NULL);

    char* start = pos;
    vertex* new_child = GetP(mytree);
    vertex* new_node = NULL;
    assert(new_child != NULL);
    if (*pos == '*' || *pos == '/' || *pos == '^')
    {
        new_node = create_vertex(mytree, NULL, NULL);
        assert(new_node != NULL);
        new_node->left_son = new_child;
        new_child->parent  = new_node;

        new_node->data->type = Operator;
        if (*pos == '*')
            new_node->data->oper_name = put_info("*");
        else if (*pos == '/')
            new_node->data->oper_name = put_info("/");
        else
            new_node->data->oper_name = put_info("^");
        pos++;

        start = pos;
        new_node->right_daughter = GetP(mytree);
        assert(new_node->right_daughter != NULL);
        new_node->right_daughter->parent = new_node;

        CHECK_LEN(start);
    }
    if (*pos == '*' || *pos == '/' || *pos == '^')
    {
        RESTRUCT_OPER

        new_node->data->type = Operator;
        if (*pos == '*')
            new_node->data->oper_name = put_info("*");
        else if (*pos == '/')
            new_node->data->oper_name = put_info("/");
        else
            new_node->data->oper_name = put_info("^");
        pos++;

        start = pos;
        new_node->right_daughter = GetM(mytree);
        assert(new_node->right_daughter != NULL);
        new_node->right_daughter->parent = new_node;

        CHECK_LEN(start);
    }

    if (new_node != NULL)
        return new_node;
    else
        return new_child;
}

vertex* GetP(Tree* mytree)
{
    assert(mytree != NULL);

    char* start = pos;
    vertex* new_node = NULL;

    if (*pos == '(')
    {
        pos++;
        start = pos;
        new_node = GetOp(mytree);
        assert(new_node != NULL);

        sassert(*pos == ')');
        pos++;

        return new_node;
    }

    if ( *(pos) <= '9' && *(pos) >= '0')
    {
        new_node = GetN(mytree);
        assert(new_node != NULL);

        return new_node;
    }
    else
    {
        char* name = give_name();
        assert(name != NULL);

        new_node = create_vertex(mytree, NULL, NULL);

        if (*pos != '(')
        {
            new_node->data->type = Variable;
            new_node->data->var_name = name;
            return new_node;
        }

        if (!isfunc(name))
        {
            printf("Syntax error!!! It's not a function: %s", name);
            abort();
        }
        new_node->data->type = Function;
        new_node->data->func_name = name;

        pos++;
        start = pos;

        vertex* new_child = GetOp(mytree);
        assert(new_child != NULL);

        sassert(*pos == ')');
        pos++;

        new_node->right_daughter = new_child;
        new_child->parent = new_node;
    }

    return new_node;
}

vertex* GetN(Tree* mytree)
{
    assert(mytree != NULL);

    vertex* new_node = create_vertex(mytree, NULL, NULL);
    new_node->data->type = Number;

    int ans = 0;

    while ('0' <= *pos && *pos <= '9')
    {
        ans = ans * 10 + (*pos - '0');
        pos++;
    }

    new_node->data->number = ans;
    return new_node;
}

char* give_name()
{
    assert(pos != NULL);

    char buff[101];
    int i = 0;
    while(*pos != '(' && *pos != ' ' && (isalpha(*pos) || isdigit(*pos)) && i < 100)
    {
        buff[i] = *pos;
        pos++;
        i++;
    }
    buff[i] = '\0';
    char* ans = put_info(buff);

    return ans;
}

bool isfunc(char* string)
{
    assert(string != NULL);


    #define DEF_FUNC( name, differenciation) if(!strcmp(#name, string)) return true;

    #include "Functions.h"

    #undef DEF_FUNC

    return false;
}

int print_expression(Tree* mytree)
{
    assert(mytree != NULL);

    print_node(mytree->root);

    return 1;
}

int print_node(vertex* node)
{
    if (node == NULL)
        return 0;
    if (node->left_son != NULL && node->left_son->data->oper_name != NULL)
    {
        assert(node->data->oper_name != NULL);
        if (node->data->oper_name[0] != '+')
            if (node->left_son->data->type == Operator && ((node->left_son->data->oper_name[0] == '+' || node->left_son->data->oper_name[0] == '-') || node->data->oper_name[0] == '^'))
            {
                printf("(");
                print_node(node->left_son);
                printf(")");
            }
            else
                print_node(node->left_son);
        else
            print_node(node->left_son);
    }
    else
        print_node(node->left_son);


    switch(TYPE)
    {
        case Operator:
        {
            if (node->data->oper_name == NULL)
            {
                printf("Bad node, type != type of name\n type = Operator");
                abort();
            }
            printf("%s", DATA->oper_name);
            break;
        }
        case Function:
        {
            if (DATA->func_name == NULL)
            {
                printf("Bad node, type != type of name\n type = Function");
                abort();
            }
            printf("%s(", DATA->func_name);
            print_node(node->right_daughter);
            printf(")");
            return 1;
        }
        case Number:
        {
            printf("%d", DATA->number);
            break;
        }
        case Variable:
        {
            if (DATA->var_name == NULL)
            {
                printf("Bad node, type != type of name\n type = Variable");
                abort();
            }
            printf("%s", DATA->var_name);
            break;
        }
        default:
        {
            printf("Bad node, no type!!!!");
            abort();
        }
    }

    if (node->right_daughter != NULL && node->right_daughter->data->oper_name != NULL)
    {
        if (node->right_daughter->data->type == Operator && (node->right_daughter->data->oper_name[0] == '+' || node->right_daughter->data->oper_name[0] == '-'))
        {
            printf("(");
            print_node(node->right_daughter);
            printf(")");
        }
        else
            print_node(node->right_daughter);
    }
    else
        print_node(node->right_daughter);

    return 0;
}

Tree* Tree_construct()
{
    Tree* myTree = (Tree*) calloc(1, sizeof(*myTree));
    if (myTree == NULL)
        return NULL;

    myTree->root    = NULL;
    myTree->error   = 0;
    myTree->counter = 0;

    return myTree;
}

char* fillBuff(int inFile)
{
    assert(inFile > 0);

    long int numSymbols = calcSize(way_to_in);
    assert(numSymbols != 0);

    char* buff = (char*) calloc(numSymbols + 2, sizeof(*buff));
    assert(buff != NULL);

    long int error = read(inFile, buff, numSymbols);
    assert(error == numSymbols);

    return buff;
}

long int calcSize(const char* inFile)
{
    assert(inFile != NULL);

    struct stat fileInfo;
    stat(inFile, &fileInfo);

    return fileInfo.st_size;
}

vertex* root_create(Tree* myTree)
{
    ASSERT(Tree_ok(myTree));

    if (myTree->root != NULL)
    {
        myTree->error = Root_error;
        return NULL;
    }

    vertex* new_root = create_empty_elem(myTree);
    myTree->root     = new_root;

    ASSERT(Tree_ok(myTree));

    return new_root;
}

bool delete_branch(Tree* myTree, vertex* Judah)
{
    ASSERT(Tree_ok(myTree));

    if (Judah == NULL)
        return true;

    if (Judah->left_son != NULL)
        delete_branch(myTree, Judah->left_son);
    if (Judah->right_daughter != NULL)
        delete_branch(myTree, Judah->right_daughter);

    if (Judah->data != NULL)
        delete_data(&(Judah->data));

    Judah->data = NULL;

    if (Judah->parent != NULL)
    {
        if (Judah->parent->left_son == Judah)
            Judah->parent->left_son = NULL;
        else
            Judah->parent->right_daughter = NULL;

        Judah->parent = NULL;
    }

    free(Judah);
    myTree->counter--;

    return true;
}

bool Tree_ok(Tree* myTree)
{
    if (myTree == NULL)
        return false;

    if (myTree->counter == 0 && myTree->root != NULL)
    {
        myTree->error = Root_error;
        return false;
    }

    if (myTree->counter != 0 && myTree->root == NULL)
    {
        myTree->error = Counter_error;
        return false;
    }

    if (myTree->error != 0)
        return false;

    if (myTree->counter != 0)
    {
        if (!(Linkers_ok(myTree->root)))
            return false;
    }

    return true;
}

vertex* create_vertex(Tree* myTree, vertex* left_vertex, vertex* right_vertex)
{
    vertex* new_vertex = create_empty_elem(myTree);
    if (new_vertex == NULL)
        return NULL;

    new_vertex->right_daughter = right_vertex;
    new_vertex->left_son       = left_vertex;
    new_vertex->data           = (data_for_rec_tree*) calloc(1, sizeof(*(new_vertex->data)));


    if(left_vertex != NULL && right_vertex != NULL)
    {
        left_vertex->parent  = new_vertex;
        right_vertex->parent = new_vertex;
    }


    return new_vertex;
}

bool Tree_distruct(Tree** myTree)
{
    ASSERT(Tree_ok(*myTree));
    if (*myTree == NULL)
        return false;
    if ((*myTree)->error != 0)
        return false;

    if (!delete_branch(*myTree, (*myTree)->root))
        return false;

    (*myTree)->root = NULL;

    free(*myTree);
    *myTree = NULL;

    return  true;
}

data_t* put_info(char* info)
{
    assert(info != NULL);

    size_t size = strlen(info) + 1;

    if (size == 0)
        return NULL;

    data_t* data = (data_t*) calloc(size, sizeof(*data));

    if (data != NULL)
        strcpy(data, info);

    return data;
}

vertex* create_empty_elem(Tree* myTree)
{
    vertex* new_elem = (vertex*) calloc(1, sizeof(*new_elem));
    if (new_elem == NULL)
    {
        myTree->error = Memory_error;
        return NULL;
    }

    new_elem->data           = NULL;
    new_elem->parent         = NULL;
    new_elem->left_son       = NULL;
    new_elem->right_daughter = NULL;
    myTree->counter++;

    return new_elem;
}

bool check_links(vertex* node)
{
    if (node == NULL)
        return false;

    if (node->left_son != NULL)
    {
        if (node->left_son->parent != node)
            return false;
    }
    if (node->right_daughter != NULL)
    {
        if (node->right_daughter->parent != node)
            return false;
    }

    return true;
}

bool Linkers_ok(vertex* node)
{
    if (node == NULL)
        return false;

    if (!(check_links(node)))
        return false;

    if (node->left_son != NULL)
    {
        if (!(Linkers_ok(node->left_son)))
            return false;
    }

    if (node->right_daughter != NULL)
    {
        if (!(Linkers_ok(node->right_daughter)))
            return false;
    }

    if (node->right_daughter == NULL && node->left_son == NULL)
        return true;

    return true;
}

int delete_data(data_for_rec_tree** old_data)
{
    if (old_data == NULL)
        return -1;
    switch ((*old_data)->type) {
        case Operator: {
            if ((*old_data)->oper_name == NULL)
                return -2;
            free((*old_data)->oper_name);
            (*old_data)->oper_name = NULL;
            break;
        }
        case Function: {
            if ((*old_data)->func_name == NULL)
                return -2;
            free((*old_data)->func_name);
            (*old_data)->func_name = NULL;
            break;
        }
        case Variable: {
            if ((*old_data)->var_name == NULL)
                return -2;
            free((*old_data)->var_name);
            (*old_data)->var_name = NULL;
            break;
        }
        case Number: {
            (*old_data)->number = 0;
            break;
        }
        default: {
            printf("Error of deleting data");
            return -42;
        }
    }
    *old_data = NULL;
    return 0;
}

Tree* differenciation(Tree* in_tree)
{
    assert(in_tree != NULL);
    ASSERT(Tree_ok(in_tree));

    Tree* out_tree = (Tree*) calloc(1, sizeof(*out_tree));
    assert(out_tree != NULL);

    out_tree->root = d(in_tree->root, out_tree);

    if (Tree_ok(out_tree) == false)
    {
        printf("Bad tree");
        if (out_tree != NULL)
            printf("\n Error = %d", out_tree->error);
        return NULL;
    }

    return out_tree;
}

vertex* d(vertex* node, Tree* out_tree)
{
    assert(node != NULL);
    assert(out_tree != NULL);

    switch(TYPE)
    {
        case Number:
        {
            vertex* new_node = create_vertex(out_tree, NULL, NULL);
            new_node->data->type = Number;
            new_node->data->number = 0;
            return new_node;
        }
        case Operator:
        {
            switch(DATA->oper_name[0])
            {
                case '+':
                {
                    vertex* new_node = create_vertex(out_tree, NULL, NULL);
                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info("+");
                    new_node->left_son = d(node->left_son, out_tree);
                    assert(new_node->left_son);
                    new_node->left_son->parent =  new_node;
                    new_node->right_daughter = d(node->right_daughter, out_tree);
                    assert(new_node->right_daughter);
                    new_node->right_daughter->parent = new_node;
                    return new_node;
                    break;
                }
                case '-':
                {
                    vertex* new_node = create_vertex(out_tree, NULL, NULL);
                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info("-");
                    new_node->left_son = d(node->left_son, out_tree);
                    assert(new_node->left_son);
                    new_node->left_son->parent = new_node;
                    new_node->right_daughter = d(node->right_daughter, out_tree);
                    assert(new_node->right_daughter);
                    new_node->right_daughter->parent = new_node;
                    return new_node;
                    break;
                }
                case '*':
                {
                    vertex* new_node = create_vertex(out_tree, NULL, NULL);
                    vertex* mul1     = create_vertex(out_tree, NULL, NULL);
                    vertex* mul2     = create_vertex(out_tree, NULL, NULL);
                    vertex* copy_l    = make_copy(node->left_son, out_tree);
                    vertex* copy_r    = make_copy(node->right_daughter, out_tree);

                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info("+");

                    new_node->left_son = mul1;
                    mul1->parent = new_node;
                    mul1->data->type = Operator;
                    mul1->data->oper_name = put_info("*");
                    mul1->left_son = d(node->left_son, out_tree);
                    mul1->left_son->parent = mul1;
                    mul1->right_daughter = copy_r;
                    copy_r->parent = mul1;

                    new_node->right_daughter = mul2;
                    mul2->parent = new_node;
                    mul2->data->type = Operator;
                    mul2->data->oper_name = put_info("*");
                    mul2->right_daughter = d(node->right_daughter, out_tree);
                    mul2->right_daughter->parent = mul2;
                    mul2->left_son = copy_l;
                    copy_l->parent = mul2;

                    return new_node;
                    break;
                }
                case '/':
                {
                    vertex* new_node  = create_vertex(out_tree, NULL, NULL);
                    vertex* sub       = create_vertex(out_tree, NULL, NULL);
                    vertex* degree    = create_vertex(out_tree, NULL, NULL);
                    vertex* indicator = CREATE;
                    vertex* mul1      = create_vertex(out_tree, NULL, NULL);
                    vertex* mul2      = create_vertex(out_tree, NULL, NULL);
                    vertex* copy_l    = make_copy(node->left_son, out_tree);
                    vertex* copy_r    = make_copy(node->right_daughter, out_tree);
                    vertex* copy_r2   = make_copy(node->right_daughter, out_tree);

                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info ("/");
                    new_node->left_son = sub;
                    sub->parent = new_node;
                    new_node->right_daughter = degree;
                    degree->parent = new_node;

                    sub->data->type = Operator;
                    sub->data->oper_name = put_info("-");
                    sub->left_son = mul1;
                    mul1->parent = sub;
                    sub->right_daughter = mul2;
                    mul2->parent = sub;

                    mul1->data->type = Operator;
                    mul1->data->oper_name = put_info("*");
                    mul1->left_son = d(node->left_son, out_tree);
                    mul1->left_son->parent = mul1;
                    mul1->right_daughter = copy_r;
                    copy_r->parent = mul1;

                    mul2->data->type = Operator;
                    mul2->data->oper_name = put_info("*");
                    mul2->left_son = d(node->right_daughter, out_tree);
                    mul2->left_son->parent = mul2;
                    mul2->right_daughter = copy_l;
                    copy_l->parent = mul2;

                    degree->left_son = copy_r2;
                    copy_r2->parent = degree;
                    degree->data->type = Operator;
                    degree->data->oper_name = put_info("^");
                    degree->right_daughter = indicator;
                    indicator->parent = degree;

                    indicator->data->type = Number;
                    indicator->data->number = 2;

                    return new_node;
                    break;
                }
                case '^':
                {
                    vertex* new_node = CREATE;
                    vertex* copy_node = make_copy(node, out_tree);

                    Tree* fake_tree = (Tree*) calloc(1, sizeof(*fake_tree));
                    fake_tree->root = create_vertex(fake_tree, NULL, NULL);
                    vertex* log = create_vertex(fake_tree, NULL, NULL);
                    vertex* f = make_copy(node->left_son, fake_tree);
                    vertex* g = make_copy(node->right_daughter, fake_tree);

                    fake_tree->root->data->type = Operator;
                    fake_tree->root->data->oper_name = put_info("*");
                    fake_tree->root->left_son = log;
                    log->parent = fake_tree->root;
                    fake_tree->root->right_daughter = g;
                    g->parent = fake_tree->root;

                    log->data->type = Function;
                    log->data->func_name = put_info("ln");
                    log->right_daughter = f;
                    f->parent = log;

                    new_node->data->type = Operator;
                    new_node->data->oper_name = put_info("*");
                    new_node->left_son = copy_node;
                    copy_node->parent = new_node;
                    new_node->right_daughter = d(fake_tree->root, out_tree);
                    new_node->right_daughter->parent = new_node;

                    Tree_distruct(&fake_tree);
                     return new_node;
                     break;
                }
                default:
                {
                    printf("Error, I don't know how differenciate this Operator!");
                    abort();
                }
            }
        }
        case Variable:
        {
            vertex* new_node = create_vertex(out_tree, NULL, NULL);
            assert(new_node != NULL);
            assert(node->data->var_name != NULL);

            if (strcmp("exp", node->data->var_name))
            {
                new_node->data->type = Number;
                new_node->data->number = 1;
            }
            else
            {
               new_node->data->type = Variable;
               new_node->data->var_name = put_info("exp");
            }

            return new_node;
        }
        case Function:
        {
            assert(node->data->func_name != NULL);

            #define DEF_FUNC( name, func_for_diff)  if (!strcmp(node->data->func_name, #name)) \
            {\
                func_for_diff;\
            }

            #include "Functions.h"

            #undef DEF_FUNC

            printf("I can't find this function %s", node->data->func_name);
            abort();
        }
        default:
        {
            printf("I don't know this type %d", node->data->type);
            abort();
        }
    }
}

int copy(vertex* to, vertex* from, Tree* mytree)
{
    assert(mytree != NULL);

    to = make_copy(from, mytree);

    return 0;
}

vertex* make_copy(vertex* from, Tree* mytree)
{
    if (from == NULL)
        return NULL;

    vertex* new_node = create_vertex(mytree, NULL, NULL);
    new_node->data->type = from->data->type;
    switch (new_node->data->type)
    {
        case Operator:
        {
            assert(from->data->oper_name);
            new_node->data->oper_name = put_info(from->data->oper_name);
            break;
        }
        case Function:
        {
            assert(from->data->func_name);
            new_node->data->func_name = put_info(from->data->func_name);
            break;
        }
        case Number:
        {
            new_node->data->number = from->data->number;
            break;
        }
        case Variable:
        {
            assert(from->data->var_name);
            new_node->data->var_name = put_info(from->data->var_name);
            break;
        }
        default:
        {
            printf("Something was broken, i can't copy this %d", new_node->data->type);
        }
    }
    new_node->left_son = make_copy(from->left_son, mytree);
    if (new_node->left_son != NULL)
        new_node->left_son->parent = new_node;

    new_node->right_daughter = make_copy(from->right_daughter, mytree);
    if (new_node->right_daughter != NULL)
        new_node->right_daughter->parent = new_node;

    return new_node;
}

int to_be_simple(Tree* mytree)
{
    ASSERT(Tree_ok(mytree));

    int i = 2;
    int safety = 0;
    for(; safety < 200 && i > 0; safety++)
    {
        int current_num_nodes = mytree->counter;
        simple(mytree->root, mytree);
        print_expression(mytree);
        printf("\n");
        if(current_num_nodes == mytree->counter)
            i--;
    }

    if (safety == 200)
        printf("universe_cicle");

    ASSERT(Tree_ok(mytree));
}

int simple(vertex* node, Tree* mytree)
{
    assert(node != NULL);
    assert(mytree != NULL);

    if (node->right_daughter == NULL && node->left_son == NULL)
        return 0;

    if (node->left_son != NULL)
        simple(node->left_son, mytree);
    if (node->right_daughter != NULL)
        simple(node->right_daughter, mytree);

    if (TYPE == Operator)
    {
        if (LS == NULL || RD == NULL)
        {
            printf("Error !!! operator with die branches");
            abort();
        }

        if(ISNUM_L && ISNUM_R)
        {
            TYPE = Number;
            if (DATA->oper_name[0] == '+')
                DATA->number = LS->data->number + RD->data->number;
            else if (DATA->oper_name[0] == '-')
                DATA->number = LS->data->number - RD->data->number;
            else if (DATA->oper_name[0] == '*')
                DATA->number = LS->data->number * RD->data->number;
            else if (DATA->oper_name[0] == '/')
                DATA->number = LS->data->number / RD->data->number;
            else if (DATA->oper_name[0] == '^')
                DATA->number = LS->data->number ^ RD->data->number;
            else
            {
                printf("Bad operator!!!");
                abort();
            }
            free(DATA->oper_name);
            delete_branch(mytree, LS);
            delete_branch(mytree, RD);
            return 1;
        }
        else if(ISNUM_R || ISNUM_L)
        {
            if (ISZERO_L || ISZERO_R)
            {
                if (ISZERO_L)
                {
                    if (DATA->oper_name[0] == '*' || DATA->oper_name[0] == '/' || DATA->oper_name[0] == '^')
                    {
                        delete_branch(mytree, LS);
                        delete_branch(mytree, RD);
                        free(DATA->oper_name);
                        TYPE = Number;
                        DATA->number = 0;

                        return 1;
                    }
                    else if (DATA->oper_name[0] == '+')
                    {
                        delete_branch(mytree, LS);
                        RD->parent = node->parent;
                        if (node->parent->left_son == node)
                            RD->parent->left_son = RD;
                        else
                            RD->parent->right_daughter = RD;
                        node->parent = NULL;
                        node->right_daughter = NULL;
                        delete_data(&(DATA));
                        free(node);
                        (mytree->counter)--;

                        return 1;
                    }
                }
                else
                {
                    if (DATA->oper_name[0] == '*')
                    {
                        delete_branch(mytree, LS);
                        delete_branch(mytree, RD);
                        free(DATA->oper_name);
                        TYPE = Number;
                        DATA->number = 0;

                        return 1;
                    }
                    else if (DATA->oper_name[0] == '+')
                    {
                        delete_branch(mytree, RD);
                        LS->parent = node->parent;
                        if (node->parent->left_son == node)
                            LS->parent->left_son = LS;
                        else
                            LS->parent->right_daughter = LS;
                        node->parent = NULL;
                        node->left_son = NULL;
                        delete_data(&(DATA));
                        free(node);
                        (mytree->counter)--;

                        return 1;
                    }
                    else if (DATA->oper_name[0] == '/')
                    {
                        printf("Syntax error, y can't div to zero");
                        abort();
                    }
                    else if (DATA->oper_name[0] == '^')
                    {
                        delete_branch(mytree, LS);
                        delete_branch(mytree, RD);
                        free(DATA->oper_name);
                        TYPE = Number;
                        DATA->number = 1;

                        return 1;
                    }
                }
            }
            else if (ISNUM_L && LS->data->number == 1)
            {
                if (DATA->oper_name[0] == '^')
                {
                    delete_branch(mytree, LS);
                    delete_branch(mytree, RD);
                    free(DATA->oper_name);
                    TYPE = Number;
                    DATA->number = 1;

                    return 1;
                }
                else if (DATA->oper_name[0] == '*')
                {
                    LS->data->number = 0;
                    free(DATA->oper_name);
                    DATA->oper_name = put_info("+");
                    return 1;
                }
            }
            else if (ISNUM_R && RD->data->number == 1)
            {
                if (DATA->oper_name[0] == '^')
                {
                    free(DATA->oper_name);
                    DATA->oper_name = put_info("+");
                    RD->data->number = 0;

                    return 1;
                }
                else if (DATA->oper_name[0] == '*')
                {
                    RD->data->number = 0;
                    free(DATA->oper_name);
                    DATA->oper_name = put_info("+");
                    return 1;
                }
            }
        }
    }
    if (RD->data->type == Variable)
    {
        if (TYPE == Function && !strcmp("ln", DATA->func_name) && !strcmp(RD->data->var_name, "exp"))
        {
            delete_branch(mytree, RD);
            TYPE = Number;
            DATA->number = 1;

            return 1;
        }
    }
    else if (TYPE == Function && !strcmp(DATA->func_name, "ln"))
    {
        if (ISNUM_R && RD->data->number == 1)
        {
            delete_branch(mytree, RD);
            TYPE = Number;
            DATA->number = 0;

            return 1;
        }
    }

    return 0;
}
