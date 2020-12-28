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


//初始化栈
Status InitStack(Stack *S)
{
    S->base=(SElemType *)malloc(INIT_SIZE*sizeof(SElemType));
    if(!S->base) exit(OVERFLOW);
    S->top=S->base;
    S->stackSize=INIT_SIZE;
    return OK;
}
//入栈
Status Push(Stack *S,char e)
{
    //栈满，重新分配内存
    if(S->top-S->base>=S->stackSize){
        S->base=(SElemType *)realloc(S->base,(INIT_SIZE+INCREMENT)*sizeof(SElemType));
        if(!S->base) exit(OVERFLOW);
        S->top=S->base+S->stackSize;
        S->stackSize+=INCREMENT;
    }
    *S->top++=e;
    return OK;
}
//出栈
char Pop(Stack *S){
    char e;

    if(S->top==S->base)    return ERROR;    //如果栈空，则报错
    e=*(--S->top);
    return e;
}
// 判定括号匹配
Status Judge(Stack *S)
{
    // 声明一个数组存放输入的表达式
    SElemType *strArr = {};
    //进行表达式的输入和判断 
    SElemType *p;
    char n;

    scanf("%c",&n);
    while(n!='(' && n!='[' && n!='{')        // 第一个括号的检测。忽略数字等其他符号，直到输入括号
    {
        if(n==')' || n==']' || n=='}'  || n=='@')    return FALSE;    //若为')'或']'，则表明不匹配。'@'用于结束输入
        scanf("%c",&n);               // 继续获取
    }
    // 获取到括号则进栈
    if(n=='(' || n=='['  || n=='{')    Push(S,n);    //检测到左括号，进栈
    scanf("%c",&n);  // 继续获取
    while(n!='@')    //'@'用于结束输入
    {
        // 判断是否是括号
        if(n=='(' || n==')' || n=='[' || n==']' || n=='{' || n=='}')
        {
            // 是括号先入栈
            p=S->top;
            Push(S,n);
            if(*(p-1)=='(')        //与前一个括号比较 如果匹配了 则 出栈
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
        scanf("%c",&n);  // 继续获取
    }
    if(S->top==S->base)    return TRUE; //栈内没有元素时，说明匹配 
    else return FALSE;
}

int main()
{
    Stack Sta;
    Stack *S=&Sta;

    printf("INITIALIZING...\n");
    if(InitStack(S)) printf("Succeed!\n");

    printf("请输入表达式：('@'结束):\n");
    if(Judge(S) == 1){
        printf("It's True!");
    }
    else{
        char e = e=*(--S->top);
        printf("不匹配(栈顶，可能有多个)：%c\n",e);
        printf("It's False\n");
    }
    return 0;
}