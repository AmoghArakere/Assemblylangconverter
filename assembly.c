
/* Program to convert given expression into assembly instructions
   Data Structure used: queue */



#include <stdio.h>
#include<string.h>
typedef enum
{
    lparen,
    rparen,
    plus,
    minus,
    times,
    divide,
    mod,
    eos,
    operand
} precedence;
//initializing queue front and rear values
int front = 0, rear = 0;
int front1 = 1, rear1 = 1;

int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};

precedence q[100];
precedence q1[100];
char expr[100];

//function to get each character from the input expression  
precedence getToken(char *symbol, int *n)
{
    *symbol = expr[(*n)++];
    switch (*symbol)
    {
    case '(':
        return lparen;
    case ')':
        return rparen;
    case '+':
        return plus;
    case '-':
        return minus;
    case '/':
        return divide;
    case '*':
        return times;
    case '%':
        return mod;
    case '\0':
        return eos;
    default:
        return operand;
    }
}
void addq(precedence item)
{
    q[rear++] = item;
}
precedence deleteq()
{
     return q[front++];
}
void addq1(precedence item)
{
    q1[rear1++] = item;
}
precedence deleteq1()
{
     return q1[front1++];
}
void printToken(precedence a)
{
    switch (a)
    {
    case plus:
        printf("add \n");
        break;
    case minus:
        printf("sub \n");
        break;
    case divide:
        printf("div \n");
        break;
    case times:
        printf("mul \n");
        break;
    case mod:
        printf("mod \n");
        break;
    }
}

void assembly(void)
{
    char symbol;
    precedence token;
    int n = 0;
   q1[0]=times;
    // q[0] = eos;
    for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
    {
        if (token == operand)
        {
            printf("load %c\n", symbol);
        }
        else if (token == lparen)
        {
            continue;
        }
        
        else if (token == rparen)
        {
            addq(token);
            while(front1<rear1)
            {
                printToken(deleteq1());
            }
            while (q[front] != rparen)
            {
                printToken(deleteq());
            }
            deleteq();
     
        }
        else
        {
            if (isp[token] >= icp[q1[0]])
            {
                addq1(token);
            }
            else
            {
                addq(token);
            }
        }
    }
    addq(eos);
    addq1(eos);
     while ((token = deleteq1()) != eos)
    {
          printToken(token);
    }
    while ((token = deleteq()) != eos)
    {
          printToken(token);
    }
    
    
    printf("store x\n");
}
void main()
{
    printf("Enter the expression:\n");
    gets(expr);
    printf("The assembly language equivalent is:\n");
    assembly();
   
}