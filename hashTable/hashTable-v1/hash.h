#ifndef MY_MYHASH_H_
#define MY_MYHASH_H_

//哈希表（散列表）

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

//以储存int类型数据为例

#define HASHINVAILD  -10086
#define HASHMAXSIZE  1024
#define HASHINITSIZE 64

static int cur_hash_len = HASHINITSIZE;

typedef
struct _hash_t{
    int* elem;  //散列表首地址
    int size;   //当前哈希表中存放的数据个数
}hash_t;

bool 
InitHashTable(hash_t*);


//哈希函数（简单）
int 
HashFunc(int);

bool
InsertHash(hash_t*, int);


bool 
SearchHash(const hash_t*, int, int*);

void 
DestoryHash(hash_t*);


#endif