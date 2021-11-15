//
//  main.c
//  DS1
//
//  Created by 孫渝鈞 on 2021/10/12.
//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int Encode(int Mode,int n,int m)
{
    char InputString[10000]; //用字元來表示資料
    scanf("%s",InputString);
    int StringLen;  //原字串資料長度
    StringLen=strlen(InputString);
    int cut_strlen;  //切割後每個字串的長度
    cut_strlen=StringLen/n;
    char cut_string[n][cut_strlen];  //分割後的每段字串
    int k=0;
    for(int i=0;i<n;i++){             //分割資料
        for(int j=0;j<cut_strlen;j++){
            cut_string[i][j]=InputString[k];
            k++;
        }
    }
    int int_cut_string[n]; //分割後的int資料
    for(int i=0;i<n;i++){
        int_cut_string[i]=0; //皆初始化為0
    }
    int power; //次方
    for(int i=0;i<n;i++){  //將字串轉成int
        power=cut_strlen-1;
        for(int j=0;j<cut_strlen;j++){
            int_cut_string[i]+=(cut_string[i][j]-48)*pow(10,power);
            power=power-1;
        }
    }
    int print_matrix[n+m][n+1]; //要印出來的陣列
    for(int i=0;i<n;i++){
        for(int j=0;j<n+1;j++){
            if(j!=n){
                if(i==j){
                    print_matrix[i][j]=1;
                }
                else{
                    print_matrix[i][j]=0;
                }
            }
            else{
                print_matrix[i][j]=int_cut_string[i];
            }
        }
    }
    int v=1;
    for(int i=n;i<n+m;i++){    //Vandermonde matrix
        int count=0;           //計數
        int last=0;            //每一列的最後一個數字
        for(int j=0;j<n+1;j++){
            if(j!=n){
                print_matrix[i][j]=pow(v,j);
                last+=print_matrix[i][j]*int_cut_string[count];
                count++;
            }
            else{
                print_matrix[i][j]=last;
            }
        }
        v++;
    }
    for(int i=0;i<n+m;i++){    //印出答案
        for(int j=0;j<n+1;j++){
            printf("%d ",print_matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
int Decode(int Mode,int n)
{
    float matrix[n+1][n+1];    //原線性矩陣（要用float存，因為相除可能會有小數點的問題）
    for(int i=0;i<n;i++){      //輸入線性方程組
        for(int j=0;j<n+1;j++){
            scanf("%f",&matrix[i][j]);
        }
    }
    int j;
    float temp[n+1],ratio;     //temp是對調時暫時存放的陣列
    for(int i=0;i<n;i++){      //用高斯消去法最理想解是要matrix[i][i]為常數，其餘為0（對角線下的三角形要為0)
        if(matrix[i][i]==0){   //當matrix[i][i]為0時，就要與另一列對換
            j=i+1;
            while(matrix[j][i]==0){ //找下一列matrix[i][i]!=0
                j++;
            }
            for(int k=0;k<n+1;k++){ //找到後兩列對調
                temp[k]=matrix[i][k];
                matrix[i][k]=matrix[j][k];
                matrix[j][k]=temp[k];
            }
        }
        for(j=i+1;j<n;j++){    //與下一列相消產生０
            ratio=matrix[j][i]/matrix[i][i];  //倍數
            for(int k=0;k<n+1;k++){           //兩列對消
                matrix[j][k]=matrix[j][k]+(-1)*ratio*matrix[i][k];
            }
        }
    }
    float ans[n+1];  //最後xyz的解
    ans[n-1]=matrix[n-1][n]/matrix[n-1][n-1];  //從最後一列開始，因為未知數最少
    for(int i=n-2;i>=0;i--){   //從倒數第二列開始往上推答案
        ans[i]=matrix[i][n];
        for(int j=i+1;j<n;j++){
            ans[i]=ans[i]+(-1)*matrix[i][j]*ans[j];
        }
        ans[i]=ans[i]/matrix[i][i];
     }

     for(int i=0;i<n;i++){  //印出答案
         printf("%0.0f",ans[i]);
     }
  
     return 0;
}
int main()
{
    int Mode;    //Mode=0(Encode),Mode=1(Decode)
    scanf("%d",&Mode);
    if(Mode==0){
        int n,m;
        scanf("%d %d",&n,&m);
        Encode(Mode,n,m);  //進入Encodec函式
    }
    else if(Mode==1){
        int n;
        scanf("%d",&n);
        Decode(Mode,n);    //進入Decodec函式
    }
    
    return 0;
}
