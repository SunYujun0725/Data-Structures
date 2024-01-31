//
//  main.c
//  DS4-1
//
//  Created by 孫渝鈞 on 2022/1/1.
//
#include <stdio.h>
#include <math.h>
int main() {
    unsigned int p,m,n;  //輸入p,開m個bit,n個ID
    scanf("%u %u %u",&p,&m,&n);
    unsigned int ID;
    int o;  //要開幾個unsigned int陣列
    o=m/32;
    if(m%32!=0){
        o+=1;
    }
    unsigned int tf[o];
    for(int i=0;i<o;i++){ //將ture flase table出始為0
        tf[i]=0;
    }
    unsigned int address; //要放的位置
    unsigned int k;  //在第幾個int陣列裡
    unsigned int compare;  //要跟第幾個bit比
    if(m<=15){
        for(int i=0;i<n;i++){
            scanf("%u",&ID);
            address=ID%m;  //要放的位置
            k=address/32;  //放在第幾個陣列
            compare=pow(2,(31-(address-32*k)));  //要跟第幾個位置比
            if((tf[k]&compare)!=0){    //不可以放
                printf("%u %u\n",ID,0);
            }
            else{    //可放
                printf("%u %u\n",ID,1);
                tf[k]+=compare;
            }
        }
    }
    else if(m>15&&m<7000){
        for(int i=0;i<n;i++){
            scanf("%u",&ID);
            address=ID*ID*ID*ID*ID*ID*ID%(p*m*p*m*p*m+(m-p)*m-p)%p%m;
            k=address/32;
            compare=pow(2,(31-(address-32*k)));
            if((tf[k]&compare)!=0){   //不可以放
                printf("%u %u\n",ID,0);
            }
            else{
                printf("%u %u\n",ID,1);
                tf[k]+=compare;
            }
        }
    }
    else{
        for(int i=0;i<n;i++){
            scanf("%u",&ID);
            address=ID%p%m;
            k=address/32;
            compare=pow(2,(31-(address-32*k)));
            if((tf[k]&compare)!=0){   //不可以放
                printf("%u %u\n",ID,0);
            }
            else{
                printf("%u %u\n",ID,1);
                tf[k]+=compare;
            }
        }
    }
    return 0;
}
