#include "helper2.h"
#include <stdio.h>
#define DSIZE   8  




int tester(int x){
	return x+2;
}




void initbuf(* tmp_buf){
	PUTSIZE(HDRP(tmp_buf),128)
		PUTSIZE(FTRP(tmp_buf),128)
		PUTID(tmp_buf,0)
}
/*
 *char HDRP(*char bp){
 return ((char*)(bp)-DSIZE)
 }


 *char FTRP(*char bp){
 return ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE));  

 }
 */


void PUTSIZE(*void, size){
PUT(HDRP(p),size);
PUT(FTRP(p),size);

}

void PUTID(*void p, int ID){
PUT(HDRP(p), );
}


void PUT(p, val){    
	(*(unsigned int *)(p)= (val)); 
}


// not int?
int GET(p){
	return (*(unsigned int *)(p));  
}


int GET_SIZE(p){   
	return ((GET(p) >>3)<<3);
}

int GET_ID(p){      
	return ((GET(p) & 0x6 ) >>1);
}

int GET_ALLOC(p){    
	return (GET(p) & 0x1);
} 

*char HDRP(bp){        
	return ((char*)(bp)-DSIZE);
}

*char FTRP(bp){
	return ((char*)(bp)+ GET_SIZE(HDRP(bp))-(2*DSIZE)); 
}

*char NEXT_BLKP(bp){  
	return ((char*)(bp) +GET_SIZE(bp));
}


/*
 *char PREV_BLKP(bp){ 


 return (char*)(bp) + GET}
 */



