#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/ssl.h>
#include <openssl/sha.h>
#include "BlockChain_Tools.h"

typedef struct Block{
        char data[64];
        unsigned char hashprev[SHA256_DIGEST_LENGTH];
        struct Block* prev;
}Block;


typedef struct BlockChain{
        int len;
        Block* start;
}BlockChain;



void Add(BlockChain* ln){
        Block* st = malloc(sizeof(Block));
        printf("Write your data: ");
        char datast[64];
        scanf("%s", datast);
        if (ln->len == 0){
                st->prev = NULL;
                strcpy(st->data, datast);
        }
        else{
                strcpy(st->data, datast);
                st->prev = ln->start;
                SHA256(st->prev->data, strlen(st->prev->data), st->hashprev);
        }
        ln->start = st;
        ln->len++;
}

void Print(BlockChain* ln){
        Block* st = ln->start;
        int a = ln->len;
        printf("Len of BlockChain: %i\n", ln->len);
        while(st){
                printf("Data: %s Hashprev: ", st->data);
                if (a==1){
                        printf("None");
                }
                else{
                        for (int i = 0; i<SHA256_DIGEST_LENGTH; i++){
                                printf("%x", st->hashprev[i]);
                        }
                }
                a--;
                printf("\n");
                st = st->prev;
        }

}

void CheckHash(BlockChain* ln){
        Block* st = ln->start;
        Block* pred;
        unsigned char a[SHA256_DIGEST_LENGTH];
        int Flag = 1;
        int c = ln->len;
        while (c>1){
                pred = st;
                SHA256(st->prev->data, strlen(st->prev->data), a);
                printf("Hashteor: ");
                for (int i = 0; i<SHA256_DIGEST_LENGTH; i++){
                        printf("%x", a[i]);
                }
                printf("\nHashin: ");
                for (int i = 0; i<SHA256_DIGEST_LENGTH; i++){
                        printf("%x", pred->hashprev[i]);
                }
                printf("\n");
                for (int i = 0; i<SHA256_DIGEST_LENGTH; i++){
                        if (a[i]!=pred->hashprev[i]){
                                Flag = 0;
                        }
                }
                if (Flag == 0){
                        printf("ERROR HASH!!!\n");
                        break;
                }
                st = st->prev;
                c--;
        }
        if (Flag == 1){
                printf("Correct Hash!\n");
        }
}



void Quit(BlockChain *ln){
        Block* st = ln->start;
        Block* pred;
        while (st){
                pred=st->prev;
                free(st);
                st = pred;
        }
}



void Delete(BlockChain* ln){
        Block* st = ln->start;
        Block* pred = st;
        printf("Write key: ");
        char key[64];
        scanf("%s", key);
        int c = 0;
        while (st){
                if (!strcmp(key, st->data)){
                        break;
                }
                c++;
                pred = st;
                st = st->prev;
        }
        if (c==0){
                pred = st;
                ln->start = st->prev;
                free (pred);
        }
        else if (!(st->prev)){
                pred->prev = NULL;
                strcpy(pred->hashprev, "");
                free(st);
        }
        else{
                pred->prev = st->prev;
                SHA256(pred->prev->data, strlen(pred->prev->data), pred->hashprev);
                free(st);
        }
        ln->len--;
}

