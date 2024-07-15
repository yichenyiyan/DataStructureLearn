#include "strand.h"
#include <stdlib.h>


static void testFunc1() {
    Strand* s = (Strand*)malloc(sizeof(Strand));
    StrandInit(s);

    printf("s->size: %ld\n", s->size);
    printf("s->capacity: %ld\n", s->capacity);

    printf("getSize: %ld\n", getStrandSize(s));
    printf("getCapacity: %ld\n", getStrandCapacity(s));

    ValidStrandPrint(s);

    char buf[] = "hello yichen!";
    printf("buf size: %ld\n", sizeof(buf));
    printf("push_back return: %d\n", StrandPush_back(s, buf, sizeof(buf)));
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    StrandClear(s);
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    printf("push_back return: %d\n", StrandPush_back(s, buf, sizeof(buf)));
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    printf("pop_back return: %d\n", StrandPop_back(s, 20));
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    printf("pop_back return: %d\n", StrandPop_back(s, 6));
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    printf("pop_back return: %d\n", StrandPop_back(s, 1));
    printf("getSize: %ld\n", getStrandSize(s));

    ValidStrandPrint(s);

    free(s);
}

int main(int argc, char** argv) {
    testFunc1();
    return 0;
}