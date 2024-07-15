#ifndef STRAND_H_
#define STRAND_H_

// 数据结构--串
// 顺序储存结构

#include <stdio.h>
#include <stdint.h>

#define STRAND_MAX_LENGTH 1024

typedef struct yichenStrand {
    char buffer[STRAND_MAX_LENGTH];
    /* 字符串长度 */
    size_t size;
    /* 字符串最大容量 */
    size_t capacity;
}Strand;

/* 初始化字符串 */
void StrandInit(Strand*);
/* 获取字符大小 */
size_t getStrandSize(Strand*);
/* 获取字符最大容量 */
size_t getStrandCapacity(Strand*);
/* 尾插 */
int StrandPush_back(Strand*, char*, size_t);
/* 尾删 */
int StrandPop_back(Strand*, size_t);
/* 清空 */
void StrandClear(Strand*);
/* 打印输出有效字符 */
void ValidStrandPrint(Strand*);



#endif