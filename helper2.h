#ifndef LIBS2
#define LIBS2

#define DSIZE	8
//#define PACK

//#define PUT(p, val)	(*(unsigned int *)(p)= (val))  

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


char* HDRP(void* bp);
char* FTRP(void* bp);
char* NEXT_BLKP_RAM(void* bp, int *max_size);
char* NEXT_BLKP_BUF(void* bp, int *BUF_SIZE, int MAX_BUF_SIZE);
char* PREV_BLKP(void* bp, *int size);
char* FIRST_ID_BLKP(void* bp,int ID);
char* FIRST_BLKP(void*bp);
void initbuf(void* tmp_buf);
char* SWAP(void* prev, void* p);
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

