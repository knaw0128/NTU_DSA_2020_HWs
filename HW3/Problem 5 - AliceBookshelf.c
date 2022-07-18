#include<stdio.h>
#include<stdlib.h>
typedef struct treap{
    int val;
    int priority;
    int reverse;
    int size;
    int max;
    int increase;
    struct treap *left;
    struct treap *right;
} treap;

treap *root=NULL;

int size(treap *target){
    if(target==NULL)
        return 0;
    return target->size;
}

treap *new_node(int k, int rand){
    treap *new;
    new = (treap *)malloc(sizeof(treap));
    new->val = k;
    new->left = NULL;
    new->right = NULL;
    new->reverse = 0;
    new->priority = rand;
    new->max = k;
    new->size = 1;
    new->increase = 0;
    return new;
}

int max(int a, int b) {
  if (a>b)
    return a;
  else
    return b;
}

void swap(treap *target){
    treap *ll=target->left;
    treap *rr=target->right;
    target->left = rr;
    target->right = ll;
}

void down(treap *target){
    if(target==NULL)
        return;
    if(target->reverse){
        swap(target);
        if(target->left!=NULL)
            target->left->reverse^=1;
        if(target->right!=NULL)
            target->right->reverse^=1;
        target->reverse = 0;
    }
    int plus = target->increase;
    if(plus!=0){
        target->val += plus;
        target->max += plus;
        if(target->left!=NULL)
            target->left->increase += plus;
        if(target->right!=NULL)
            target->right->increase += plus;
        target->increase = 0;
    }
}

void up(treap *target){
    if(target==NULL)
        return;
    target->size = 1;
    target->max = target->val;
    if(target->left!=NULL){
        down(target->left);
        target->size+=target->left->size;
        target->max = max(target->max, target->left->max);
    }
    if(target->right!=NULL){
        down(target->right);
        target->size+=target->right->size;
        target->max = max(target->max, target->right->max);
    }
}

treap *merge(treap *a,treap *b){
    if(a==NULL)
        return b;
    if(b==NULL)
        return a;
    
    if(a->priority < b->priority){
        down(a);
        a->right = merge(a->right,b);
        up(a);
        return a;
    }
    else{
        down(b);
        b->left = merge(a,b->left);
        up(b);
        return b;
    }
}

void split(treap *root, treap **a, treap **b, int pos){
    //呼叫時a,b要取址
    down(root);
    if(root==NULL){
        *a = NULL;
        *b = NULL;
        return;
    }
    else if(size(root->left)+1 <= pos){
        *a = root;
        split(root->right, &((*a)->right), b, pos-size(root->left)-1);
    }
    else{
        *b = root;
        split(root->left, a, &((*b)->left), pos);
    }
    up(root);
}

void insert(int k, int rand, int pos){
    treap *a=NULL,*b=NULL;
    treap *new = new_node(k, rand);
    split(root,&a,&b,pos);
        
    root = merge(a,merge(new,b));
}

void delete(treap **target, int k){
    treap *a=NULL, *b=NULL, *c=NULL;
    split(*target, &a, &b, k-1);
    if(b==NULL)
        return;
    split(b,&b,&c,1);
    free(b);
    *target = merge(a,c);
}

int query(treap *root, int l, int r){
    treap *a=NULL, *b=NULL, *c=NULL;
    split(root,&a,&b,l-1);
    split(b,&b,&c,r-l+1);
    down(b);
    int finded = b->max;
    root = merge(a, merge(b,c));
    up(root);
    return finded;
}

void in_order(treap *start){
    if(start==NULL){
        // printf("NULL\n");
        return;
    }
    // printf("Go left\n");
    in_order(start->left);
    printf("%d ",start->val);

    // printf("Go right\n");
    in_order(start->right);
}

void increase(treap *target, int l, int r, int more){
    treap *a, *b, *c;
    down(target);
    split(target,&a,&b,l-1);
    if(b==NULL)
        return;
    split(b,&b,&c,r-l+1);
    down(b);
    b->increase += more;
    down(b);
    target = merge(a,merge(b,c));
}

void reverse(treap **target, int l, int r){
    treap *a=NULL, *b=NULL, *c=NULL;
    down(*target);
    split(*target,&a,&b,l-1);
    if(b==NULL)
        return;
    down(b);
    split(b,&b,&c,r-l+1);
    down(b);
    b->reverse^=1;
    down(b);
    up(b);
    *target = merge(a,merge(b,c));
}

void kill_largest(treap **target, int largest){
    treap *a=NULL, *b=NULL, *c=NULL;
    if(*target == NULL)
        return;
    down(*target);
    if((*target)->left!=NULL && (*target)->left->max+(*target)->left->increase == largest){
        kill_largest(&((*target)->left), largest);
        up(*target);
        return;
    }

    if((*target)->val+(*target)->increase == largest){
        treap *temp = *target;
        down((*target)->left);
        down((*target)->right);
        *target = merge((*target)->left, (*target)->right);
        free(temp);
        up(*target);
        return;
    }
    if((*target)->right!=NULL && (*target)->right->max+(*target)->right->increase == largest){
        kill_largest(&((*target)->right), largest);
        up(*target);
        return;
    }
}

int main(){
    FILE *ans, *input;
    ans = fopen("P5_ans.txt","w");
    input = fopen("test-P6.txt","r");
    if(input==NULL){
        printf("FAILLLLLLLLLLLLLLLLLLL\n");
        return 0;
    }
    srand(123456789);
    int n,q;
    // scanf("%d %d",&n,&q);
    fscanf(input,"%d %d",&n,&q);
    int value;
    for(int a=0;a<n;a++){
        // scanf("%d",&value);
        fscanf(input,"%d",&value);
        insert(value, rand(), a);
    }
    // in_order(root);
    // printf("\n");
    int order;
    for(int a=0;a<q;a++){
        // scanf("%d",&order);
        fscanf(input,"%d ",&order);
        if(order==1){
            int p, k;
            // scanf("%d%d",&p,&k);
            fscanf(input,"%d %d",&p,&k);
            insert(p, rand(), k);
            // in_order(root);
            // printf("\n");
        }

        if(order==2){
            int k;
            // scanf("%d",&k);
            fscanf(input,"%d",&k);
            delete(&root, k);
            // in_order(root);
            // printf("\n");
        }

        if(order==3){
            int l, r, p;
            // scanf("%d%d%d",&l,&r,&p);
            fscanf(input,"%d %d %d",&l,&r,&p);
            increase(root, l, r, p);
            // in_order(root);
            // printf("\n");
        }

        if(order==4){
            int l, r;
            // scanf("%d%d",&l,&r);
            fscanf(input,"%d %d",&l,&r);
            int out=0;
            out = query(root, l, r);
            // printf("query = %d\n",out);
            fprintf(ans,"%d\n",out);
            // in_order(root);
            // printf("\n");
        }

        if(order==5){
            int l, r;
            // scanf("%d%d",&l,&r);
            fscanf(input,"%d %d",&l,&r);
            reverse(&root, l, r);
            // in_order(root);
            // printf("\n");
        }

        if(order==6){
            // printf("MAX = %d\n",root->max);
            if(root!=NULL){
                down(root);
                up(root);
                kill_largest(&root, root->max);
            }
            // in_order(root);
            // printf("\n");
        }

    }
    // in_order(root);
    // printf("\n");
    return 0;
}