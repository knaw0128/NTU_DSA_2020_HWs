#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct productline{
    int cago;
    struct productline *pre;
    struct productline *next;
} proline;

char push[]="push",merge[]="merge"; 
char order[200002][8]={'\0'};
int order_num[200002][2]={0},pack[100002]={0};
int all_lines[100002]={0};
int used[100002]={0};
int *heaps[100002]={0};
int heap_len[100002] = {0};
int heap_max[100002];
int set[100002];
int where[100002]={0};
proline *lines[100002][2] = {NULL};


int find(int x){
    if(set[x]==x)return x;
    return set[x]=find(set[x]);
}

void U(int x,int y){
    x=find(x);
    y=find(y);
    set[x]=y;
}

void sort_heap(int line){
    int len = heap_len[line], temp;
    while(len!=0){
        temp = len/2;
        if(temp==0) break;
        if(heaps[line][len-1]>heaps[line][temp-1]){     //available to change to min heap
            int buf = heaps[line][len-1];
            heaps[line][len-1] = heaps[line][temp-1];
            heaps[line][temp-1] = buf;
        }
        len = temp;
    }
}

void sort_heap_bottom(int line){
    int now = 1, left=2, right=3;
    while(now<heap_len[line]){
        left = now*2;
        right = now*2+1;
        if(left>heap_len[line]) left = now;
        if(right>heap_len[line]) right=now;
        if(heaps[line][now-1]<heaps[line][left-1] || heaps[line][now-1]<heaps[line][right-1]){
            if(heaps[line][left-1] > heaps[line][right-1]){
                int temp = heaps[line][left-1];
                heaps[line][left-1] = heaps[line][now-1];
                heaps[line][now-1] = temp;
                now = left;
            }
            else{
                int temp = heaps[line][right-1];
                heaps[line][right-1] = heaps[line][now-1];
                heaps[line][now-1] = temp;
                now = right;
            }
        }
        else break;
    }
}

void heap_append(int target,int line){
    heap_len[line]++;
    heaps[line][heap_len[line]-1] = target;
    sort_heap(line);
}

void heap_pop(int line){
    int last = heap_len[line]-1;
    heaps[line][0] = heaps[line][last];
    heap_len[line]--;
    sort_heap_bottom(line);
}

void append(proline *lines[100002][2],char order[],int order_num[2],int n){
    if(!strcmp(order,push)){
        if(lines[order_num[1]][0]!=NULL){
            int final = find(lines[order_num[1]][0]->cago);
            U(order_num[0], final);
            set[lines[order_num[1]][0]->cago] = final;
        }
        else where[order_num[0]] = order_num[1];
    
        all_lines[order_num[1]]++;
        //update queue
        proline *new = (proline *)malloc(sizeof(proline));
        new->cago = order_num[0];
        new->pre = lines[order_num[1]][1];
        new->next = NULL;
        if(new->pre!=NULL)
            lines[order_num[1]][1]->next = new;
        lines[order_num[1]][1] = new;
        if(lines[order_num[1]][0] == NULL)
            lines[order_num[1]][0] = new;
        //update heaps
        while(heap_len[order_num[1]]>=heap_max[order_num[1]]){
            heaps[order_num[1]] = realloc(heaps[order_num[1]], heap_max[order_num[1]]*2*sizeof(int));
            heap_max[order_num[1]]*=2;
        }
        heap_append(order_num[0],order_num[1]);
    }

    if(!strcmp(order,merge)){
        if(lines[order_num[0]][0]==NULL)
            return;
        int sub = find(lines[order_num[0]][0]->cago);
        set[lines[order_num[0]][0]->cago] = sub;
        if(lines[order_num[1]][0]!=NULL){
            int nas = find(lines[order_num[1]][0]->cago);
            set[lines[order_num[1]][0]->cago] = nas;
            U(sub, nas);
        }
        where[sub] = order_num[1];
        //update queue
        proline *end_1 = lines[order_num[1]][1];
        proline *start_2 = lines[order_num[0]][0];
        proline *new_end = lines[order_num[0]][1];

        if(start_2 == NULL){
            free(heaps[order_num[0]]);
            heap_len[order_num[0]] = 0;
            heap_max[order_num[0]] = 0;
            return;
        }
        if(end_1==NULL){
            lines[order_num[1]][0] = start_2;
            lines[order_num[1]][1] = new_end;
        }
        else{
            end_1->next = start_2;
            if(start_2!=NULL)
                start_2->pre = end_1;
            if(new_end!=NULL)
                lines[order_num[1]][1] = new_end;
        }
        lines[order_num[0]][1] = NULL;
        lines[order_num[0]][0] = NULL;
        //update heaps
        int heap0_len = heap_len[order_num[0]];
        int heap1_len = heap_len[order_num[1]];
        if(heap0_len <= heap1_len){
            while((heap_len[order_num[1]]+heap_len[order_num[0]])>=heap_max[order_num[1]]){
                heaps[order_num[1]] = realloc(heaps[order_num[1]], (heap_max[order_num[1]]+heap_max[order_num[0]])*2*sizeof(int));
                heap_max[order_num[1]]*=2;
                heap_max[order_num[0]]*=2;
            }
            for(int a=0;a<heap0_len;a++){
                heap_append(heaps[order_num[0]][a],order_num[1]);
                heaps[order_num[0]][a] = 0;
            }
            free(heaps[order_num[0]]);
            heap_len[order_num[0]] = 0;
            heap_max[order_num[0]] = 0;
            heap_len[order_num[1]] = heap_len[order_num[1]]+heap_len[order_num[0]];
            return;
        }
        else{
            while((heap_len[order_num[1]]+heap_len[order_num[0]])>=heap_max[order_num[0]]){
                heaps[order_num[0]] = realloc(heaps[order_num[0]], (heap_max[order_num[1]]+heap_max[order_num[0]])*2*sizeof(int));
                heap_max[order_num[0]]*=2;
                heap_max[order_num[1]]*=2;
            }
            for(int a=0;a<heap1_len;a++){
                heap_append(heaps[order_num[1]][a],order_num[0]);
                heaps[order_num[1]][a] = 0;
            }
            int *temp;
            temp = heaps[order_num[1]];
            heaps[order_num[1]] = &heaps[order_num[0]][0];
            heaps[order_num[0]] = temp;
            int haha;
            haha = heap_len[order_num[0]];
            heap_len[order_num[0]] = heap_len[order_num[1]];
            heap_len[order_num[1]] = haha;
            haha = heap_max[order_num[0]];
            heap_max[order_num[0]] = heap_max[order_num[1]];
            heap_max[order_num[1]] = haha;
            free(heaps[order_num[0]]);
            heap_len[order_num[0]] = 0;
            heap_max[order_num[0]] = 0;
            heap_len[order_num[1]] = heap_len[order_num[1]]+heap_len[order_num[0]];
            return;
        }
    }
}

int check(proline *lines[100002][2], int l, int target, int all_lines[]){
    proline *temp=NULL;
    int b = find(target);
    set[target] = b;
    if(where[b] == -1) return 0;
    int a = where[b];
    int is_used=0;

    if(used[heaps[a][0]]!=0){
        heap_pop(a);
        is_used++;
    }

    if(used[lines[a][0]->cago]!=0){
        temp = lines[a][0];
        if(lines[a][0] != lines[a][1])
            lines[a][0] = lines[a][0]->next;
        else{
            lines[a][0] = NULL;
            lines[a][1] = NULL;
        }
        free(temp);
        all_lines[a]--;
        is_used++;
    }

    if(used[lines[a][1]->cago]!=0){
        temp = lines[a][1];
        if(lines[a][0] != lines[a][1])
            lines[a][1] = lines[a][1]->pre;
        else{
            lines[a][0] = NULL;
            lines[a][1] = NULL;
        }
        free(temp);
        all_lines[a]--;
        is_used++;
    }

    if(is_used!=0) 
        return check(lines,l,target,all_lines);

    if(lines[a][0]->cago == target){
        temp = lines[a][0];
        if(lines[a][0] != lines[a][1])
            lines[a][0] = lines[a][0]->next;
        else{
            lines[a][0] = NULL;
            lines[a][1] = NULL;
        }
        free(temp);
        all_lines[a]--;
        used[target]++;
        return 1;
    }

    if(lines[a][1]->cago == target){
        temp = lines[a][1];
        if(lines[a][0] != lines[a][1]){
            lines[a][1] = lines[a][1]->pre;
            lines[a][1]->next = NULL;
        }
        else{
            lines[a][0] = NULL;
            lines[a][1] = NULL;
        }
        free(temp);
        all_lines[a]--;
        used[target]++;
        return 1;
    }
        
    if(heaps[a][0] == target){
        heap_pop(a);
        used[target]++;
        return 1;
    }

    return 0;
}

int main(){
    int t;
    int n,o,l;
    int size = 10;

    scanf("%d",&t);
    while(t--){
        for(int a=0;a<100002;a++){
            heaps[a] = calloc(size, sizeof(int));
            used[a] = 0;
            all_lines[a] = 0;
            lines[a][0] = NULL;
            lines[a][1] = NULL;
            heap_len[a] = 0;
            heap_max[a] = size;
            set[a] = a;
            order[a][0] ='\0';
            where[a] = -1;
            order[a+100000][0] ='\0';
        }
        scanf("%d%d%d",&n,&o,&l);
        for(int a=0;a<o;a++){
            scanf("%s",order[a]);
            scanf("%d%d",&order_num[a][0],&order_num[a][1]);
        }

        for(int a=0;a<n;a++){
            scanf("%d",&pack[a]);
        }
        int step=0;

        for(int a=0;a<n;a++){
            while(!check(lines,l,pack[a],all_lines)){
                
                if(step>o) break;
                append(lines,order[step],order_num[step],n);
                step++;
            }
            if(step>o)
                break;
        }

        if(step>o)
            printf("impossible\n");
        else 
            printf("possible\n");
    }
}
