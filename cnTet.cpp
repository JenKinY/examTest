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

// ����====
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



int check(char a,char b) //�������ȼ�
{
    if(a=='('||b=='(' || a=='['||b=='[' || a=='{'||b=='{')return 0;  //����������ţ�ֻ�����������ŵ�ʱ��ż�����������ڵı��ʽ
    if(a=='+'||a=='-')return 1;  //�Ӽ���ͬ������
    if(a=='*'&&(b=='*'||b=='/'))return 1;//�˳���ͬ������
    if(a=='/'&&(b=='*'||b=='/'))return 1;//�˳���ͬ������
    return 0;// ��ͬ���������
}
int work(int x,int y,char a) //����
{
    if(a=='+')return x+y;
    if(a=='-')return x-y;
    if(a=='*')return x*y;
    if(a=='/')return x/y;
}

int calExpression()
{
    memset(s,0,sizeof(s));// s �� val ���飬��¼��ʱ�����ֻ��������
//    scanf("%s",str);
    int l=strlen(str);
    str[l]=')'; // ��ͷ��β ��һ������
    c.push('('); //�Ȱѿ�ͷ����������ջ���������������ȼ�
    cnt=0;  //��һ��cnt�������������ǰ���ϵ���ֿ���
    int i=0;
    while(i<=l)
    {
        if(str[i]>='0'&&str[i]<='9') //�����������
        {
            int x=0;
            while(str[i]>='0'&&str[i]<='9')
            {
                x=x*10+str[i]-'0';
                i++;
            }
            val[cnt++]=x; // �õ��� ���� ����� val��
        }
        else  //����� ����������
        {
            if(str[i]==')') //���������ž�Ҫ�������ţ�������������㼶�ϸ�
            {
                while(!c.empty()&&c.top()!='(') //�ҵ������ţ���ֹͣ
                {
                    s[cnt++]=c.top(); //���������������������м� ��ʱ�洢��˳���ԭʽ�����෴
                    c.pop();     //��Ϊ���õ���ջ
                }
                c.pop();//�������Ÿ�t��ջ
            }else if(str[i]==']') //���������ž�Ҫ�������ţ�������������㼶�ϸ�
            {
                while(!c.empty()&&c.top()!='[') //�ҵ������ţ���ֹͣ
                {
                    s[cnt++]=c.top(); //���������������������м� ��ʱ�洢��˳���ԭʽ�����෴
                    c.pop();     //��Ϊ���õ���ջ
                }
                c.pop();//�������Ÿ�t��ջ
            }
            else if(str[i]=='}') //���������ž�Ҫ�������ţ�������������㼶�ϸ�
            {
                while(!c.empty()&&c.top()!='}') //�ҵ������ţ���ֹͣ
                {
                    s[cnt++]=c.top(); //���������������������м� ��ʱ�洢��˳���ԭʽ�����෴
                    c.pop();     //��Ϊ���õ���ջ
                }
                c.pop();//�������Ÿ�t��ջ
            }
            else //����� �� ������
            {
                while(!c.empty()&&check(str[i],c.top()))//���ʱ���Ҫ�����㼶���ˣ�������㼶����ͬ���򵼳�����ķ���
                {
                    //��ͬ��������������²�����
                    s[cnt++]=c.top();
                    c.pop();
                }
                c.push(str[i]);   //��������ż���ջ��
            }
            i++;
        }
    }

    for(i=0; i<cnt; i++)  //�ܹ��� cnt �� ���� + �����
    {
        if(!s[i])  //��������ֵĻ�����ѹ��ջ
            v.push(val[i]);
        else
        {
            int y=v.top();
            v.pop();
            int x=v.top();  //��ջ��ȡ���������� + - * / ����
            v.pop();
            v.push(work(x,y,s[i]));//�õ��Ľ����ѹ��ջ��
        }
    }
    printf("%d\n",v.top());
}


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

    // �����ǣ��ɹ������ +1
    int flag = 0;


    // ����һ������������ı��ʽ
    SElemType *strArr = {};
    //���б��ʽ��������ж� 
    SElemType *p;
    char n;

    scanf("%c",&n);
    if (n!='@')str[flag] = n;flag++;   // FLAG
    while(n!='(' && n!='[' && n!='{')        // ��һ�����ŵļ�⡣�������ֵ��������ţ�ֱ����������
    {
        if(n==')' || n==']' || n=='}'  || n=='@')    return FALSE;    //��Ϊ')'��']'���������ƥ�䡣'@'���ڽ�������
        scanf("%c",&n);               // ������ȡ
        if (n!='@')str[flag] = n;flag++;   // FLAG
    }
    // ��ȡ���������ջ
    if(n=='(' || n=='['  || n=='{')    Push(S,n);    //��⵽�����ţ���ջ
    scanf("%c",&n);  // ������ȡ
    if (n!='@')str[flag] = n;flag++;   // FLAG
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
        if (n!='@')str[flag] = n;flag++;   // FLAG
    }
    if(S->top==S->base)    return TRUE; //ջ��û��Ԫ��ʱ��˵��ƥ�� 
    else return FALSE;
}

int main()
{
//    ���Ա��ʽ��
//    4+(2+8)*[5/(9-4)]@
    Stack Sta;
    Stack *S=&Sta;

    if(InitStack(S)) printf("�ɹ�����ջ...\n");

    printf("��������ʽ��('@'����):\n");
    if(Judge(S) == 1){
        printf("It's True!\n");
        // ������ʽ�����
        printf("%s=",str);
        calExpression();
    }
    else{
        char e = e=*(--S->top);
        printf("��ƥ��(ջ���������ж��)��%c\n",e);
        printf("It's False\n");
    }


    time_t timep;
    time (&timep);
    printf("����ʱ�䣺%s",ctime(&timep));

    return 0;
}
