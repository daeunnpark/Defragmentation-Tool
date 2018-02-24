#include "helper2.h"
#include <stdio.h>
#define DSIZE   8  




int tester(int x){
	return x+2;
}




void initbuf(void* tmp_buf){

printf("INTI HERE\n");
	PUT_SIZE(tmp_buf,128);
	PUT_ID(tmp_buf,0);
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

char*  NEXT_BLKP(void* bp){  
	return ((char*)(bp)+GET_SIZE(bp));
//return ((char*)FTRP(bp) + DSIZE);

}


/*
 *char PREV_BLKP(bp){ 


 return (char*)(bp) - GET}
 }

*/

