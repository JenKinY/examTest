//https://www.cnblogs.com/stargazer7/p/9823227.html
#include <cstdio>
#include <cstdlib>
#define INIT_SIZE 10
#define INCREMENT 5

#define OVERFLOW -2
#define FALSE 0
#define OK 1
#define TRUE 1
#define ERROR 0

typedef char SElemType;
typedef int Status;
typedef struct stack{
    SElemType *base;
    SElemType *top;
    int stackSize;
}Stack;


//��ʼ��ջ
Status InitStack(Stack *S)
{
    S->base=(SElemType *)malloc(INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stackSize=INIT_SIZE;
    return OK;
}
//��ջ
Status Push(Stack *S,char e)
{
    //ջ�������·����ڴ�
    if(S->top-S->base>=S->stackSize){
        S->base=(SElemType *)realloc(S->base,(INIT_SIZE+INCREMENT)*sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);
        S->top=S->base+S->stackSize;
        S->stackSize+=INCREMENT;
    }
    *S->top++=e;
    return OK;
}
//��ջ
char Pop(Stack *S){
    char e;

    if(S->top==S->base)    return ERROR;    //���ջ�գ��򱨴�
    e=*(--S->top);
    return e;
}
// �ж�����ƥ��
Status Judge(Stack *S)
{
    // ����һ������������ı��ʽ
    SElemType *strArr = {};
    //���б��ʽ��������ж� 
    SElemType *p;
    char n;

    scanf("%c",&n);
    while(n!='(' && n!='[' && n!='{')        // ��һ�����ŵļ�⡣�������ֵ��������ţ�ֱ����������
    {
        if(n==')' || n==']' || n=='}'  || n=='@')    return FALSE;    //��Ϊ')'��']'���������ƥ�䡣'@'���ڽ�������
        scanf("%c",&n);               // ������ȡ
    }
    // ��ȡ���������ջ
    if(n=='(' || n=='['  || n=='{')    Push(S,n);    //��⵽�����ţ���ջ
    scanf("%c",&n);  // ������ȡ
    while(n!='@')    //'@'���ڽ�������
    {
        // �ж��Ƿ�������
        if(n=='(' || n==')' || n=='[' || n==']' || n=='{' || n=='}')
        {
            // ����������ջ
            p=S->top;
            Push(S,n);
            if(*(p-1)=='(')        //��ǰһ�����űȽ� ���ƥ���� �� ��ջ
            {
                if(*p==')')
                {
                    printf("%c\n",Pop(S));
                    printf("%c\n",Pop(S));
                }
                else if(*p==']' || *p == '}')    return FALSE;
            }
            else if(*(p-1)=='[')
            {
                if(*p==']')
                {
                    printf("%c\n",Pop(S));
                    printf("%c\n",Pop(S));
                }
                else if(*p==')' || *p == '}')    return FALSE;
            }
            else if(*(p-1)=='{')
            {
                if(*p=='}')
                {
                    printf("%c\n",Pop(S));
                    printf("%c\n",Pop(S));
                }
                else if(*p==')' || *p == ']')    return FALSE;
            }
        }
        scanf("%c",&n);  // ������ȡ
    }
    if(S->top==S->base)    return TRUE; //ջ��û��Ԫ��ʱ��˵��ƥ�� 
    else return FALSE;
}

int main()
{
    Stack Sta;
    Stack *S=&Sta;

    printf("INITIALIZING...\n");
    if(InitStack(S)) printf("Succeed!\n");

    printf("��������ʽ��('@'����):\n");
    if(Judge(S) == 1){
        printf("It's True!");
    }
    else{
        char e = e=*(--S->top);
        printf("��ƥ��(ջ���������ж��)��%c\n",e);
        printf("It's False\n");
    }
    return 0;
}