#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"jrb.h"
#include"dllist.h"
#include"jval.h"
typedef struct state
{
    int pos;
    char puzzle[10];
}State;
Dllist open;
Dllist close;
// khai bao nguyen mau 
void di_trai(char p[]);
void di_phai(char p[]);
void di_len(char p[]);
void di_xuong(char p[]);
void save_in_open(char p[]);
void save_in_close(char p[]);
void doi(char *p , int i1 , int i2 )
{
    int *temp;
    *temp = p[i1];
    p[i1] = p[i2];
    p[i2] = *temp;
}
void di_trai(char puzzle[])
{
    save_in_open(puzzle);
    int i , pos;
    char re[10];
    strcpy(re,puzzle);
    for(i=0;i<strlen(puzzle)-1;i++)
    {
        if(puzzle[i] = '0')
        {
            pos = i;
            break;
        }  
    }
    if(pos == 0||pos == 3 || pos == 6)
        return ;
    else
    {
        doi(re,pos,pos-1);
    }
    strcpy(puzzle,re);
    save_in_close(puzzle);
}
void di_phai(char puzzle[])
{
    save_in_open(puzzle);
    int i , pos;
    char re[10];
    strcpy(re,puzzle);
    for(i=0;i<strlen(puzzle)-1;i++)
    {
        if(puzzle[i] = '0')
        {
            pos = i;
            break;
        }  
    }
    if(pos == 2||pos == 5 || pos == 8)
        return ;
    else
    {
        doi(re,pos,pos+1);
    }
    strcpy(puzzle,re);
    save_in_close(puzzle);
}
void di_len(char puzzle[])
{
    save_in_open(puzzle);
    int i , pos;
    char re[10];
    strcpy(re,puzzle);
    for(i=0;i<strlen(puzzle)-1;i++)
    {
        if(puzzle[i] = '0')
        {
            pos = i;
            break;
        }  
    }
    if(pos<=2)
        return ;
    else
    {
        doi(re,pos,pos-3);
    }
    strcpy(puzzle,re);
    save_in_close(puzzle);
}
void di_xuong(char puzzle[])
{
    save_in_open(puzzle);
    int i , pos;
    char re[10];
    strcpy(re,puzzle);
    for(i=0;i<strlen(puzzle)-1;i++)
    {
        if(puzzle[i] = '0')
        {
            pos = i;
            break;
        }  
    }
    if(pos>=6)
        return ;
    else
    {
        doi(re,pos,pos+3);
    }
    strcpy(puzzle,re);
    save_in_close(puzzle);
}
void print_present(char puzzle[])
{
    int i;
    for(i=0;i<strlen(puzzle);i++)
    {
        if((i+1)%3==0)
        {
            printf("%d\n",puzzle[i]);
        }
        else
        {
            printf("%d\t",puzzle[i]);
        }
    }
    printf("\n");
}
void save_in_open(char puzzle[])
{
    Dllist node_o,node_c;

    dll_traverse(node_c,close)
    {
        if(strcmp(puzzle,jval_s(node_c->val))==0)
        {
            return ;
        }
        else
        {
            dll_traverse(node_o,open)
            {
                if (strcmp(puzzle,jval_s(node_o->val))==0)
                {
                    return;
                }
                else
                {
                    dll_append(open,new_jval_s(puzzle));
                }
                
            }
        }
    }
}
void save_in_close(char puzzle[])
{
    Dllist node_o , node_c;
    dll_traverse(node_o,close)
    {
        if(strcmp(puzzle,jval_s(node_o->val))==0)
        {
            return ;
        }
        else
        {
            dll_traverse(node_c,open)
            {
                if (strcmp(puzzle,jval_s(node_c->val))==0)
                {
                    return;
                }
                else
                {
                    dll_append(open,new_jval_s(puzzle));
                }
                
            }
        }
    }
}
int main()
{
    char Puzzle[10]="012345678";
    char Des[10]="123804765";
    int i;
    Dllist node;
    while(strcmp(Puzzle,Des)!=0)
    {
        dll_traverse(node,close)
        {
            printf("%s\n",jval_s(node->val));
        }
    }
    return 0;
}