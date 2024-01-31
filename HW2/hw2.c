//
//  main.c
//  DS-hw2mix
//
//  Created by 孫渝鈞 on 2021/11/16.
//
#include <stdio.h>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
#define nodesize_cols 2
#define link_cols 3
#define compare_size_cols 2
#define parent_cols 2

int cmp1(const void* p1, const void* p2)      //qsort排序
{
  const int* arr1 = (const int*)p1;
  const int* arr2 = (const int*)p2;
  return (arr2[1] < arr1[1]) - (arr2[1] > arr1[1]);
}
int cmp2(const void *a,const void *b)        //qsort排序
{
    int *c = (int *)a;
    int *d = (int *)b;
    if(*c != *d)
        return *c - *d;
    return *(d+1) - *(c+1);
}

int main()
{
    int nodes,links,packet_size;
    scanf("%d %d %d",&nodes,&links,&packet_size);  //輸入有幾個點,線,封包大小
    int nodesize[nodes][nodesize_cols];
    for(int i=0;i<nodes;i++){
        for(int j=0;j<2;j++){
            scanf("%d",&nodesize[i][j]);
        }
    }
    int link[links][link_cols];     //輸入有幾條線，線與線的連接點
    for(int i=0;i<links;i++){
        for(int j=0;j<3;j++){
            scanf("%d",&link[i][j]);
        }
    }
    
    int nodesize2[nodes][nodesize_cols];    //建立第二個方式要用的nodesize表，因為第一種方式會改變到nodesize的值
    for(int i=0;i<nodes;i++){
        for(int j=0;j<2;j++){
            nodesize2[i][j]=nodesize[i][j];
        }
    }
    
    
    /*第一種方式*/
    
    int parent1[nodes][parent_cols];          //建立父母表1
    for(int i=0;i<nodes;i++){
        parent1[i][0]=nodesize[i][0];
        parent1[i][1]=-1;
    }
    parent1[0][1]=0;
 
   
    
    int check1[links];           //確認該條線是否建立 0:失敗,1:成功 且有成功過就不能再連
    for(int i=0;i<links;i++){   //全初始化為0
        check1[i]=0;
    }
    int facksize;    //假的size，讓一開始可以比較，之後就會存真的size
    int p=nodes-1;   //parent表指標
    for(int i=nodes-1;i>=0;i--){
        
        facksize=1000000000;
        
        for(int j=0;j<links;j++){
            if(link[j][1]==nodesize[i][0]&&check1[j]!=1){
                if(nodesize[ link[j][2] ][1]<facksize){
                    parent1[p][1]=nodesize[ link[j][2] ][0];
                    facksize=nodesize[ link[j][2] ][1];
                }
            }
            if(link[j][2]==nodesize[i][0]&&check1[j]!=1){
                if(nodesize[ link[j][1] ][1]<facksize){
                    parent1[p][1]=nodesize[ link[j][1] ][0];
                    facksize=nodesize[ link[j][1] ][1];
                }
            }
        }
        for(int k=0;k<links;k++){
            if((link[k][1]==parent1[p][0]&&link[k][2]==parent1[p][1])||(link[k][1]==parent1[p][1]&&link[k][2]==parent1[p][0])){
                check1[k]=1;
                break;
            }
        }
        p--;
        
    }
    int child[2][nodes]; //建立一個放有多少小孩的陣列
    for(int i=0;i<2;i++){      //初始化為0
        for(int k=0;k<nodes;k++){
            child[i][k]=0;
        }
    }
    int father=0;
        for(int i=0;i<nodes;i++){
        child[0][i]=father;
        father++;
    }
    for(int father=0;father<nodes;father++){
        for(int i=1;i<nodes;i++){
            if(parent1[i][1]==father){
                child[1][father]++;
            }
        }
    }
    
    /*計算Total_cost*/
    int Total_cost1=0;
    int size;
    for(int i=0;i<nodes;i++){
        size=0;
        if(child[1][i]==0){  //從沒有小孩開始加
here:
            child[1][i]=-1; //改成-1避免重複走過
            for(int k=1;k<nodes;k++){ //找節點的size
                if(nodesize[k][0]==child[0][i]){
                    size+=nodesize[k][1];
                    Total_cost1+=size/packet_size;
                    if(size%packet_size!=0){
                        Total_cost1++;
                    }
                    child[1][parent1[i][1]]--;
                    if(child[1][parent1[i][1]]>0){
                        for(int k=1;k<nodes;k++){
                            if(nodesize[k][0]==child[0][parent1[i][1]]){
                                size+=nodesize[k][1];
                                nodesize[k][1]=size;
                                break;
                            }
                        }
                    }
                    if(child[1][parent1[i][1]]==0){
                        i=parent1[i][1];
                        goto here;
                    }
                    break;
                }
            }
        }
    }
    
    
    /*第二種方式*/
    
    qsort(nodesize2,nodes,nodesize_cols * sizeof(int), cmp1); //重新排序，size小的在上面
    int parent2[nodes][parent_cols]; //建立父母表
    for(int i=0;i<nodes;i++){
        for(int k=0;k<2;k++){
            parent2[i][k]=0;
        }
    }
    for(int i=0;i<nodes;i++){
        if(i==0){
            parent2[i][1]=0;
        }
        parent2[i][0]=nodesize2[i][0];
    }
    int check2[links];
    for(int i=0;i<links;i++){   //全初始化為0
        check2[i]=0;
    }
   
    p=1; //parent表
    for(int i=1;i<nodes;i++){
        for(int j=0;j<links;j++){
            if(link[j][1]==nodesize2[i][0]&&check2[j]!=1){
                check2[j]=1;
                parent2[p][1]=link[j][2];
                p++;
                break;
            }
            if(link[j][2]==nodesize2[i][0]&&check2[j]!=1){
                check2[j]=1;
                parent2[p][1]=link[j][1];
                p++;
                break;
            }
        }
    }
    
    qsort(parent2,nodes,sizeof(parent2[0]), cmp2);  //排序parent表
 
    for(int i=0;i<2;i++){      //初始化為0
        for(int k=0;k<nodes;k++){
            child[i][k]=0;
        }
    }
    father=0;
    for(int i=0;i<nodes;i++){
        child[0][i]=father;
        father++;
    }
    for(int father=0;father<nodes;father++){
        for(int i=1;i<nodes;i++){
            if(parent2[i][1]==father){
                child[1][father]++;
            }
        }
    }
    
    /*計算Total_cost*/
    int Total_cost2=0;
    for(int i=0;i<nodes;i++){
        size=0;
        if(child[1][i]==0){  //從沒有小孩開始加
here2:
            child[1][i]=-1; //改成-1避免重複走過
            for(int k=1;k<nodes;k++){ //找節點的size
                if(nodesize2[k][0]==child[0][i]){
                    size+=nodesize2[k][1];
                    Total_cost2+=size/packet_size;
                    if(size%packet_size!=0){
                        Total_cost2++;
                    }
                    child[1][parent2[i][1]]--;
                    if(child[1][parent2[i][1]]!=0){
                        for(int k=1;k<nodes;k++){
                            if(nodesize2[k][0]==child[0][parent2[i][1]]){
                                size+=nodesize2[k][1];
                                nodesize2[k][1]=size;
                                break;
                            }
                        }
                    }
                    if(child[1][parent2[i][1]]==0){
                        i=parent2[i][1];
                        goto here2;
                    }
                    break;
                }
            }
        }
    }
    
    /*比較哪一種Total_cost最小*/
    
    if(Total_cost1<=Total_cost2){
        
        printf("%d ",nodes);
        printf("%d\n",Total_cost1);
        for(int i=0;i<nodes;i++){
            for(int k=0;k<2;k++){
                printf("%d ",parent1[i][k]);
            }
            printf("\n");
        }
    }
    else{
        printf("%d ",nodes);
        printf("%d\n",Total_cost2);
        for(int i=0;i<nodes;i++){
            for(int k=0;k<2;k++){
                printf("%d ",parent2[i][k]);
            }
            printf("\n");
        }
    }
    
    return 0;
}
