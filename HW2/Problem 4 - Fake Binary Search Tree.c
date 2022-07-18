#include<stdio.h>
#include<stdlib.h>
int data[1000002]={0},left[1000002]={0},right[1000002]={0};
int ans=0;
typedef struct tree{
    int data;
    struct tree *left;
    struct tree *right;
} tree;

tree *build( int data[], int left[], int right[],int now){
    tree *new;
    new = (tree *)malloc(sizeof(tree));
    new->data = data[now];
    if(left[now]!=-1)
        new->left = build(data,left,right,left[now]);
    else new->left = NULL;
    if(right[now]!=-1)
        new->right = build(data,left,right,right[now]);
    else new->right = NULL;
    return new;
}

void triversal(tree *head,int left,int right){
    if(head==NULL) return;
    if(head->data>left && head->data<right)
        ans++;
    if(head->data<right)
        triversal(head->left,left,head->data);
    else
        triversal(head->left,left,right);
    if(head->data>left)
        triversal(head->right,head->data,right);
    else
        triversal(head->right,left,right);
}

int main(){
    int n;
    tree *head=NULL;
    scanf("%d",&n);
    for(int a=0;a<n;a++)
        scanf("%d%d%d",&data[a+1],&left[a+1],&right[a+1]);
    head = build(data, left , right, 1);
    triversal(head,0,1000000005);
    printf("%d",ans);
    return 0;
}