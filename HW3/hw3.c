//
//  main.c
//  DS3-4
//
//  Created by 孫渝鈞 on 2021/12/11.
//
#include <stdio.h>
#include <math.h>


typedef struct node{
    int nodeID;
    int x;
    int y;
    int connectID;
    double con;
    double interN;
}node_t;

typedef struct link{
    int linkID;
    int sender;
    int receiver;
    int connect;
}link_t;

int number_nodes;
int number_links;
int power;
int N;
double sinr;
double firstsinr;
int firstreceiver;
double firstdistance;
double consumption;
double interference=0;
double sinr;
int success=0;

node_t nodes[100000];

link_t links[100000];



double Distance(int s_id,int r_id){  //算距離的平方
    
    return pow((nodes[s_id].x-nodes[r_id].x),2)+pow((nodes[s_id].y-nodes[r_id].y),2);

}

double SINR(int s_id,int r_id){      //算sinr值
    
    consumption=power/(pow(Distance(s_id,r_id),1.5));
    interference=0;
    
    for(int i=0;i<number_links;i++){
        
        if(links[i].connect==1&&links[i].sender!=s_id&&links[i].receiver!=r_id){
            interference+=(power/(pow(Distance(links[i].sender,r_id),1.5)));
            
        }
    }
    sinr=consumption/(interference+N);
    return sinr;
    
}

int main() {
    int sender_id;
    int receiver_id;
    scanf("%d",&number_nodes);
    scanf("%d",&number_links);
    scanf("%d",&power);
    scanf("%d",&N);
    
    for(int i=0;i<number_nodes;i++){
        scanf("%d %d %d",&nodes[i].nodeID,&nodes[i].x,&nodes[i].y);
        nodes[i].connectID=-1;
        nodes[i].con=0;
        nodes[i].interN=0;
    }
    for(int i=0;i<number_links;i++){
        scanf("%d %d %d",&links[i].linkID,&links[i].sender,&links[i].receiver);
        links[i].connect=0;
    }
    int count=0;
    
    for(int i=0;i<number_links;i++){     //先讓第一條醒來
        sender_id=links[i].sender;
        receiver_id=links[i].receiver;
        firstdistance=(power/pow(Distance(links[i].sender,links[i].receiver),1.5));
        firstsinr=firstdistance/N;
        if(firstsinr>1){
            nodes[sender_id].connectID=links[i].receiver;
            nodes[receiver_id].connectID=links[i].sender;
            links[i].connect=1;
            nodes[sender_id].con=(power/pow(Distance(links[i].sender,links[i].receiver),1.5));
            nodes[sender_id].interN=N;
            
            count++;
            break;
        }
    }
    double temph[number_nodes];   //設一個分母暫時要增加的陣列
    
    for(int i=0;i<number_links;i++){
        
        sender_id=links[i].sender;
        receiver_id=links[i].receiver;
        
        if(nodes[sender_id].connectID==-1&&nodes[receiver_id].connectID==-1){  //如果connectID都沒有連過
            
            for(int i=0;i<number_nodes;i++){
                temph[i]=0;
            }
            links[i].connect=1;   //先假設讓他連起來
            sinr=(SINR(links[i].sender,links[i].receiver));
            
            if(sinr>1){  //如果新增的線sinr>1
                
                nodes[sender_id].con=consumption;
                nodes[sender_id].interN=interference+N;
                
                for(int j=0;j<number_links;j++){   //算每個點的sinr值
                    if(links[j].connect==1&&i!=j){
                        
                        temph[links[j].sender]=(power/(pow(Distance(links[i].sender,links[j].receiver),1.5)));
                        
                        
                        nodes[links[j].sender].interN+=temph[links[j].sender];
                        
                        if(nodes[links[j].sender].interN<nodes[links[j].sender].con){   //if sinr>1 成功
                          
                            success=1;
                        }
                        else{  //if sinr<1 失敗
                           
                            for(int k=0;k<number_nodes;k++){   //要減掉剛剛加的值
                                nodes[k].interN-=temph[k];
                            }
                            for(int k=0;k<number_nodes;k++){
                                temph[k]=0;
                            }
                            
                            links[i].connect=0;
                            success=0;
                            break;
                        }
                    }
                }
            }
            else{  //如果新增的線sinr<1
                success=0;    //失敗
                links[i].connect=0;
            }
            if(success==1){  //如果新增進來能讓每個點的sinr>1 成功
                nodes[sender_id].connectID=links[i].receiver;
                nodes[receiver_id].connectID=links[i].sender;
                /*for(int j=0;j<number_nodes;j++){
                 printf("%d\n",nodes[j].connectID);
                 }*/
                links[i].connect=1;
                count++;
                //printf("%d %d %d\n",i,links[i].sender,links[i].receiver);
                
            }
            
        }
        
    }
    
    /*printf*/
    printf("%d\n",count);  //印出成功傳送的個數
    for(int i=0;i<number_links;i++){
        if(links[i].connect==1){
            printf("%d %d %d\n",i,links[i].sender,links[i].receiver);
        }
    }
    
    return 0;
}
