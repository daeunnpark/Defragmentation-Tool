#include "helper.h"
#include "helper2.h"
#define MAXSIZE	1024
#define TEMP_RAM_SIZE 128


struct block {
	void *addr; // addr of header
	int size;
	int ID;
	int flag;
	struct block *next;
	struct block *prev;

};

void* sort(void* bp, int BUF_SIZE);
void print_RAM(void* bp, int RAM_COUNT);
void* coalesce(void *bp,int RAM_SIZE);
void printLL(struct block *head);
void* createLL(void *ram);


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



	void* RAM_cursor;
	void* BUF_cursor;
	struct block* LLhead;


	printf("-----FROM HERE----\n");
	//	print_RAM(ram,160);
	/*
	   printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   ram = NEXT_BLKP(ram);
	   printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));


	 */

	// Initialize cursor
	RAM_cursor = ram;
	BUF_cursor = tmp_buf;

	LLhead = createLL(ram);
	printLL(LLhead);





	/*
	   if(RAM_COUNT+16 < MAXSIZE+1){
	   errno=ENOMEM;
	   printf("SBRK_ERROR\n");

	   exit(errno);
	   }

	 */


	// GET FIRST BLOCK
	/*
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

	 */
	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}


void* sort(void *bp, int BUF_COUNT){
	// only 1 element
	int BUF_COUNT2 = BUF_COUNT;
	int totalSIZE=0;
	int BUF_SIZE = BUF_COUNT+GET_SIZE(bp);

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
		printf("BUF COUNT IN SORT: %d\n", BUF_COUNT);
		printf("totalSIZE IN SORT: %d\n", totalSIZE);
		printf("BUF COUNT IN SORT: %d\n", GET_SIZE(bp));  
		//Last block
		//printf("BUF COUNT MUST BE 0: %d\n",BUF_COUNT);
		while(BUF_COUNT+ GET_SIZE(bp)<totalSIZE){
			printf("GG\n");
			BUF_COUNT+= GET_SIZE(bp);
			bp = NEXT_BLKP(bp);

		}

	}

	return bp; // Header of Last block in sorted list

}




// bp = first block of ram
void print_RAM(void* bp,int RAM_SIZE){ 
	printf("---PRINTING---\n");
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
			if ( RAM_COUNT2+8 < RAM_SIZE+1 ){
				bp += 8; //4 bytes
				RAM_COUNT2+=8;
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
if(BUF_SIZE!=0):{
while(0 < BUF_SIw
ZE - GET_SIZE(PREV_BLKP(tmp_buf))){// Stops at 0
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


// Creates a LL and returns head
void* createLL(void *ram){
	printf("TTT\n");
	struct block *head = NULL;
	struct block *cursor = NULL;

	int count=0;
	struct block *currentBlock = NULL;
	//	currentBlock->prev=NULL;
	//	currentBlock->next=NULL;


	// NOT empty
	if(GET_ID(ram)==1 || GET_ID(ram)==2 || GET_ID(ram)==3){
		currentBlock = malloc(sizeof(struct block));
		currentBlock->ID = GET_ID(ram);
		currentBlock->size = GET_SIZE(ram);
		currentBlock->flag = GET_ALLOC(ram);
		currentBlock->addr = ram;// addr of ram
		count+=currentBlock->size;

		head = currentBlock;
		cursor = currentBlock;

		while(count+ GET_SIZE(NEXT_BLKP(ram)) < MAXSIZE+1){



			if(GET_ID(NEXT_BLKP(ram))==1 || GET_ID(NEXT_BLKP(ram))==2 || GET_ID(NEXT_BLKP(ram))==3){   
				struct block *nextBlock = malloc(sizeof(struct block));
				nextBlock->ID = GET_ID(NEXT_BLKP(ram));
				nextBlock->size = GET_SIZE(NEXT_BLKP(ram));
				nextBlock->flag = GET_ALLOC(NEXT_BLKP(ram));
				nextBlock->addr = NEXT_BLKP(ram); // addr of header
				(*cursor).next = nextBlock;
				cursor= cursor->next;	
				count+=(*cursor).size;
				ram = NEXT_BLKP(ram);


			}
			else{
				ram= NEXT_BLKP(ram)+8;
				count+=8; // count is ahead


			}
		}


	} else {
		// Ram empty?
		return NULL;
	}

	(*cursor).next = NULL;// Tail
	return head;


}



void printLL(struct block* head){
	struct block* cursor = head;

	while(cursor!=NULL){
		printf("ID:%d SIZE:%d FLAG:%d ADDR:%p\n", cursor->ID, cursor->size, cursor-> flag, cursor->addr);
		cursor = cursor->next;
	}

}



/*


   printf("-----SBRK-----\n");
   if(cse320_sbrk(size)==NULL){
//	printf(errno);
perror("");					
exit(errno);
}
BUF_COUNT+=GET_SIZE(cursor);
MAX_BUF_SIZE+=size;
}
IZE(NEXT_BLKP(ram)

)

 */
