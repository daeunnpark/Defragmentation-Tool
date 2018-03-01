#include "helper.h"
#include "helper2.h"
#define MAXSIZE	1024
#define TEMP_RAM_SIZE 128


void* sort(void* bp, int BUF_SIZE);
void print_RAM(void* bp, int RAM_COUNT);
//void print_BUF(void* bp, int COUNT);
void* coalesce(void *bp,int RAM_SIZE);



struct Block {
	void * addr; // addr of header
	// char* = 8 bytes 
};

int main(int argc, char** argv) {
	if (*(argv + 1) == NULL) {
		printf("You should provide name of the test file.\n");
		return 1;
	}
	void* ram = cse320_init(*(argv + 1));
	void* tmp_buf = cse320_tmp_buffer_init();
	int ret = 0;
	/*
	 * You code goes below. Do not modify provided parts
	 * of the code.
	 */

	int RAM_COUNT = 0;
	int BUF_COUNT=0;
	ssize_t INCR_BUF_SIZE=0;
	int MAX_BUF_SIZE = 128;
	int firstflag=0;
	int secondflag=0;
	int ID = 0;
	void* cursor;
	void* BUF_cursor;
	// Traverse	

	printf("-----FROM HERE----\n");
	print_RAM(ram,160);
	/*
	   printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   ram = NEXT_BLKP(ram);
	   printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));


	 */

	cursor = ram;
	BUF_cursor = tmp_buf;
	while(RAM_COUNT + GET_SIZE(cursor) < MAXSIZE+1){

		if(GET_ID(cursor)==1 || GET_ID(cursor)==2 || GET_ID(cursor)==3){

			printf("!!!HH!!!!!\n");

			// Not enough BUF
			if(BUF_COUNT + GET_SIZE(cursor) >  MAX_BUF_SIZE){
				if(MAX_BUF_SIZE < MAXSIZE+1){			
					ssize_t size = BUF_COUNT+GET_SIZE(cursor) - MAX_BUF_SIZE;
					//	INCR_BUF_SIZE+=size;
					printf("-----SBRK-----\n");
					if(cse320_sbrk(size)==NULL){
						//	printf(errno);
						perror("");					
						exit(errno);
					}
					BUF_COUNT+=GET_SIZE(cursor);
					MAX_BUF_SIZE+=size;
				}
				printf("Print error\n");

			}			
			memmove(BUF_cursor, cursor , GET_SIZE(cursor));
			printf("ddd\n");  
			BUF_COUNT+=GET_SIZE(BUF_cursor);
			printf("BUF COuNT: %d\n", BUF_COUNT);
			printf("aaaa\n");		

			print_RAM(tmp_buf,BUF_COUNT);

			printf("sss\n");  		
			sort(BUF_cursor,BUF_COUNT-GET_SIZE(tmp_buf));		
			printf("kkk\n");  	
			printf("After: %p\n",tmp_buf); 		
				print_RAM(tmp_buf,BUF_COUNT);


			RAM_COUNT+=GET_SIZE(ram);
			cursor = NEXT_BLKP(cursor);


			BUF_cursor = NEXT_BLKP(BUF_cursor);



		} else {

			if ( RAM_COUNT+4 < MAXSIZE+1 ){
				ram += 4; //4 bytes
				RAM_COUNT+=4;
			}

			else{

				printf("-- END of Ram222 -- \n");
				break;
			}
		}



	}
	printf("-- END of Ram -- \n");
	// Not enough mem in Ram for last block

	if(RAM_COUNT+16 < MAXSIZE+1){
		errno=ENOMEM;
		printf("SBRK_ERROR\n");

		exit(errno);
	}




	// GET FIRST BLOCK
	while(-1< RAM_COUNT-GET_SIZE(PREV_BLKP(ram))){
		RAM_COUNT-=GET_SIZE(PREV_BLKP(ram));
		ram = PREV_BLKP(ram);
	}

	while(-1<BUF_COUNT - GET_SIZE(PREV_BLKP(tmp_buf))){
		BUF_COUNT-=GET_SIZE(PREV_BLKP(tmp_buf));
		tmp_buf = PREV_BLKP (tmp_buf);
	}


	memcpy(ram, tmp_buf,BUF_COUNT);		//LAST BLOCK
	ram = coalesce(ram,RAM_COUNT); // ram points at last block


	PUT_SIZE(HDRP(ram),16);
	PUT_SIZE(FTRP(ram),16);
	PUT_ID(HDRP(ram),0);
	PUT_ID(FTRP(ram),0);
	PUT_ALLOC(HDRP(ram),0);
	PUT_ALLOC(FTRP(ram),0);

	while(-1< RAM_COUNT-GET_SIZE(PREV_BLKP(ram))){
		RAM_COUNT-=GET_SIZE(PREV_BLKP(ram));
		ram = PREV_BLKP(ram);
	}


	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}


void* sort(void *bp, int BUF_COUNT){
	// only 1 element

	int totalSIZE=0;

	if(BUF_COUNT==0){
		printf("1 to SORT\n");
		return bp;

	} else {

		totalSIZE = BUF_COUNT+(GET_SIZE(bp));

		while( (0 < BUF_COUNT) && ( GET_ID( PREV_BLKP(bp) ) > GET_ID(bp)) ){

			BUF_COUNT-=GET_SIZE(PREV_BLKP(bp));
			bp = SWAP( PREV_BLKP(bp) ,bp);     

		}	

		while( (0 < BUF_COUNT) && (GET_ID(PREV_BLKP(bp)) == GET_ID(bp)) && ((GET_ALLOC(PREV_BLKP(bp)) == 0) && (GET_ALLOC(bp)== 1)) ){
			BUF_COUNT-=GET_SIZE(PREV_BLKP(bp));
			bp = SWAP(PREV_BLKP(bp),bp);

		}

		while( (0 < BUF_COUNT)  && (GET_ID(PREV_BLKP(bp)) == GET_ID(bp)) && (GET_ALLOC(PREV_BLKP(bp)) == GET_ALLOC(bp)) && (GET_SIZE(PREV_BLKP(bp)) > GET_SIZE(bp)) ){
			BUF_COUNT-=GET_SIZE(PREV_BLKP(bp));
			bp = SWAP(PREV_BLKP(bp),bp);     		
		}

		printf("SORTED\n");

		//Last block
		printf("BUF COUNT MUST BE 0: %d\n",BUF_COUNT);
		while(BUF_COUNT+ GET_SIZE(bp)<totalSIZE+1){

			BUF_COUNT+= GET_SIZE(bp);
			bp = NEXT_BLKP(bp);

		}

	}

	return bp;

}




// bp = first block of ram
void print_RAM(void* bp,int RAM_SIZE){ 
	printf("---RAM PRINTING---\n");
	//for 1st block

	int	RAM_COUNT2 = 0;
	while( RAM_COUNT2 + GET_SIZE(bp) < RAM_SIZE+1){

		if(GET_ID(bp)==1 || GET_ID(bp)==2 || GET_ID(bp)==3){

			printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(bp), GET_ID(bp), GET_ALLOC(bp));
			//printf("11RAM SIZE = %d\n", RAM_SIZE);


			RAM_COUNT2+=GET_SIZE(bp);

			bp = NEXT_BLKP(bp);
			if(RAM_COUNT2==RAM_SIZE){
				break;

			}



		} else {
			printf("HEEE\n");
			if ( RAM_COUNT2+4 < RAM_SIZE+1 ){
				bp += 4; //4 bytes
				RAM_COUNT2+=4;
			}else {

				printf("-- END of Ram333 -- \n");  
				break;

			}

		}
	}

	printf("---END RAM PRINTING---\n");  


}
/*
   void print_BUF(void* tmp_buf, int BUF_SIZE){

   printf("ggggg\n");

   int BUF_TMP_MAX = BUF_SIZE;
// GO to 1st block
if(BUF_SIZE!=0){
while(0 < BUF_SIZE - GET_SIZE(PREV_BLKP(tmp_buf))){// Stops at 0
printf("ggggg2222\n");	
BUF_SIZE-=GET_SIZE(PREV_BLKP(tmp_buf));
printf("BUFFF: %d\n",BUF_SIZE);

tmp_buf = PREV_BLKP (tmp_buf);


}

printf("---BUF PRINTING---\n");
int BUF_COUNT=0;
printf("BUFFF: %d\n",BUF_TMP_MAX); 
printf("BUFFF: %d\n",GET_SIZE(tmp_buf)); 
while(BUF_COUNT+GET_SIZE(tmp_buf) < BUF_TMP_MAX+1){
//	printf("rrSIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(tmp_buf), GET_ID(tmp_buf), GET_ALLOC(tmp_buf));
BUF_COUNT+=GET_SIZE(tmp_buf);		
printf("BUcount: %d\n",BUF_COUNT);	
tmp_buf = NEXT_BLKP(tmp_buf); 
}


printf("---END BUF PRINTING---\n");
}else{
printf("BUF SIZE = 0\n");

}
}
 */
// bp = first block in ram
void* coalesce(void *bp,int RAM_COUNT){


	int RAM_COUNT2=0;
	while(RAM_COUNT2 < RAM_COUNT+1){ // stop it =

		int prev_alloc = GET_ALLOC(HDRP(bp)); // current		
		int next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));


		size_t size = GET_SIZE(HDRP(bp));

		if((!prev_alloc) && (!next_alloc)){
			size+=GET_SIZE(HDRP(NEXT_BLKP(bp)));
			PUT_SIZE(HDRP(bp),size);
			PUT_SIZE(FTRP(NEXT_BLKP(bp)),size);
			// NO change in bp

		} else {
			RAM_COUNT2+=GET_SIZE(bp);
			bp = NEXT_BLKP(bp);
		}
		// RESET RAM ptr
		/*	while(PREV_BLKP(bp)!= NULL){
			bp = PREV_BLKP(bp, RAM_SIZE);
			}
		 */

	}

	return bp; // Last block

}







