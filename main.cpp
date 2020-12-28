// https://blog.csdn.net/qq_33897261/article/details/102787692
#include <cstdio>

#define MAXSIZE 20

typedef struct{
    char Data[MAXSIZE];
    int topIdx;
}SeqStack;

void Push(SeqStack *L, char c){
    L->topIdx++;
    L->Data[L->topIdx] = c;
}

int Pop(SeqStack *L){
    L->topIdx--;
    return L->Data[L->topIdx];
}

int isEmpty(SeqStack L){
    if (L.topIdx != 0){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    char c;
    SeqStack bracket;
    bracket.topIdx = 0;

    do {
        scanf("%c", &c);
        if (c == '(')
            Push(&bracket, c);
        if (c == ')'){
            if (isEmpty(bracket) == 0){
                printf("NO");
                return 0;
            }
            else
            {
                Pop(&bracket);
            }
        }
    }while(c != '@');

    if (isEmpty(bracket) == 0)
        printf("YES");
    else
        printf("NO");

    return 0;
}
