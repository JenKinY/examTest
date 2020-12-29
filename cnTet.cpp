//https://www.cnblogs.com/stargazer7/p/9823227.html
#include <cstdio>
#include <cstdlib>
#include <time.h>
#define INIT_SIZE 10
#define INCREMENT 5

#define OVERFLOW -2
#define FALSE 0
#define OK 1
#define TRUE 1
#define ERROR 0

// 计算====
#include<bits/stdc++.h>
using namespace std;
char str[1010];
char s[1010];
int cnt,val[1010];
stack<char>c;
stack<int>v;
// ====


typedef char SElemType;
typedef int Status;
typedef struct stack{
    SElemType *base;
    SElemType *top;
    int stackSize;
}Stack;



int check(char a,char b) //计算优先级
{
    if(a=='('||b=='(' || a=='['||b=='[' || a=='{'||b=='{')return 0;  //如皋是左括号，只有遇到右括号的时候才计算这对括号内的表达式
    if(a=='+'||a=='-')return 1;  //加减是同级运算
    if(a=='*'&&(b=='*'||b=='/'))return 1;//乘除是同级运算
    if(a=='/'&&(b=='*'||b=='/'))return 1;//乘除是同级运算
    return 0;// 不同级别的运算
}
int work(int x,int y,char a) //计算
{
    if(a=='+')return x+y;
    if(a=='-')return x-y;
    if(a=='*')return x*y;
    if(a=='/')return x/y;
}

int calExpression()
{
    memset(s,0,sizeof(s));// s 和 val 数组，记录此时是数字还是运算符
//    scanf("%s",str);
    int l=strlen(str);
    str[l]=')'; // 开头结尾 加一对括号
    c.push('('); //先把开头的左括号入栈，方便后面计算优先级
    cnt=0;  //用一个cnt将数和运算符的前后关系区分开来
    int i=0;
    while(i<=l)
    {
        if(str[i]>='0'&&str[i]<='9') //处理这个数字
        {
            int x=0;
            while(str[i]>='0'&&str[i]<='9')
            {
                x=x*10+str[i]-'0';
                i++;
            }
            val[cnt++]=x; // 得到的 数字 存放在 val中
        }
        else  //运算符 或者是括号
        {
            if(str[i]==')') //遇到右括号就要找左括号，括号里面的运算级较高
            {
                while(!c.empty()&&c.top()!='(') //找到左括号，就停止
                {
                    s[cnt++]=c.top(); //把里面的运算符导出来，切记 此时存储的顺序和原式正好相反
                    c.pop();     //因为运用的是栈
                }
                c.pop();//把左括号给t出栈
            }else if(str[i]==']') //遇到右括号就要找左括号，括号里面的运算级较高
            {
                while(!c.empty()&&c.top()!='[') //找到左括号，就停止
                {
                    s[cnt++]=c.top(); //把里面的运算符导出来，切记 此时存储的顺序和原式正好相反
                    c.pop();     //因为运用的是栈
                }
                c.pop();//把左括号给t出栈
            }
            else if(str[i]=='}') //遇到右括号就要找左括号，括号里面的运算级较高
            {
                while(!c.empty()&&c.top()!='}') //找到左括号，就停止
                {
                    s[cnt++]=c.top(); //把里面的运算符导出来，切记 此时存储的顺序和原式正好相反
                    c.pop();     //因为运用的是栈
                }
                c.pop();//把左括号给t出栈
            }
            else //运算符 或 左括号
            {
                while(!c.empty()&&check(str[i],c.top()))//这个时候就要看运算级别了，如果运算级别相同，则导出里面的符号
                {
                    //不同级别的运算先留下不处理
                    s[cnt++]=c.top();
                    c.pop();
                }
                c.push(str[i]);   //把这个符号加入栈中
            }
            i++;
        }
    }

    for(i=0; i<cnt; i++)  //总共有 cnt 个 数字 + 运算符
    {
        if(!s[i])  //如果是数字的话，先压入栈
            v.push(val[i]);
        else
        {
            int y=v.top();
            v.pop();
            int x=v.top();  //在栈中取出两个进行 + - * / 操作
            v.pop();
            v.push(work(x,y,s[i]));//得到的结果再压入栈中
        }
    }
    printf("%d\n",v.top());
}


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

    // 数组标记，成功添加则 +1
    int flag = 0;


    // 声明一个数组存放输入的表达式
    SElemType *strArr = {};
    //进行表达式的输入和判断 
    SElemType *p;
    char n;

    scanf("%c",&n);
    if (n!='@')str[flag] = n;flag++;   // FLAG
    while(n!='(' && n!='[' && n!='{')        // 第一个括号的检测。忽略数字等其他符号，直到输入括号
    {
        if(n==')' || n==']' || n=='}'  || n=='@')    return FALSE;    //若为')'或']'，则表明不匹配。'@'用于结束输入
        scanf("%c",&n);               // 继续获取
        if (n!='@')str[flag] = n;flag++;   // FLAG
    }
    // 获取到括号则进栈
    if(n=='(' || n=='['  || n=='{')    Push(S,n);    //检测到左括号，进栈
    scanf("%c",&n);  // 继续获取
    if (n!='@')str[flag] = n;flag++;   // FLAG
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
        if (n!='@')str[flag] = n;flag++;   // FLAG
    }
    if(S->top==S->base)    return TRUE; //栈内没有元素时，说明匹配 
    else return FALSE;
}

int main()
{
//    测试表达式：
//    4+(2+8)*[5/(9-4)]@
    Stack Sta;
    Stack *S=&Sta;

    if(InitStack(S)) printf("成功构建栈...\n");

    printf("请输入表达式：('@'结束):\n");
    if(Judge(S) == 1){
        printf("It's True!\n");
        // 输出表达式及结果
        printf("%s=",str);
        calExpression();
    }
    else{
        char e = e=*(--S->top);
        printf("不匹配(栈顶，可能有多个)：%c\n",e);
        printf("It's False\n");
    }


    time_t timep;
    time (&timep);
    printf("现在时间：%s",ctime(&timep));

    return 0;
}
