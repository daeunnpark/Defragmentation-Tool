#include "helper.h"
#include "helper2.h"
#define MAXSIZE	1024
#define TEMP_RAM_SIZE 128


void sort(void* bp, int BUF_SIZE);
void print_RAM(void* bp, int RAM_SIZE);
void print_BUF(void* bp, int BUF_SIZE);
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

	int RAM_SIZE = 0;
	int BUF_SIZE=0;
	ssize_t INCR_BUF_SIZE=0;
	int MAX_BUF_SIZE = 128;
	int firstflag=0;
	int secondflag=0;
	int ID = 0;
	void* dptr;

	// Traverse	

	printf("-----FROM HERE----\n");
	print_RAM(ram,RAM_SIZE);
	/*
	   printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   ram = NEXT_BLKP(ram);
	   printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));


	 */


	while(RAM_SIZE + GET_SIZE(ram) < MAXSIZE+1){

		if(GET_ID(ram)==1 || GET_ID(ram)==2 || GET_ID(ram)==3){

			printf("!!!HH!!!!!\n");


			if(BUF_SIZE + GET_SIZE(ram)+1 >  MAX_BUF_SIZE){
				if(MAX_BUF_SIZE < MAXSIZE+1){			
					ssize_t size = BUF_SIZE+GET_SIZE(ram)+1 - MAX_BUF_SIZE;
					INCR_BUF_SIZE+=size;

					if(cse320_sbrk(size)==NULL){
						//	printf(errno);
						perror("");					
						exit(errno);
					}

					MAX_BUF_SIZE+=size;
				}printf("Print error\n");

			}				printf("Print error\n"); 
			memmove(tmp_buf, ram , GET_SIZE(ram));
			sort(tmp_buf,BUF_SIZE);		
			print_BUF(tmp_buf,BUF_SIZE);


			//	RAM_SIZE+=GET_SIZE(ram);
			ram = NEXT_BLKP_RAM(ram, &RAM_SIZE);

			//	BUF_SIZE+=GET_SIZE(tmp_buf);
			tmp_buf = NEXT_BLKP_BUF(tmp_buf, &BUF_SIZE, MAX_BUF_SIZE);



		} else {

			if ( RAM_SIZE+4 < MAXSIZE+1 ){
				ram += 4; //4 bytes
				RAM_SIZE+=4;
			}

			else{

				printf("-- END of Ram222 -- \n");
				break;
			}
		}



	}
	printf("-- END of Ram -- \n");
	// Not enough mem in Ram for last block

	if(RAM_SIZE+16< MAXSIZE+1){
		errno=ENOMEM;
		printf("SBRK_ERROR\n");

		exit(errno);
	}

	//int saveSIZE= RAM_SIZE;
	int finalsize = BUF_SIZE+INCR_BUF_SIZE;




	while(PREV_BLKP_C(ram,&RAM_SIZE)){
		ram = PREV_BLKP(ram, &RAM_SIZE);
	}

	while(PREV_BLKP_C(tmp_buf,&BUF_SIZE)){
		tmp_buf = PREV_BLKP (tmp_buf,&BUF_SIZE);
	}



	memcpy(ram, tmp_buf,finalsize);		//LAST BLOCK

	coalesce(ram,RAM_SIZE);

	PUT_SIZE(HDRP(ram),16);
	PUT_SIZE(FTRP(ram),16);
	PUT_ID(HDRP(ram),0);
	PUT_ID(FTRP(ram),0);
	PUT_ALLOC(HDRP(ram),0);
	PUT_ALLOC(FTRP(ram),0);



	while(PREV_BLKP_C(ram,&RAM_SIZE)!= '\0'){
		ram = PREV_BLKP(ram, &RAM_SIZE);
	}



	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}


void sort(void *bp, int BUF_SIZE){
	// only 1 element
	int ID = GET_ID(bp);

	while( (PREV_BLKP_C(bp,&BUF_SIZE)!= '\0') && ( GET_ID( PREV_BLKP_C(bp,&BUF_SIZE) ) > GET_ID(bp)) ){

		SWAP( PREV_BLKP_C(bp,&BUF_SIZE) ,bp, &BUF_SIZE);     
	}	

	while( (PREV_BLKP_C(bp,&BUF_SIZE)!= '\0') && (GET_ID(PREV_BLKP_C(bp,&BUF_SIZE)) == GET_ID(bp)) && ((GET_ALLOC(PREV_BLKP_C(bp,&BUF_SIZE)) == 0) && (GET_ALLOC(bp)== 1)) ){
		SWAP(PREV_BLKP_C(bp,&BUF_SIZE),bp, &BUF_SIZE);

	}

	while( (PREV_BLKP_C(bp,&BUF_SIZE)!= '\0') && (GET_ID(PREV_BLKP_C(bp,&BUF_SIZE)) == GET_ID(bp)) && (GET_ALLOC(PREV_BLKP_C(bp,&BUF_SIZE)) == GET_ALLOC(bp)) && (GET_SIZE(PREV_BLKP_C(bp,&BUF_SIZE)) > GET_SIZE(bp)) ){
		SWAP(PREV_BLKP_C(bp,&BUF_SIZE),bp,  &BUF_SIZE);     		
	}

	printf("SORTED\n");
}





void print_RAM(void* bp, int RAM_SIZE){ 
	printf("---RAM PRINTING---\n");
//for 1st block

RAM_SIZE = 0;
	while(bp!=NULL &&( RAM_SIZE + GET_SIZE(bp) < MAXSIZE+1)){

		if(GET_ID(bp)==1 || GET_ID(bp)==2 || GET_ID(bp)==3){

			printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(bp), GET_ID(bp), GET_ALLOC(bp));
			printf("11RAM SIZE = %d\n", RAM_SIZE);

			
	RAM_SIZE+=GET_SIZE(bp);

			bp = NEXT_BLKP_RAM(bp, &RAM_SIZE);
			printf("2RAM SIZE = %d\n", RAM_SIZE);   

printf("SIZE: %d\n",GET_SIZE(bp));
		} else {
			printf("HEEE\n");
			if ( RAM_SIZE+4 < MAXSIZE+1 ){
				bp += 4; //4 bytes
				RAM_SIZE+=4;
			}else {

				printf("-- END of Ram333 -- \n");  
				break;

			}

		}
	}

	printf("---END RAM PRINTING---");  


}


void print_BUF(void* bp, int BUF_SIZE){

	while( PREV_BLKP_C(bp,&BUF_SIZE)     != '\0'){
		bp = PREV_BLKP(bp,&BUF_SIZE);
	}

	printf("---BUF PRINTING---");

	while(bp!='\0'){
		printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(bp), GET_ID(bp), GET_ALLOC(bp));
		bp = NEXT_BLKP_RAM((bp),&BUF_SIZE); 
	}


	printf("---END BUF PRINTING---");

}

// bp = first block in ram
void* coalesce(void *bp,int RAM_SIZE){

	// Start at 2nd block to avoid 1st with prev
	bp = NEXT_BLKP_RAM((bp),&RAM_SIZE);


	while(HDRP(NEXT_BLKP_C(bp,&RAM_SIZE))!= '\0'){
		int prev_alloc = GET_ALLOC(FTRP(PREV_BLKP_C(bp,&RAM_SIZE)));
		int next_alloc = GET_ALLOC(HDRP(NEXT_BLKP_C(bp,&RAM_SIZE)));
		size_t size = GET_SIZE(HDRP(bp));



		if(prev_alloc && next_alloc){ // 1-- --1
			return bp;

		} else if(prev_alloc && !next_alloc){ // 1-- --0
			size+=GET_SIZE(HDRP(NEXT_BLKP_C(bp,&RAM_SIZE)));

			PUT_SIZE(HDRP(bp),size); 
			PUT_SIZE(FTRP(NEXT_BLKP_C(bp, &RAM_SIZE)), size);  


		} else if(!prev_alloc && next_alloc){ // 0-- --1
			size+=GET_SIZE(FTRP(PREV_BLKP_C(bp, &RAM_SIZE)));

			PUT_SIZE(FTRP(bp), size);  
			PUT_SIZE(HDRP(PREV_BLKP_C(bp, &RAM_SIZE)),size); 

			bp= PREV_BLKP(bp, &RAM_SIZE);



		} else { // 0-- --0 
			size+=GET_SIZE(FTRP(PREV_BLKP_C(bp,&RAM_SIZE)))+ GET_SIZE(HDRP(NEXT_BLKP_C(bp,&RAM_SIZE)));

			PUT_SIZE(HDRP(PREV_BLKP_C(bp, &RAM_SIZE)),size);
			PUT_SIZE(FTRP(NEXT_BLKP_C(bp,&RAM_SIZE)), size); 

			bp= PREV_BLKP(bp,&RAM_SIZE);
		}
		bp = NEXT_BLKP_RAM(bp, &RAM_SIZE);

	}
	// RESET RAM ptr
	/*	while(PREV_BLKP(bp)!= NULL){
		bp = PREV_BLKP(bp, RAM_SIZE);
		}
	 */


	return bp;
}






