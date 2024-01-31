#include<stdio.h>
#include<stdlib.h>
unsigned int hash_func(unsigned int id, unsigned int p, unsigned int m){
    return id % p % m;
}

int main(){
    unsigned int p, m, n;
    char id[1000];
    scanf("%u%u%u", &p, &m, &n);
    unsigned int* showed = malloc( sizeof(unsigned int) * (m/32+1) );

    //init
    for(int i = 0; i < (m/32+1); i++){
        showed[i] = 0;
    }

    for(int i = 0; i < n; i++){
        unsigned int id_num;
        scanf("%u", &id_num);
        unsigned int hash_num = hash_func(id_num, p, m);
        int idx = hash_num / 32, bit_pos = hash_num % 32;
        if(showed[idx] & (1 << bit_pos)) printf("%u 0\n", id_num);
        else printf("%u 1\n", id_num);
        showed[idx] |= (1 << bit_pos);
    }
    return 0;
}
