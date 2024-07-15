#include"hash.h"

bool
InitHashTable(hash_t* h){
    h->size = cur_hash_len;
    h->elem = (int*)malloc((h->size)*sizeof(int));
    if(h->elem == NULL)
        return false;
    
    for(int i = 0; i < cur_hash_len; ++i){
        h->elem[i] = HASHINVAILD;
    }

    return true;
}



int 
HashFunc(int key){
    return key % cur_hash_len;
}


bool
InsertHash(hash_t* h, int val){
    int idx = HashFunc(val);
    if(h->elem[idx] == HASHINVAILD)//此案例中未对哈希冲突进行处理
        h->elem[idx] = val;
    else
        return false;
    
    return true;
}

bool 
SearchHash(const hash_t* h, int val, int* ret){
    int idx = HashFunc(val);
    if(h->elem[idx] == HASHINVAILD)
        return false;
    else
        *ret = h->elem[idx];

    return true;
}


void
DestoryHash(hash_t* h){
    free(h->elem);
}