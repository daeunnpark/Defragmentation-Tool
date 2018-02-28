#include "helper2.h"
#include <stdio.h>
#include <string.h>
#define DSIZE   8  
#define MAXSIZE2 1024



int tester(int x){
	return x+2;
}


void initbuf(void* tmp_buf){

	printf("INTI HERE\n");
	PUT_SIZE(tmp_buf,128);
	PUT_ID(tmp_buf,0);

	printf("TMP SIZE: %d\n",GET_SIZE(tmp_buf) );
	tmp_buf += GET_SIZE(tmp_buf);
}

void PUT(void* p, int val){
	(*(unsigned int *)(p)= (val)); 
}


void PUT_SIZE(void* p, int size){
	/*
	   PUT(HDRP(p), (GET(HDRP(p))<<61)>>61 | size);
	   PUT(FTRP(p),(GET(FTRP(p))<<61)>>61 | size);
	 */
	PUT( p, (GET(p)<<61)>>61 | size);
}

void PUT_ID(void* p, int ID){
	/*
	   PUT(HDRP(p),GET(HDRP(p)) | ID<<1 );
	   PUT(FTRP(p),GET(FTRP(p)) | ID<<1 );
	 */

	PUT( p, GET(p) | (ID<<1));
}


void PUT_ALLOC(void* p, int flag){
	/*	
		PUT(HDRP(p),GET(HDRP(p)) | flag);
		PUT(FTRP(p),GET(FTRP(p)) | flag);
	 */
	PUT( p, GET(p) | flag); 
}


// not int?
int GET(void* p){
	return (*(unsigned int *)(p));  
}


int GET_SIZE(void* p){   
	return ((GET(p) >>3)<<3);
}

int GET_ID(void* p){      
	return ((GET(p) & 0x6 ) >>1);
}

int GET_ALLOC(void* p){    
	return (GET(p) & 0x1);
} 

char* HDRP(void* bp){        
	//	return ((char*)(bp)-DSIZE);
	return bp;
}
//Footer of bp
char* FTRP(void* bp){
	//	return ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE)); 
	return ((char*)(bp) + GET_SIZE(bp) - DSIZE);
}
//Header of NEXT
char* NEXT_BLKP_RAM(void* bp, int* RAM_SIZE){  
RAM_SIZE+=GET_SIZE(bp);	
if( MAXSIZE2 < RAM_SIZE){
return NULL;
}

return ((char*)(bp)+GET_SIZE(bp));
	//return ((char*)FTRP(bp) + DSIZE);

}

//Header of NEXT
char* NEXT_BLKP_BUF(void* bp, int *BUF_SIZE, int MAX_BUF_SIZE){  
BUF_SIZE+=GET_SIZE(bp);
if( MAX_BUF_SIZE < BUF_SIZE ){
return NULL;
}

return ((char*)(bp)+GET_SIZE(bp));
	//return ((char*)FTRP(bp) + DSIZE);

}


//Header of PREV
char* PREV_BLKP(void* bp, int *size){ 
size-=GET_SIZE(bp);	
	   if(size<0){
	   return NULL; // DEFAULT FREE
	   } 
	 	
return ((char*)(bp) - GET_SIZE((char *)(bp)-DSIZE));
}


char* SWAP(void* prev, void* p){
	int SIZE = GET_SIZE(prev);
	int ID = GET_ID(prev);
	int FLAG = GET_ALLOC(prev);
	char temp[GET_SIZE(prev)];
	printf("HERE SWAPS\n");

	memcpy(temp, prev, GET_SIZE(prev));
	memmove(prev, p, GET_SIZE(p));
	memcpy(NEXT_BLKP(prev),temp,GET_SIZE(temp));
	
printf("HERE: %d %d %d\n", SIZE, ID, FLAG);
	printf("NEW PREV : %d %d %d\n", GET_SIZE(prev), GET_ID(prev), GET_ALLOC(prev));
	printf("NEW now : %d %d %d\n", GET_SIZE(NEXT_BLKP(prev)), GET_ID(NEXT_BLKP(prev)), GET_ALLOC(NEXT_BLKP(prev)));

	return prev; 

}

