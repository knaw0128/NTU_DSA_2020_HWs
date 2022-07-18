#include<stdio.h>
#include<stdlib.h>
typedef struct list{
    int edge;
    struct list *next;
    struct list *pre;
} list;
typedef struct ans{
    int head;
    int tail;
    struct ans *next;
} ans;
list *adj_list[100002]={NULL};
ans *right=NULL,*temp=NULL,*start=NULL;
int path[100002]={0};

int find_list(int check,int pre){
    list *kow=NULL, *target=NULL;
    ans *temp=NULL;
    int nieb;
    int change=1;
    kow = adj_list[check];
    if(kow!=NULL)
        nieb = kow->edge;
    else return 1;
    target = adj_list[nieb];

    if(path[check]==1)
        return 0;
    path[check] = 1;

    while(kow!=NULL){
        // printf("check = %d  kow = %d\n",check,nieb);
        if(kow->edge==pre){
            path[check] = 0;
            return 1;
        }
        if(adj_list[nieb]!=NULL&&adj_list[nieb]->edge==check){
            // printf("GET\n");
            temp = (ans *)malloc(sizeof(ans));
            temp->head = check;
            temp->tail = nieb;
            temp->next=NULL;
            if(start!=NULL)
                right->next=temp;
            else
                start=temp;
            right=temp;

            adj_list[nieb] = adj_list[nieb]->next;
            adj_list[check] = adj_list[check]->next;
            kow = kow->next;
            if(kow!=NULL)
                nieb = kow->edge;
        }
        else{
            change = find_list(nieb, check);
            if(!change){
                return 0;
            }
            kow = adj_list[check];
        }
    }
    return 1;
}

int main(){
    int n,l;
    scanf("%d",&n);
    for(int b=0;b<n;b++){
        int input;
        list *now=NULL,*temp=NULL;
        list *r_now=NULL,*r_temp=NULL;
        scanf("%d",&l);
        for(int a=0;a<l;a++){
            scanf("%d",&input);
            now = (list *)malloc(sizeof(list));
            now->edge = input;
            now->pre = temp;
            now->next = NULL;
            if(temp!=NULL)
                temp->next = now;
            else
                adj_list[b+1] = now;
            temp = now;
        }
    }

    list *kow,*trash=NULL;
    int nieb,change;

    for(int a=1;a<=n;a++){
        change = find_list(a, 0);
        if(!change){
            printf("No\n");
            return 0;
        }
    }

    for(int a=1;a<=n;a++){
        if(adj_list[a]!=NULL){
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");
    while(start!=NULL){
        printf("%d %d\n",start->head,start->tail);
        start=start->next;
    }
    return 0;
}