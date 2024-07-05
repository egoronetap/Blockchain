#ifndef BLOCKCHAIN_TOOLS__H
#define BLOCKCHAIN_TOOLS__H

typedef struct BlockChain BlockChain;

void Print(BlockChain*ln);
void Add(BlockChain*ln);
void Delete(BlockChain*ln);
void Quit(BlockChain*ln);
void CheckHash(BlockChain*ln);

#endif
