#include "helper.h"
#include "helper2.h"
#define MAXSIZE	1024
#define MAXSIZE2 128


struct block {
	void *addr; // addr of header
	int size;
	int ID;
	int flag;
	struct block *next;
	struct block *prev;

};

//void* sort(void* bp, int BUF_SIZE);
void bubbleSort(void *start);
void print_RAM(void* bp, int RAM_COUNT);
void* coalesce(void *bp,void *head);
void printLL(struct block *head);
void* createLL(void *ram);
void swap(struct block *a, struct block *b);
void toBUF(void *bp, void *head);
void print_BUF(void* tmp_buf);
int countSize(void* head);

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
	void* BUF_cursor;// = tmp_buf;
	struct block* LLhead;
	int count=0;

	printf("-----FROM HERE----\n");
	//	print_RAM(ram,160);
	/*
	   printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   ram = NEXT_BLKP(ram);
	   printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	   truct block* cursor = head;

	 */

	// Initialize cursor
	RAM_cursor = ram;
	BUF_cursor = tmp_buf;

	printf("1   %p\n", tmp_buf);  
	printf("2   %p\n", BUF_cursor);
	LLhead = createLL(ram);
	//	printLL(LLhead);

	//	printf("NEW COUNT: %d\n",countSize(LLhead));




	printf("L1   %p\n", LLhead);

	count = countSize(LLhead);

	printf("L2   %p\n", LLhead);  

	/*
	   if(MAXSIZE-16>count ||MAXSIZE-16==count){
	   printf("PPP\n");

	   if(count>MAXSIZE2){
	   if(cse320_sbrk(count-MAXSIZE2)==NULL){
	   printf("SBRK_ERROR\n");
	   printf("----!!!!!____");
	   perror(": ");
	   exit(errno);

	   }else{
	   printf("ALLOCated with\n");


	   }

	   }
	   } else {
	   errno=ENOMEM;
	   printf("SBRK_ERROR\n");
	   exit(errno);

	   }
	 */
	bubbleSort(LLhead);
	printLL(LLhead);
	printf("0   %p\n", tmp_buf);
	toBUF(BUF_cursor, LLhead); // update bp to last

	printf("4   %p\n", tmp_buf); 
	printf("3   %p\n", BUF_cursor);

	print_BUF(tmp_buf);
	//print_BUF(BUF_cursor);

	coalesce(tmp_buf, LLhead);
	print_BUF(tmp_buf);

	printf("5   %p\n", BUF_cursor);  
	printf("DIF: %d\n", tmp_buf - BUF_cursor);


memcpy(ram,tmp_buf,count+16);

	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}




void bubbleSort(void *start)
{
	int swapped, i;
	struct block *ptr1;
	struct block *lptr = NULL;

	/* Checking for empty list */

	if (ptr1 == NULL){
		return;
	}
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (ptr1->ID > ptr1->next->ID)
			{ 
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			else if((ptr1->ID ==  ptr1->next->ID) && ptr1->flag == 0 && ptr1->next->flag==1 ){
				swap(ptr1,ptr1->next);
				swapped=1;

			}

			else if((ptr1->ID == ptr1->next->ID) && ptr1->flag==1 && ptr1->next->flag==0 &&(ptr1->size > ptr1->next->size)){
				swap(ptr1, ptr1->next);
				swapped=1;

			}

			ptr1 = ptr1->next;

		}
		lptr = ptr1;
	}
	while (swapped);
}

/* function to swap data of two nodes a and b*/
void swap(struct block *a, struct block *b){
	int tempID = a->ID;
	int tempSize = a->size;
	int tempFlag = a->flag;
	void *tempAddr = a->addr;

	a->ID = b->ID;
	a->size = b->size;
	a->flag = b->flag;
	a->addr = b->addr; //?

	b->ID = tempID;
	b->size = tempSize;
	b->flag = tempFlag;
	b->addr = tempAddr;

}


void toBUF(void *bp, void *head){
	printf("gggrr\n");
	int sbrkflag=0;
	struct block *cursor = head;
	int count = countSize(head);

	if(count+16>MAXSIZE){
		errno=ENOMEM;
		printf("SBRK_ERROR\n");
		exit(errno);
	}

	int count2=(*cursor).size;

	void* temp;

	while(cursor!=NULL){
		printf("HOW MANY\n");

		count2+=(*cursor).size;
		if(count2>MAXSIZE2 || sbrkflag==1){
			if(sbrkflag==0) { // first time 
				sbrkflag=1;
				temp = cse320_sbrk(count2-MAXSIZE2);
				if(temp==NULL){
					printf("SBRK_ERROR\n");
					printf("----!!!!!____");
					perror(": ");
					exit(errno);

				}else{
					//	bp =temp-;
					printf("FIRST"); 
					printf("ID: %d FLAG: %d SIZE:  %d\n", (*cursor).ID,(*cursor).flag, (*cursor).size);

				}


			}
			else{
				printf("keeps alloc");			

				printf("ID: %d FLAG: %d SIZE:  %d\n", (*cursor).ID,(*cursor).flag, (*cursor).size);

				temp = cse320_sbrk((*cursor).size);
			//	bp =temp;	
			}	
		}
	

printf("WHERE1\n");

	memcpy(bp,(*cursor).addr, (*cursor).size);
printf("WHERE2\n");  	
	bp = NEXT_BLKP(bp);

		cursor = cursor->next;
printf("WHERE3\n");  
	//	count2+=(*cursor).size;
		printf("ggg\n");
	}

	PUT_SIZE(HDRP(bp),16);
	PUT_SIZE(FTRP(bp),16);
	PUT_ID(HDRP(bp),0);
	PUT_ID(FTRP(bp),0);
	PUT_ALLOC(HDRP(bp),0);
	PUT_ALLOC(FTRP(bp),0);
	/*
	   } else {
	   errno=ENOMEM;
	   printf("SBRK_ERROR\n");
	   exit(errno);

	   }

	 */
	}




void* coalesce(void *bp, void *head){
	int size=0;
	struct block* cursor = head;
	// cursor not null

	while(cursor->next !=NULL){
printf("gg\n");
		if( (cursor->ID == cursor->next->ID) && cursor->flag ==0 && cursor->next->flag == 0){
			size=GET_SIZE(HDRP(bp)) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
printf("coal: %d %d %d\n",GET_SIZE(HDRP(bp)), GET_SIZE(HDRP(NEXT_BLKP(bp))), size);  
printf("During coal: %d %d %d %d\n",GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), GET_SIZE(HDRP(NEXT_BLKP(bp))),GET_SIZE(FTRP(NEXT_BLKP(bp))) );
printf ("SIZE: %d\n", size);

			PUT_SIZE(FTRP(NEXT_BLKP(bp)),size);
PUT_SIZE(HDRP(bp),size);





printf("AFTEr coal: %d %d\n", GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(NEXT_BLKP(bp)) ));
		}else{
			bp = NEXT_BLKP(bp);
		}


		cursor = cursor->next;
	}	
/*	while(cursor->next !=NULL){
printf("gg\n");
		if( (cursor->ID == cursor->next->ID) && cursor->flag ==0 && cursor->next->flag == 0){
			size=GET_SIZE(HDRP(bp)) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
printf("coal: %d %d %d\n",GET_SIZE(HDRP(bp)), GET_SIZE(HDRP(NEXT_BLKP(bp))), size);  
			PUT_SIZE(HDRP(bp),size);
			PUT_SIZE(FTRP(NEXT_BLKP(bp)),size);

		}else{
			bp = NEXT_BLKP(bp);
		}


		cursor = cursor->next;
	}	*/	
}




// Creates a LL and returns head
void* createLL(void *ram){


	struct block *head = NULL;
	struct block *cursor = NULL;

	int count=0;
	int countsize= 0 ;
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
		countsize+=currentBlock->size;
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
				countsize+=(*cursor).size;

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

	printf("COUNT SIZE: %d \n", countsize);
	/*
	// enough space
	if(MAXSIZE-16>countsize ||MAXSIZE-16==countsize){
	if(countsize>MAXSIZE2){
	if(cse320_sbrk(countsize-MAXSIZE2)==NULL){
	printf("SBRK_ERROR\n");
	printf("----!!!!!____");
	perror(": ");
	exit(errno);

	}else{
	printf("ALLOC");


	}

	}
	}
	else{
	errno=ENOMEM;
	printf("SBRK_ERROR\n");
	exit(errno);

	}
	//return head;
	 */
	return head;
}



void printLL(struct block* head){
	struct block* cursor = head;

	while(cursor!=NULL){
		printf("ID:%d FLAG:%d SIZE:%d ADDR:%p\n", cursor->ID, cursor->flag, cursor-> size, cursor->addr);
		cursor = cursor->next;
	}

}

void print_BUF(void* tmp_buf){

	printf("---START BUF PRINTING---\n");	
	void* tmp = tmp_buf;
	while(GET_SIZE(tmp)!=0){	
		//	while(GET_ID(tmp)==1 ||GET_ID(tmp)==2 ||GET_ID(tmp)==3)
		printf("ID : %d ALLOC : %d SIZE: %d\n", GET_ID(tmp), GET_ALLOC(tmp), GET_SIZE(tmp));

		tmp+=GET_SIZE(tmp);
	}

	printf("---END BUF PRINTING---\n");

}

int countSize(void* head){
	struct block* cursor = head;
	int count = cursor->size;
	while(cursor->next!=NULL){

		cursor = cursor->next;
		count+=cursor->size;
	}
	return count;

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
