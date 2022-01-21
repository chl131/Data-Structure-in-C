#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 13
#define PRIME 7

int hash1(int key){
    return key % TABLE_SIZE;
}

int hash2(int key){
    return PRIME-(key%PRIME);
}

int hash_func(int key, int i){
    return (hash1(key) + i*hash2(key))%TABLE_SIZE;
}

int main()
{
    int hash_table[TABLE_SIZE];
    int hash_table_status[TABLE_SIZE] = {0};
    int value;
    int value_status;
    int hash_value;
    int inputs_size = 0;
    int i;

    /*Hash all the inputs*/
    while(scanf("%d", &value) != EOF){
        inputs_size++;
        i = 0;
        value_status = 0;
        while(value_status == 0){
            hash_value = hash_func(value, i);
            if(hash_table_status[hash_value] == 0){
                hash_table[hash_value] = value;
                value_status = 1;
                hash_table_status[hash_value] = 1;
            }
            i++;
        }
    }
    /*End of hashing*/


    /*Print the hash table*/
    int j = 0;
    int j_old;
    i = 0;

    if(inputs_size != 0){
        while(j==0){
            if(hash_table_status[i] == 1){
                printf("%d->%d", i, hash_table[i]);
                j++;
            }
            i++;
        }
    }

    while(j<inputs_size){
        printf("\n");
        j_old = j;
        while(j == j_old){
            if(hash_table_status[i] == 1){
                printf("%d->%d", i, hash_table[i]);
                j++;
            }
            i++;
        }
    }
    /*End of printing the hash table*/

    return 0;
}
