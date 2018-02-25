#include "helper2.h"
#include <stdio.h>
#include <string.h>
#define DSIZE   8  
#define MAXSIZEbuf 1024



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
/*
 *char HDRP(*char bp){
 return ((char*)(bp)-DSIZE)
 }


 *char FTRP(*char bp){
 return ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE));  

 }
 */

void PUT(void* p, int val){
	(*(unsigned int *)(p)= (val)); 
}


void PUT_SIZE(void* p, int size){
	PUT(HDRP(p), (GET(HDRP(p))<<61)>>61 | size);
	PUT(FTRP(p),(GET(FTRP(p))<<61)>>61 | size);
}

void PUT_ID(void* p, int ID){
	PUT(HDRP(p),GET(HDRP(p)) | ID<<1 );
	PUT(FTRP(p),GET(FTRP(p)) | ID<<1 );
}

void PUT_ALLOC(void* p, int flag){
	PUT(HDRP(p),GET(HDRP(p)) | flag);
	PUT(FTRP(p),GET(FTRP(p)) | flag);
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

char* FTRP(void* bp){
	//	return ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE)); 
	return ((char*)(bp)+ DSIZE + GET_SIZE(bp));
}

char* NEXT_BLKP(void* bp){  
	return ((char*)(bp)+GET_SIZE(bp));
	//return ((char*)FTRP(bp) + DSIZE);

}

//MAXSIZEbuf can be modified!! put as args?
//Returns first block with ID
char* FIRST_ID_BLKP(void* bp, int ID){
	
int currentSIZEbuf = 0;
while (currentSIZEbuf < MAXSIZEbuf){
		if(GET_ID(bp)!=ID){
			bp = NEXT_BLKP(bp);
			currentSIZEbuf+=GET_SIZE(bp);
		}else{
			return bp;

		}

	}

	return NULL;
}

char* PREV_BLKP(void* bp){ 
/*
	if(GET_ID(bp)==0){
		return NULL; // DEFAULT FREE
	} 
*/	return ((char*)(bp) - GET_SIZE((char *)(bp)-DSIZE));
}


char* FIRST_BLKP(void* bp){
	while(GET_ID(bp)!=NULL){
		if(GET_ID(bp)==0 && GET_SIZE(bp)==128){
			break;

		}//else{
		bp= PREV_BLKP(bp);

	}
	return bp;
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
/*
PUT_SIZE(NEXT_BLKP(prev),SIZE);
PUT_ID(NEXT_BLKP(prev),ID);
PUT_ALLOC(NEXT_BLKP(prev),FLAG); 
*/

printf("NEW now : %d %d %d\n", GET_SIZE(NEXT_BLKP(prev)), GET_ID(NEXT_BLKP(prev)), GET_ALLOC(NEXT_BLKP(prev)));


return prev; 

}

