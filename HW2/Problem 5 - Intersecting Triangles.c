#include <stdio.h>
#include "generator.h"
int sum[2100000] = {0},BIT[2100000] = {0};
int left[3000001]={0},right[3000001]={0};
int r_left[3000001]={0},r_right[3000001]={0};
int q_left[3000001]={0},q_right[3000001]={0};
int view[2100000] = {0};

void merge(int p[],int front,int mid,int end,int r[],int q[]){
    int left_idx = 0, right_idx = 0;
    for(int a=front;a<=mid;a++){
        left[left_idx] = p[a];
        r_left[left_idx] = r[a];
        q_left[left_idx] = q[a];
        left_idx++;
    }
    left[left_idx] = 2000000;
    for(int a=mid+1;a<=end;a++){
        right[right_idx] = p[a];
        r_right[right_idx] = r[a];
        q_right[right_idx] = q[a];
        right_idx++;
    }
    right[right_idx] = 2000000;
    left_idx = 0;
    right_idx = 0;

    for(int a=front;a<=end;a++){
        if(left[left_idx]<right[right_idx]){
            p[a] = left[left_idx];
            r[a] = r_left[left_idx];
            q[a] = q_left[left_idx];
            left_idx++;
        }
        else if(left[left_idx]==right[right_idx]){
            if(r_left[left_idx]>r_right[right_idx]){
                p[a] = left[left_idx];
                r[a] = r_left[left_idx];
                q[a] = q_left[left_idx];
                left_idx++;
            }
            else{
                p[a] = right[right_idx];
                r[a] = r_right[right_idx];
                q[a] = q_right[right_idx];
                right_idx++;
            }
        }
        else{
            p[a] = right[right_idx];
            r[a] = r_right[right_idx];
            q[a] = q_right[right_idx];
            right_idx++;
        }
    }
}

void mergesort(int p[],int front,int end,int r[],int q[]){
    if (front<end) {                   
        int mid = (front+end)/2;         
        mergesort(p, front, mid, r, q);    
        mergesort(p, mid+1, end, r, q);  
        merge(p, front, mid, end, r, q);  
    }  
}

void buildBIT(int sum[]){
    int lowbit;
    for(int a=1;a<=2100000;a++){
        lowbit = a&(-a);
        BIT[a] = sum[a]-sum[a-lowbit];
    }
}

int query(int idx){
    int ans=0;
    while(idx){
        ans+=BIT[idx];
        idx -= idx&(-idx);
    }
    return ans;
}

void delete(int idx){
    while(idx<=2100000){
        BIT[idx] -= 1;
        idx += idx&(-idx);
    }
}

int main() {
    generator.init();
    int t = generator.getT();
    while (t--){
        long long int ans=0;
        for(int a=0;a<=2100000;a++)
            sum[a]=0;
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
        for(int a=0;a<n;a++){
            if(q[a]>r[a]){
                int temp=q[a];
                q[a] = r[a];
                r[a] = temp;
            }
            sum[q[a]+1048577]++;
        }
        for(int a=2;a<=2100000;a++)
            sum[a]+=sum[a-1];

        mergesort(p,0,n-1,r,q);
        buildBIT(sum);
        
        for(int a=0;a<n;a++){
            delete(q[a]+1048577);
            ans+=query(r[a]+1048577);
        }
        
        printf("%lld\n",ans);
    }
}