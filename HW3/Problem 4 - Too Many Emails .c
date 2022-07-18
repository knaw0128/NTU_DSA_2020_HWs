#include<stdio.h>
#include<string.h>
char D[100002];
char G[100002];

int check(int G[], int D[]){
    for(int a=0;a<52;a++)
        if(G[a]<D[a])
            return 0;
    return 1;
}

void copy(char new[],char old[],int head,int end){
    int skip = end-head;
    int idx=0;
    int old_len = strlen(old);
    for(int a=0;a<old_len;a++){
        if(a==head)
            a+=skip;
        else {
            new[idx] = old[a];
            idx++;
        }
    }
    new[idx] = '\0';
}

int str2int(char s){
    if(s<91)
        s-=65;
    else s-=71;
    int ans = s;
    return ans;
}

int cut(char G[],int place[],int len){
    long long int front=0,rear=0,temp=1,hash1=29476247,hash2 = 24252257;
    int idx=0;
    for(int a=0;a<len/2;a++){
        front = hash2*front+str2int(G[a]);
        rear = temp*str2int(G[len-a-1])+rear;
        temp = (temp*hash2)%hash1;
        if(front >= hash1)
            front = front%hash1;
        if(rear >= hash1)
            rear = rear%hash1;
        if(front==rear){
            front = 0;
            rear = 0;
            temp = 1;
            place[idx] = a;
            place[idx+1] = len-a-2;
            idx+=2;
        }
    }
    return idx-1;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%s",G);
        scanf("%s",D);
        int D_times[52]={0};//先大寫
        int G_times[52]={0};
        int len_D = strlen(D);
        int len_G = strlen(G);
        for(int a=0;a<52;a++){
            D_times[a] = 0;
            G_times[a] = 0;
        }
        
        for(int a=0;a<len_D;a++){
            if(D[a]<91)
                D_times[D[a]-65]++;
            else D_times[D[a]-71]++;
        }
        
        int ans[2]={-100005,-1};
        int now;
        int temp_head,temp_end;
        int word[100005], where[100005];
        int idx=0,idx_head=0,first=-1,prea=-1;

        for(int a=0;a<len_G;a++){
            now = str2int(G[a]);
            if(prea!=a)
                G_times[now]++;
            
            if(D_times[now]!=0&&a!=prea){
                word[idx] = now;
                where[idx] = a;
                // printf("a = %d  now = %c idx = %d\n",a,G[a],idx);
                idx++;
            }

            temp_head = where[idx_head];
            if(idx>0)
                temp_end = where[idx-1];
            else temp_end = 1000000;

            if((first==-1||now==first||prea==a)&&check(G_times,D_times)){
                if(temp_end-temp_head<ans[1]-ans[0]){
                    ans[0] = temp_head;
                    ans[1] = temp_end;
                }
                // printf("prea = %d   a = %d first = %d head = %d rear = %d\n",prea,a,first,ans[0],ans[1]);
                G_times[word[idx_head]]--;                
                first = word[idx_head];
                idx_head++;
                prea=a;
                a--;
            }
        }
        char new_G[100005];
        copy(new_G,G,ans[0],ans[1]);
        // printf("%s\n",new_G);

        int place[100005]={-1,-1};
        int len = strlen(new_G);
        idx=0;
        idx_head = cut(new_G,place,len);
        if(idx_head<0) idx_head=0;
        for(int a=0;a<len;a++){
            printf("%c",new_G[a]);
            if(a==place[idx_head]){
                printf("|");
                idx_head-=2;
            }
            else if(a==place[idx]){
                printf("|");
                idx+=2;
            }
        }
        printf("\n");
        // printf("strlen == %d\n",strlen(new_G));
    }
}