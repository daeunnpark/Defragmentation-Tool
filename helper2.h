#ifndef LIBS2
#define LIBS2

#define DSIZE	8
#endif
int tester(int x);

void PUT(void* p, int val);
void PUT_SIZE(void* p, int size);
void PUT_ID(void* p, int ID);
void PUT_ALLOC(void* p, int flag);


int GET(void* p);
int GET_SIZE(void* p); 
int GET_ID(void* p);
int GET_ALLOC(void* p);


void* HDRP(void* bp);
void* FTRP(void* bp);
void* NEXT_BLKP_RAM(void* bp, int* max_size);
void* NEXT_BLKP_BUF(void* bp, int* BUF_SIZE, int MAX_BUF_SIZE);
void* PREV_BLKP(void* bp, int* size);
void* NEXT_BLKP_C(void* bp, int* size);
void* PREV_BLKP_C(void* bp, int* size);

void* SWAP(void* prev, void* p, int* size);

//void initbuf(void* tmp_buf);

//char* FIRST_BLKP(void*bp);

/*
#define PUTSIZE(p, size)	{



(*(unsigned int *)(HDRP(p))= size))




}
#define PUTID(p,ID)	(*(unsigned int *)(p)= (ID<<1))
#define PUTALLOC(p, flag)	(*(unsigned int *)(p)= flag)   


#define GET_SIZE(p)	((GET(p) >>3)<<3)
#define GET_ID(p)	((GET(p) & 0x6 ) >>1)

#define GET_ALLOC(p)	(GET(p) & 0x1)
#define HDRP(bp)	 ((char*)(bp)-DSIZE)
#define FTRP(bp)	 ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE))  

#define NEXT_BLKP(bp)	((char*)(bp) +GET_SIZE(bp))

#define NEXT_BLKP(bp)	((char*)(bp) + GET_SIZE(((char*)(bp)-DSIZE)))

#define PREV_BLKP(bp)	((char*)(bp) + GET_SIZE(((char*)(bp)-2*DSIZE)))

*/

