#include "helper2.h"
#include <stdio.h>
#define DSIZE   8  


void PUT(void* p, int val){
//	(*(unsigned int *)(p)= (val)); 
 (*(int *)(p)= (val));
}


void PUT_SIZE(void* p, int size){
int flag = GET_ALLOC(p);
int ID = GET_ID(p);

PUT(p,size);// always ending with 000 since size if multiple of 16
PUT_ID(p,ID);
PUT_ALLOC(p,flag);

//BAD EX:	PUT( p, GET(p)<<61>>61 | size);
// For big nums, sign bit =1 and shifting -> - numb
// So, set size and re set ID and alloc

}

void PUT_ID(void* p, int ID){
int flag = GET_ALLOC(p);
int size = GET_SIZE(p);

PUT(p,size);// set 3 last bits to 0
	PUT( p, GET(p) | (ID<<1));
PUT_ALLOC(p,flag);

}


void PUT_ALLOC(void* p, int flag){
PUT( p, (GET(p)>>1)<<1 | flag); // reset to 0 and 
}


int GET(void* p){
//	return (*(unsigned int *)(p));  
return (*(int *)(p));
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

void* HDRP(void* bp){        
	return bp;
}

void* FTRP(void* bp){
	return ((char*)(bp) + GET_SIZE(bp) - DSIZE);
}

void* PREV_BLKP(void* bp){ 
return ((char*)(bp) - GET_SIZE((char *)(bp)-DSIZE));
}


void* NEXT_BLKP(void* bp){  
return ((char*)(bp)+GET_SIZE(bp));
}

void* NEXT_BLKP2(void* bp){  
if(GET(bp)==0){
return ((char*)(bp)+8);
}
return ((char*)(bp)+GET_SIZE(bp)); 

}





