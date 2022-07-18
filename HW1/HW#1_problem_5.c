#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct train{
    int train_id;
    struct train *next[2]; //0 for pre 1 for next 
    int my_status;
};
typedef struct train rail;

int same(char target[],char origin[]){
    int len_1=strlen(target),len_2=strlen(origin);
    if(len_1!=len_2) return 0;
    for(int a=0;a<len_1;a++)
        if(target[a]!=origin[a]) return 0;
    return 1;
}


int main(){
    char enter[]="enter",leave[]="leave",migrate[]="migrate";
    int r,l,n,k;
    scanf("%d%d",&k,&n);

    rail *repo[1005]={NULL};
    rail *end[1005]={NULL};

    for(int i=0;i<n;i++){
        char order[10];
        scanf("%s",&order);
        if(same(order,enter)){
            scanf("%d %d",&r,&l);
            rail *new;
            new = (rail *)malloc(sizeof(rail));
            new->train_id = l;
            new->next[1] = NULL;
            new->my_status = 1;
            new->next[0] = end[r];
            if(end[r]==NULL){
                repo[r]=new;
                end[r]=new;
                continue;
            }

           if(end[r]->next[0]==NULL)
               end[r]->next[0] = new;
            else end[r]->next[1] = new;
            end[r] = new;            
           
        }

        else if(same(order,leave)){
            scanf("%d",&r);
            rail *last;
            if(end[r] == NULL) continue;

            if(end[r]->next[1]==NULL)
                last = end[r]->next[0];
            else last =end[r]->next[1];

            if(last==NULL){
                free(end[r]);
                end[r]=NULL;
                repo[r]=NULL;
                continue;
            }
            
            if(last->next[0] == end[r])
                last->next[0]=NULL;
            else last->next[1]=NULL;

            free(end[r]);
            end[r]=last;
        }

        else if(same(order,migrate)){
            int r_a,r_b;
            rail *temp;
            scanf("%d %d",&r_a,&r_b);
            if(end[r_a]==NULL) continue;

            if(end[r_b]==NULL){ 
                repo[r_b]=end[r_a];
                end[r_b]=repo[r_a];
                repo[r_a] = NULL;
                end[r_a] = NULL;
                continue;
            }

            if(end[r_b]->next[1]==NULL)
                end[r_b]->next[1] = end[r_a];
            else end[r_b]->next[0] = end[r_a];

            if(end[r_a]->next[1]==NULL)
                end[r_a]->next[1] = end[r_b];
            else end[r_a]->next[0] =end[r_b];

            end[r_b] = repo[r_a];
            repo[r_a]=NULL;
            end[r_a]=NULL;
        }
        else continue;
    }
    rail *now,*pre;
   int step;    
    for(int a=0;a<k;a++){
        if(a!=0) printf("\n");
        now=repo[a];pre=NULL;
        while(now!=NULL){
            printf("%d ",now->train_id);
            if(now->next[0]!=NULL&&now->next[0]!=pre){
                pre = now;
                now = now->next[0];
                continue;
            }
            else if(now->next[1]!=NULL&&now->next[1]!=pre){
                pre = now;
                now = now->next[1];
                continue;
            }
            else break;
        }
    }
}
    