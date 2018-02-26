#include "helper.h"
#include "helper2.h"
#define MAXSIZE	1024
void sort(void* bp);

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

	initbuf(tmp_buf);
	//int MAXSIZE = 1024;// bytes
	int RAM_SIZE = 0;
	int BUF_SIZE=0;
	int firstflag=0;
	int secondflag=0;
	int ID = 0;
	void* dptr;

	// Traverse	

	struct Block blocks[64]; // max num of blocks in ram
	printf("-----FROM HERE----\n");

	/*
	   printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   ram = NEXT_BLKP(ram);
	   printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));


	 */
	while(RAM_SIZE < MAXSIZE){

		if(GET_ID(ram)!=0){

			printf("!!!HH!!!!!\n");
			memmove(tmp_buf, ram , GET_SIZE(ram));
			sort(tmp_buf);		

			ram = NEXT_BLKP(ram);
			RAM_SIZE+=GET_SIZE(ram);

			tmp_buf = NEXT_BLKP(tmp_buf);
			BUF_SIZE+=GET_SIZE(tmp_buf);


		}
		else{
			while( GET_SIZE(ram)==0){
				ram = ram + 4; //4 bytes
				RAM_SIZE+=4;
				//printf("HHH\n");
				//printf("currentSIZE: %d \n",currentSIZE);
			}
		}


	}
	printf("-- END of Ram -- \n");

	//		ID++;
	//	}






	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
	}


void sort(void* bp, int BUF_SIZE){//, int size, int ID, int flag){
	// only 1 element
	int ID = GET_ID(bp);

	if(GET_ID(NEXT_BLKP(bp))==0){
		printf("END OF THE BUFF\n");

	} else {
		
while( (PREV_BLKP(bp)!= NULL) && (GET_ID(PREV_BLKP(bp)) > GET_ID(bp)) ){
			SWAP();
		}	

		while( (PREV_BLKP(bp)!= NULL) && (GET_ID(PREV_BLKP(bp)) == GET_ID(bp)) && ((GET_ALLOC(PREV_BLKP(bp)) == 0) && (GET_ALLOC(bp)== 1)) ){
			SWAP();
		}

		while( (PREV_BLKP(bp)!= NULL) && (GET_ID(PREV_BLKP(bp)) == GET_ID(bp)) && (GET_ALLOC(PREV_BLKP(bp)) == GET_ALLOC(bp)) && (GET_SIZE(PREV_BLKP(bp)) > GET_SIZE(bp)) ){
			SWAP(); 
		}
	}

}






