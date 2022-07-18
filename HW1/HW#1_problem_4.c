#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct number{
    double data;
    struct number *operate[4];  
    //0 for add, 1 for minus, 2 for multiple, 3 for division
};
typedef struct number node;

int translate(char target[]){
    int len=strlen(target),a,temp,ret=0;
    for(a=0;a<len;a++){
        if(target[a]=='0') temp=0;
        if(target[a]=='1') temp=1;
        if(target[a]=='2') temp=2;
        if(target[a]=='3') temp=3;
        if(target[a]=='4') temp=4;
        if(target[a]=='5') temp=5;
        if(target[a]=='6') temp=6;
        if(target[a]=='7') temp=7;
        if(target[a]=='8') temp=8;
        if(target[a]=='9') temp=9;
        ret=ret*10+temp;
    }
    return ret;
}

node *deal(char data[],node *head,char operator,node *end){
    int dat;
    node *new=NULL;
    dat = translate(data);
    new = (node *)malloc(sizeof(node));
    new->data = dat;
    for(int a=0;a<4;a++) new->operate[a]=NULL;
    if(head==NULL)
        return new;
    if(operator=='+') end->operate[0] = new;
    if(operator=='-') end->operate[1] = new;
    if(operator=='*') end->operate[2] = new;
    if(operator=='/') end->operate[3] = new;
    
    return new;
}

void mul_and_div(node *current){
    int a;
    node *temp=NULL;
    for(a=0;a<4;a++){
        if((a==0||a==1)&&current->operate[a]!=NULL){
            current=current->operate[a];
            a=-1;
            continue;
        }
        if((a==2||a==3)&&current->operate[a]!=NULL){
            temp=current->operate[a];
            if(a==2)
                current->data = current->data * temp->data;
            if(a==3)
                current->data = current->data / temp->data;
            for(int b=0;b<4;b++)
                current->operate[b]=temp->operate[b];
            a=-1;
            free(temp);
        }
    }
}

void add_and_min(node *current){
    node *temp=NULL;
    for(int a=0;a<4;a++){
        if((a==1||a==0)&&current->operate[a]!=NULL){
            temp=current->operate[a];
            if(a==0)
                current->data = current->data + temp->data;
            if(a==1)
                current->data = current->data - temp->data;
            for(int b=0;b<4;b++)
                current->operate[b]=temp->operate[b];
            a=-1;
            free(temp);
            continue;
        }
    }
}

node *link_two_node(node *end,node *new,char operator){

    if(operator=='+') end->operate[0] = new;
    if(operator=='-') end->operate[1] = new;
    if(operator=='*') end->operate[2] = new;
    if(operator=='/') end->operate[3] = new;

    return new;
}

//translate string into number and save it into a linked list head is the first node
node *make_linked_list(node *head,int len,node *end,char input[]){
    //printf("Level = %d\n",level);
    char operator;
    int index=0;
    int bra_up=0;
    char temp_num[10]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
    for(int a=0;a<len;a++){
        
        if(input[a]=='('){
            node *temp=NULL;
            char bra[100000];
            bra_up++; a++;
            int k=0;
            while(bra!=0){
                if(input[a]=='(') bra_up++;
                if(input[a]==')') bra_up--;
                if(bra_up==0) break;
                bra[k]=input[a];
                a++;
                k++;
            }
            temp= make_linked_list(NULL,k,NULL,bra);
            if(end==NULL){
                head=temp;
                end=temp;
            }
            else end = link_two_node(end,temp,operator);

            a++;
            operator=input[a];
            continue;
        }

        if(input[a]=='+'||input[a]=='-'||input[a]=='*'||input[a]=='/'||a==len-1){
            if(a==len-1) temp_num[index]=input[a];
            index=0;
            end = deal(temp_num,head,operator,end);
            if(head==NULL) head=end;
            operator=input[a];
            for(int b=0;b<10;b++) temp_num[b]='\0';
            continue;
        }
        temp_num[index]=input[a];
        index++;
    }

    mul_and_div(head);
    add_and_min(head);
    return head;
}


int main(){
    char input[1000000];
    while(scanf("%s",input)!=EOF){
        int len=strlen(input),index=0;
        char temp_num[10],operator;
        node *head=NULL,*end=NULL;
        head = make_linked_list(head,len,end,input);
        printf("%.15lf\n",head->data);
    }
    return 0;
}