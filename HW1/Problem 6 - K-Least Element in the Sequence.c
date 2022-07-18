#include<stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct seq{
    int data;
    struct seq *next;
    struct seq *pre;
} seq;

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}

seq *Insert(seq *head,seq *end,int i,int x){
    seq *new,*temp1=head,*temp2=NULL;
    new = (seq *)malloc(sizeof(seq));
        new->data = x;
        new->next = NULL;
        new->pre = NULL;
    if(i==1){
        new->next=head;
        if(head!=NULL)
            head->pre=new;
        return new;
    }
    int now=1;
    while(now!=i-1){
        temp1 = temp1->next;
        now++;
    }
    temp2 = temp1->next;
    temp1->next = new;
    if(temp2!=NULL)
        temp2->pre = new; 
    new->next = temp2;
    new->pre = temp1;
    return new;
}

void Delete(seq *head,int i){
    int now=1;
    seq *temp1=head,*temp2=NULL,*temp3=NULL;
    while(now!=i){
        temp1 = temp1->next;
        now++;
    }
    temp3 = temp1->pre;
    temp2 = temp1->next;
    if(temp3!=NULL)
        temp3->next = temp2;
    if(temp2!=NULL)
        temp2->pre = temp3;
    free(temp1);
    return;
}

void Reverse(seq *head,int l,int r){
    int now=1;
    seq *temp1=head,*temp2=NULL;
    while(now!=l){
        temp1 = temp1->next;
        now++;
    }
    temp2 = temp1;
    now = 1;
     while(now!=r-l+1){
        temp2 = temp2->next;
        now++;
    }
    int temp0;
    while(temp1!=temp2){
        temp0 = temp1->data;
        temp1->data = temp2->data;
        temp2->data = temp0;
        temp1 = temp1->next;
        if(temp1==temp2) break;
        temp2 = temp2->pre;
    }

}

void Query(seq *head,int l,int r,int k){
    int now=1;
    seq *temp1=head,*temp2=NULL;
    while(now!=l){
        temp1 = temp1->next;
        now++;
    }
    temp2 = temp1;
    now = 1;
    int all[r-l+1];
     while(now!=r-l+1){
        all[now-1] = temp2->data;
        temp2 = temp2->next;
        now++;
    }
    all[now-1] = temp2->data;
   if(r!=l)
        qsort((void *)all, r-l+1, sizeof(int), cmpfunc);
    printf("%d\n",all[k-1]);

} 


int main(){
    int n,q,an;
    scanf("%d%d",&n,&q);
    seq *head=NULL,*new=NULL,*prev=NULL,*end=NULL;
    for(int a=0;a<n;a++){
        scanf("%d",&an);
        new = (seq *)malloc(sizeof(seq));
        new->data = an;
        new->next = NULL;
        new->pre = NULL;
        if(head==NULL){
            head = new;
            prev = head;
            end = head;
        }
        else{
            prev->next = new;
            new->pre = prev;
            prev=new;
            end=new;
        }
    }

    for(int a=0;a<q;a++){
        char order[8]={'\0','\0','\0','\0','\0','\0','\0','\0'};
        scanf("%s",&order);
        if(!strcmp(order,"Insert")){
            int i,x;
            seq *new;
            n++;
            scanf("%d%d",&i,&x);
            new = Insert(head,end,i,x);
            if(i==1)
                head = new;
        }
        if(!strcmp(order,"Delete")){
            int i;
            seq *temp=head->next;
            n--;
            scanf("%d",&i);
            Delete(head,i);
            if(i==1)
                head = temp;
        }
        if(!strcmp(order,"Reverse")){
            int l,r;
            scanf("%d%d",&l,&r);
            Reverse(head,l,r);

        }
        if(!strcmp(order,"Query")){
            int l,r,k;
            scanf("%d%d%d",&l,&r,&k);
            Query(head,l,r,k);
        }
        
        seq *haha=head;    
        while(haha!=NULL){
            printf("%d  ",haha->data);
            haha = haha->next;
        }
        printf("\n");
        
    }

    return 0;
}