//
// Created by skyzc on 2020/12/28.
// https://blog.csdn.net/qq_41890797/article/details/88061182
//
#include<bits/stdc++.h>
using namespace std;
char str[1010];
char s[1010];
int cnt,val[1010];
stack<char>c;
stack<int>v;
int check(char a,char b) //计算优先级
{
    if(a=='('||b=='(')return 0;  //如皋是左括号，只有遇到右括号的时候才计算这对括号内的表达式
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
int main()
{
    memset(s,0,sizeof(s));// s 和 val 数组，记录此时是数字还是运算符
    scanf("%s",str);
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

