#ifndef LIBS2
#define LIBS2

#define DSIZE	8
//#define PACK
#define GET(p)	(*(unsigned int *)(p))
#define PUT(p, val)	(*(unsigned int *)(p)= (val))

#define GET_SIZE(p)	((GET(p) >>3)<<3)
#define GET_ID(p)	((GET(p) & 0x6 ) >>1)

#define GET_ALLOC(p)	(GET(p) & 0x1)
#define HDRP(bp)	 ((char*)(bp)-DSIZE)
#define FTRP(bp)	 ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE))  

#define NEXT_BLKP(bp)	((char*)(bp) +GET_SIZE(bp))
/*
#define NEXT_BLKP(bp)	((char*)(bp) + GET_SIZE(((char*)(bp)-DSIZE)))

#define PREV_BLKP(bp)	((char*)(bp) + GET_SIZE(((char*)(bp)-2*DSIZE)))

*/

#endif
int tester(int x);
