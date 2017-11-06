//Name:Apu Kumar chakroborti
//Roll No:50
//20th Batch CSEDU

#include<stdio.h>
#include<string.h>
#include<ctype.h>

char input[100];
int i,error;
int expr();
int  term();
int  expr2();
int  term2();
int  factor();
int len;
char brace[100];
int brace_index=-1;


//stack<string> stk_str;
char *grammer[1000];
int grammer_index=-1;
//
void push_char(char c)
{
    brace_index+=1;
    brace[brace_index]=c;
    //printf("brace index is in the push:%d\n",brace_index);
}
void pop_char()
{
    //char c=brace[brace_index];
    brace[brace_index]='\0';
    brace_index-=1;
    //printf("brace index is in the pop:%d\n",brace_index);
    //return c;
}
char top_char()
{
    return brace[brace_index];
    //grammer_index-=1;
}


//stack implementation
void push(char *str)
{
    grammer_index+=1;
    grammer[grammer_index]=str;
    //printf("grammer index is in the push:%d\n",grammer_index);
}
void pop()
{
    grammer[grammer_index]="";
    grammer_index-=1;

    //printf("grammer index is in the pop:%d\n",grammer_index);

}
char * top()
{
    return grammer[grammer_index];
    //grammer_index-=1;
}
//stack part

void print_stack()
{
    int in;
    for(in=0; in<=grammer_index; in++)
    {
        printf("%d :%s\n",in,grammer[in]);
//pop();
    }


}

int main()
{
    freopen("output_practice2.out","w",stdout);
    FILE *file=fopen("input_practice2.txt","r");
    i=0;
    error=0;
    printf("Enter an arithmetic expression   :  "); // Eg: a+a*a
    //gets(input);
    int loc=0;
    char ch;
    char input1[100];
    while((fscanf(file,"%c",&ch))!=EOF)
    {
        input1[loc]=ch;
        loc+=1;
    }
    input1[loc]='\0';
    //fscanf(file,"%s",input);


    printf("Input String: %s\n",input1);
    push("goal->expr");
    len=strlen(input1);
    printf("string length:%d\n",len-1);
    //removing space from input string

    int ws=0;
    int j=0;
    for(ws=0; ws<len-1; ws++)
    {
        if(input1[ws]!=' ')
        {
            input[j]=input1[ws];
            j+=1;
        }
        //printf("Removed space from input string\n");
    }
    len=j;
    printf("Input String after removing space: %s   and lenght:%d\n",input,len);


    if(expr() && i>=len && error!=1)
    {
        printf("\nAccepted..!!!\n");
        print_stack();
    }
    else
    {
        pop();
        printf("\nRejected..!!!\n");
        print_stack();
    }
    return 0;
}



int  expr()
{
    push("expr->term expr2");
    if(!(term() && expr2()))
    {
        pop();
        //printf("E() returing 0\n");
        return 0;
    }
    else
    {
        //printf("E() returing 1\n");
        return 1;
    }
}
int  expr2()
{
    if(input[i]=='+')
    {
        i++;
        push(" expr2 -> + term expr2 ");
        if(!(term() && expr2()))
        {
            //  printf("Eprime() + !(T()&&Eprime()) returing 0\n");
            pop();
            printf("Syntax error :illegal character\n");
            return 0;
        }
        else
        {
            //printf("Eprime() +!(T()&&Eprime()) returing 1\n");

            return 1;
        }
    }
    else if(input[i]=='-')
    {
        i++;
        push("expr2->-term expr2");
        if(!(term()&&expr2()))
        {
            pop();
            //printf("Eprime() - !(T()&&Eprime()) returing 0\n");
            printf("Syntax error :illegal character\n");
            return 0;
        }
        else
        {
            //printf("Eprime() - !(T()&&Eprime()) returing 1\n");

            return 1;
        }

    }
    else
    {
        push("expr2->e");
        //printf("Eprime() epsilon returing 1\n");

        return 1;

    }
}
int  term()
{
    push("term->factor term2");

    if(!(factor() && term2()))
    {
        //printf("T() !(F()&&Tprime()) returing 0\n");

        pop();
        return 0;
    }
    else
    {
        //printf("T() !(F()&&Tprime()) returing 1\n");
        return 1;
    }

}
int  term2()
{

    if(input[i]=='*')
    {
        i++;


        push("term2->* factor term2");
        if(!(factor() && term2()))
        {
            //printf("Tprime() * !(F() && Tprime()) returing 0\n");
            pop();
            printf("Syntax error :illegal character\n");
            return 0;

        }
        else
        {
            //printf("Tprime() * !(F() && Tprime()) returing 1\n");
            return 1;
        }
    }
    else if(input[i]=='/')
    {
        i++;

        push("term2->/factor term2");
        if(!(factor() && term2()))
        {
            //printf("Tprime() / !(F() && Tprime()) returing 0\n");
            pop();
            printf("Syntax error :illegal character\n");
            return 0;

        }
        else
        {
            // printf("Tprime() / !(F() && Tprime()) returing 1\n");
            return 1;
        }
    }
    else
    {
        push("term2->e");
        //printf("Tprime() epsilon returing 1\n");
        return 1;
    }
}
int  factor()
{
    //pop_char();
    char ch;

    if(input[i]=='(')
    {
        push("factor->( expr )");
        push_char('(');
        i++;

        if(!expr())
        {
            pop();
            error=1;
            //printf("F() !E() returing 0\n");
            printf("Syntax error :Unexpected ( \n");
            return 0;
        }
        if(input[i]==')')
        {
            pop_char();
            //printf("brace batch matched \n");
            i++;
            //printf("F() ) returing 1\n");
            return 1;
        }
        else
        {
            pop();
            error=1;
            printf("Syntax error : Unexpected ( \n");
            //printf("F() ) else  returing 0\n");
            return 0;
        }
    }
    else if (top_char()!='(' && input[i]==')')
    {
        error=1;
        i++;
        printf("Syntax error : Unexpected ) \n");
        //printf("topchar ( error \n");
        return 0;

    }
    else if(isalnum(input[i]))
    {

        i++;
        push("factor->number | indentifier");
        //printf("F() isalnum() returing 1 %c\n",input[i-1]);
        return 1;
    }
    else
    {

        pop();
        error=1;
        printf("Syntax error : : illegal character\n");
        //printf("F() else $ returing 0\n");
        return 0;
    }
}




