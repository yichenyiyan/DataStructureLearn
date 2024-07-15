#include "strand.h"

void StrandInit(Strand* s) {
    s->size = 0;
    StrandClear(s);
    s->capacity = sizeof(s->buffer);
}

size_t getStrandSize(Strand* s) {
    return s->size;
}

size_t getStrandCapacity(Strand* s) {
    return s->capacity;
}

int StrandPush_back(Strand* s, char* push_str, size_t push_str_size) {
    if (s->size + push_str_size > s->capacity)
        return -1;
    
    /* 细节：插入字符的push_str_size 默认其是由sizeof计算，其实真正的字符数为push_str_size - 1 */
    for (size_t i = 0; i < push_str_size - 1; ++i) {
        *(s->buffer + s->size + i) = *(push_str + i);
    }

    s->size += push_str_size - 1;

    return 0;
}

int StrandPop_back(Strand* s, size_t pop_size) {
    if (pop_size > s->size)
        return -1;
    
    s->size -= pop_size;
    s->buffer[s->size] = '\0'; 

    return 0;
}

void StrandClear(Strand* s) {
    for (size_t i = 0; i < sizeof(s->buffer); ++i) {
        *(s->buffer) = '\0';
    }
    s->size = 0;
}

void ValidStrandPrint(Strand* s) {
    s->buffer[s->size] = '\0';

    printf("Valid String: %s\n", s->buffer);
}