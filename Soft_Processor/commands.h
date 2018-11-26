#define CMD_PUSH                1
#define CMD_PUSHax              11
#define CMD_PUSHbx              12
#define CMD_PUSHcx              13
#define CMD_PUSHdx              14
#define CMD_PUSHsq              15
#define CMD_ADD                 3
#define CMD_MUL                 4
#define CMD_DIV                 5
#define CMD_SUB                 6
#define CMD_POP                 20
#define CMD_POPsq               21
#define CMD_POPax               22
#define CMD_POPbx               23
#define CMD_POPcx               24
#define CMD_POPdx               25
#define CMD_JMP                 100
#define CMD_JE                  101
#define CMD_JNE                 102
#define CMD_JA                  103
#define CMD_JAE                 104
#define CMD_JB                  105
#define CMD_JBE                 106
#define CMD_OUT                 7
#define CMD_SQRT                8
#define CMD_IN                  9
#define CMD_END                 100500

 
DEF_CMD("add", CMD_ADD, {
    fprintf (bytecod, "%d ", CMD_ADD);
    return 0;
}, {
    double arg1 = 0;
	double arg2 = 0;
    int res1 = StackPop(MY_CPU -> CPU_STACK, &arg1);
    int res2 = StackPop(MY_CPU -> CPU_STACK, &arg2);
    double sum = arg1 + arg2;
    StackPush(MY_CPU -> CPU_STACK, sum);
    * curpos += 1;
    if(res1 == -1 || res2 == -1) return -1;
    else return 0;
})
 
DEF_CMD ("pop", CMD_POP, {
    fprintf (bytecod, "%d ", CMD_POP);
    return 0;
},{
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("pop_sq", CMD_POPsq, {
	
    char com_arg[100];
    fscanf (commands, "%[ []", com_arg);
    fscanf (commands, "%d", &arg);
    fscanf (commands, "%[]]", com_arg);
    fprintf (bytecod, "%d %d ", CMD_POPsq , arg);
    return 0;
},{
    int arg = commands[*curpos + 1];
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    MY_CPU -> memory[arg] = value;
    * curpos += 2;
    return res;
})
 
DEF_CMD ("pop[ax]", CMD_POPax, {
    fprintf (bytecod, "%d ",CMD_POPax);
    return 0;
},{
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    MY_CPU -> ax = value;
    * curpos += 1;
    return res;
})
 
DEF_CMD ("pop[bx]", CMD_POPbx, {
    fprintf (bytecod, "%d ",CMD_POPbx);
    return 0;
},{
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    MY_CPU -> bx = value;
    * curpos += 1;
    return res;
})
 
DEF_CMD ("pop[cx]", CMD_POPcx, {
    fprintf (bytecod, "%d ",CMD_POPcx);
    return 0;
},{
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    MY_CPU -> cx = value;
    * curpos += 1;
    return res;
})
 
DEF_CMD ("pop[dx]", CMD_POPdx, {
    fprintf (bytecod, "%d ",CMD_POPdx);
    return 0;
},{
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    MY_CPU -> dx = value;
    * curpos += 1;
    return res;
})
 
DEF_CMD ("push", CMD_PUSH, {
    double number = 0;
    fscanf (commands, "%lf", &number);
    fprintf (bytecod, "%d %lf ", CMD_PUSH, number);
    return 0;
}, {
    double arg = commands[*curpos + 1];
    int res = StackPush(MY_CPU -> CPU_STACK, arg);
    * curpos += 2;
    return res;
})
 
DEF_CMD ("push_sq", CMD_PUSHsq, {
    char com_arg[100];
    fscanf (commands, "%[ []", com_arg);
    fscanf (commands, "%d", &arg);
    fscanf (commands, "%[]]", com_arg);
    fprintf (bytecod, "%d %d ", CMD_PUSHsq , arg);
    return 0;
}, {
    int arg = commands[*curpos + 1];
    double value = MY_CPU -> memory[arg];
    int res = StackPush (MY_CPU -> CPU_STACK, value);
    * curpos += 2;
    return res;
})
 
DEF_CMD ("push[ax]", CMD_PUSHax, {
    fprintf (bytecod, "%d ",CMD_PUSHax);
    return 0;
},{
    double value = MY_CPU -> ax;
    int res = StackPush (MY_CPU -> CPU_STACK, value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("push[bx]", CMD_PUSHbx, {
    fprintf (bytecod, "%d ",CMD_PUSHbx);
    return 0;
},{
    double value = MY_CPU -> bx;
    int res = StackPush (MY_CPU -> CPU_STACK, value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("push[cx]", CMD_PUSHcx, {
    fprintf (bytecod, "%d ",CMD_PUSHcx);
    return 0;
},{
    double value = MY_CPU -> cx;
    int res = StackPush (MY_CPU -> CPU_STACK, value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("push[dx]", CMD_PUSHdx, {
    fprintf (bytecod, "%d ",CMD_PUSHdx);
    return 0;
},{
    double value = MY_CPU -> dx;
    int res = StackPush (MY_CPU -> CPU_STACK, value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("mul", CMD_MUL, {
    fprintf (bytecod, "%d ", CMD_MUL);
    return 0;
}, {
    double arg1 = 0;
	double arg2 = 0;
    int res1 = StackPop(MY_CPU -> CPU_STACK, &arg1);
    int res2 = StackPop(MY_CPU -> CPU_STACK, &arg2);
    double mul = arg1 * arg2;
    StackPush(MY_CPU -> CPU_STACK, mul);
    * curpos += 1;
    if(res1 == -1 || res2 == -1) return -1;
    else return 0;
})
 
DEF_CMD ("div", CMD_DIV, {
    fprintf (bytecod, "%d ", CMD_DIV);
    return 0;
}, {
    double arg1 = 0;
	double arg2 = 0;
    int res1 = StackPop(MY_CPU -> CPU_STACK, &arg1);
    int res2 = StackPop(MY_CPU -> CPU_STACK, &arg2);
    double div = arg2 / arg1;
    StackPush(MY_CPU -> CPU_STACK, div);
    * curpos += 1;
    if(res1 == -1 || res2 == -1) return -1;
    else return 0;
})
 
DEF_CMD ("sub", CMD_SUB, {
    fprintf (bytecod, "%d ", CMD_SUB);
    return 0;
 }, {
 	double arg1 = 0;
	double arg2 = 0;
    int res1 = StackPop(MY_CPU -> CPU_STACK, &arg1);
    int res2 = StackPop(MY_CPU -> CPU_STACK, &arg2);
    double sub = arg2 - arg1;
    int res = StackPush(MY_CPU -> CPU_STACK, sub);
    * curpos += 1;
    if(res1 == -1 || res2 == -1 || res == -1) return -1;
    else return 0;
})
 
DEF_CMD ("jmp", CMD_JMP, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JMP, labels[arg]);
    return 0;
}, {
    int index = (int) commands[*curpos + 1];
    *curpos = index;
    return 0;
})
 
DEF_CMD ("je", CMD_JE, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JE, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax == MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("jne", CMD_JNE, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JNE, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax != MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("ja", CMD_JA, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JA, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax > MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("jae", CMD_JAE, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JAE, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax >= MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("jb", CMD_JB, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JB, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax < MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("jbe", CMD_JBE, {
    fscanf(commands, "%d", &arg);
    fprintf (bytecod, "%d %d ", CMD_JBE, labels[arg]);
    return 0;
}, {
    if (MY_CPU -> ax <= MY_CPU -> bx)
    {
        int index = (int) commands[*curpos + 1];
        *curpos = index;
    }
    else
        *curpos += 2;
    return 0;
})
 
DEF_CMD ("out", CMD_OUT, {
    fprintf (bytecod, "%d ", CMD_OUT);
    return 0;
}, {
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    printf ("Result = %.3lf\n", value);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("sqrt", CMD_SQRT, {
    fprintf (bytecod, "%d ", CMD_SQRT);
    return 0;
}, {
    double value = 0;
    int res = StackPop(MY_CPU -> CPU_STACK, &value);
    double arg = sqrt( value );
    StackPush (MY_CPU -> CPU_STACK, arg);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("in", CMD_IN, {
    fprintf (bytecod, "%d ", CMD_IN);
    return 0;
}, {
    double coef = 0;
    scanf ("%lf", &coef);
    int res = StackPush (MY_CPU -> CPU_STACK, coef);
    * curpos += 1;
    return res;
})
 
DEF_CMD ("end", CMD_END, {
    fprintf (bytecod, "%d ", CMD_END);
    return 0;
}, {
    return CMD_END;
})
