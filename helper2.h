#ifndef LIBS2
#define LIBS2

#define DSIZE	8
#endif

void PUT(void* p, int val);
void PUT_SIZE(void* p, int size);
void PUT_ID(void* p, int ID);
void PUT_ALLOC(void* p, int flag);

int GET(void* p);
int GET_SIZE(void* p); 
int GET_ID(void* p);
int GET_ALLOC(void* p);

void* HDRP(void* p);
void* FTRP(void* p);
void* PREV_BLKP(void* p);
void* NEXT_BLKP(void* p);
