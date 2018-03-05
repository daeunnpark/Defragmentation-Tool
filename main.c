#include "helper.h"
#include "helper2.h"
#include "errno.h"
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

void* createLL(void *ram);
void swap(struct block *a, struct block *b);
void bubbleSort(void *start);
void* coalesce(void *bp,void *head);

void toBUF(void *bp, void *head);

void print_BUF(void* tmp_buf);
void printLL(struct block *head);

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

	if(ram==NULL){
		printf("INIT_ERROR\n");
		return errno;
	}
	struct block* LLhead= NULL;

//	print_BUF(ram);


	// Create LinkedList
	LLhead = createLL(ram);

//	printLL(LLhead);

	
	   if(countSize(LLhead)+16>MAXSIZE){
	   printf("SBRK_ERROR\n");
	   errno = ENOMEM;
	   return errno;	
	   }
	 

	// Sork LL
	bubbleSort(LLhead);//	printLL(LLhead);
	
// Write LL to tmp_buf	
	toBUF(tmp_buf, LLhead); 

	// Coalesce tmp_buf
	coalesce(tmp_buf, LLhead);
	
//Copy tmp_buf to ram, with last block of size 16
	memcpy(ram,tmp_buf,countSize(LLhead)+16);



// Reset the rest of Ram
	for(int i=countSize(LLhead)+16; i<MAXSIZE-countSize(LLhead)-16;i+=8){
		PUT(ram+i,0);
	}

//	print_BUF(ram);


	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}



// Creates a LL and returns head
void* createLL(void *ram){


	struct block *head = NULL;
	struct block *cursor = NULL;

	int flag = 0;
	int count=0;
	int countsize= 0 ;
	int i=0;
	struct block currentBlock;
	struct block blocks[64]; // max num of blocks in ram
	int nextBlockSize =0;

// Get first non empty
	while(GET(ram)==0){
		ram +=8;
		count+=8;
	}


	// FIND first block non empty, that ID !=0
	if(GET_ID(ram)==1 || GET_ID(ram)==2 || GET_ID(ram)==3){
		//	printf("FIRST BLOCK\n");		
		currentBlock = blocks[i];
		currentBlock.ID = GET_ID(ram);
		currentBlock.size = GET_SIZE(ram);
		currentBlock.flag = GET_ALLOC(ram);
		currentBlock.addr = ram;// addr of ram
		count+=currentBlock.size;
		countsize+=currentBlock.size;
		head = &currentBlock;
		cursor=  &currentBlock;
		i++;

		if(  GET(NEXT_BLKP(ram))!=0){
			nextBlockSize = GET_SIZE(NEXT_BLKP(ram));
		}
		else{

			nextBlockSize=8;

		}
	}	
	while(count+nextBlockSize  < MAXSIZE+1 ){
		if(nextBlockSize!=8){	// Next is not a gap
			if(flag!=1){
				blocks[i].ID = GET_ID(NEXT_BLKP(ram));
				blocks[i].size = GET_SIZE(NEXT_BLKP(ram));
				blocks[i].flag = GET_ALLOC(NEXT_BLKP(ram));
				blocks[i].addr = NEXT_BLKP(ram); // addr of header
			}
			else{//special NEXT_BLKP for gaps
				blocks[i].ID = GET_ID(NEXT_BLKP2(ram));
				blocks[i].size = GET_SIZE(NEXT_BLKP2(ram));
				blocks[i].flag = GET_ALLOC(NEXT_BLKP2(ram));
				blocks[i].addr = NEXT_BLKP2(ram); // addr of header

			}

			//		printf("ID: %d Size: %d Flag: %d \n", blocks[i].ID,  blocks[i].size, blocks[i].flag );  
			(*cursor).next =  &blocks[i];
			cursor= cursor->next;	
			count+=(*cursor).size;
			if(flag!=1){
				ram = NEXT_BLKP(ram);
			}else{
				ram = NEXT_BLKP2(ram);

				flag=0;
			}

			countsize+=(*cursor).size;
			i++;
			//			printf("ID222: %d Size: %d Flag: %d \n", GET_ID(ram),  GET_SIZE(ram), GET_ALLOC(ram) );  


			if(GET(NEXT_BLKP(ram))==0  ){
				nextBlockSize=8;
			}

		} else {

		ram = NEXT_BLKP(ram);
			count+=GET_SIZE(ram);
			if(GET(ram+8)!=0  ){ // = GET(NEXT_BLKP(ram)
				//			printf("always2\n");	
				flag=1;
				nextBlockSize= GET_SIZE(ram+8);

				//				printf("always2\n");

			}else{
				ram +=8;
				count+=8;
				//				printf("always11\n"); 
				nextBlockSize =8;
			}



		}



	}

	(*cursor).next = NULL;// Tail

	printf("lastcount!!!!: %d\n", count);
	return head;
}




// Sorts by decreasing ID, Allod-non Alloc, increasing size
void bubbleSort(void *start) {

	int swapped, i;
	struct block *ptr1;
	struct block *lptr = NULL;

	/* Checking for empty list */
	/*
	   if (ptr1 == NULL){
	   printf("sse\n");	
	   return;
	   }

	 */
	do
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)	{
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
	} while (swapped);
}






// Swap data of two nodes a and b
void swap(struct block *a, struct block *b){
	int tempID = a->ID;
	int tempSize = a->size;
	int tempFlag = a->flag;
	void *tempAddr = a->addr;

	a->ID = b->ID;
	a->size = b->size;
	a->flag = b->flag;
	a->addr = b->addr; 

	b->ID = tempID;
	b->size = tempSize;
	b->flag = tempFlag;
	b->addr = tempAddr;

}




// Write LL to Buf
void toBUF(void *bp, void *head){

	struct block *cursor = head;
	int sbrkflag=0;
	int count2=(*cursor).size;
	void* temp=NULL;
	/*
	   if(countSize(head)+16>MAXSIZE){
	   errno=ENOMEM;
	   printf("SBRK_ERROR\n");
	   return ENOMEM;	
	   }

	 */
	while(cursor!=NULL){

		count2+=(*cursor).size;
		if(count2>MAXSIZE2 || sbrkflag==1){
			if(sbrkflag==0) { // first time 
				sbrkflag=1;
				temp = cse320_sbrk(count2-MAXSIZE2);
				if(temp==NULL){
					printf("SBRK_ERROR\n");
					//	printf("----!!!!!____");
					//	perror(": ");
					exit(errno);

				}else{
					//	printf("FIRST"); 
					//	printf("ID: %d FLAG: %d SIZE:  %d\n", (*cursor).ID,(*cursor).flag, (*cursor).size);

				}


			} else { // NOT FIRST TIME
				//	printf("keeps alloc");			

				//	printf("ID: %d FLAG: %d SIZE:  %d\n", (*cursor).ID,(*cursor).flag, (*cursor).size);

				temp = cse320_sbrk((*cursor).size);
			}	
		}


		memcpy(bp,(*cursor).addr, (*cursor).size);
		bp = NEXT_BLKP(bp);

		cursor = cursor->next;
	}	// ADD LAST BLOCK
	PUT_SIZE(HDRP(bp),16);
	PUT_SIZE(FTRP(bp),16);
	PUT_ID(HDRP(bp),0);
	PUT_ID(FTRP(bp),0);
	PUT_ALLOC(HDRP(bp),0);
	PUT_ALLOC(FTRP(bp),0);
}







// Merges 2 consecutive unallocated blocks having = ID
void* coalesce(void *bp, void *head){
	int size=0;
	struct block* cursor = head;
	// cursor not null

	while(cursor->next !=NULL){
		if( (cursor->ID == cursor->next->ID) && cursor->flag ==0 && cursor->next->flag == 0){
			size=GET_SIZE(HDRP(bp)) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
			//	printf("coal: %d %d %d\n",GET_SIZE(HDRP(bp)), GET_SIZE(HDRP(NEXT_BLKP(bp))), size);  
			//	printf("During coal: %d %d %d %d\n",GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(bp)), GET_SIZE(HDRP(NEXT_BLKP(bp))),GET_SIZE(FTRP(NEXT_BLKP(bp))) );

			PUT_SIZE(FTRP(NEXT_BLKP(bp)),size);
			PUT_SIZE(HDRP(bp),size);

			//	printf("AFTEr coal: %d %d\n", GET_SIZE(HDRP(bp)), GET_SIZE(FTRP(NEXT_BLKP(bp)) ));
		} else {
			bp = NEXT_BLKP(bp);
		}


		cursor = cursor->next;
	}	

}



int countSize(void* head){
	struct block* cursor = head;
	int count = 0;//cursor->size;
	while(cursor!=NULL){
		//printf("count: %d\n ",cursor->size);

		count+=cursor->size;

		cursor = cursor->next;

	}
	return count;

}





// HELPERS
void printLL(struct block* head){
	struct block* cursor = head;

	while(cursor!=NULL)
	{
		//		printf("OLZZZ\n");
		printf("ID:%d FLAG:%d SIZE:%d ADDR:%p\n", cursor->ID, cursor->flag, cursor-> size, cursor->addr);
		cursor = cursor->next;
	}

}

void print_BUF(void* tmp_buf){
	int count=0;
	printf("---START BUF PRINTING---\n");	
	void* tmp = tmp_buf;



	while(GET(tmp)==0){
		printf("dddd\n");
		tmp +=8;
		count+=8;
	}

	//	printf("COUNT2: %d \n ", count); 
	//	printf("COUNT3: %d \n ",GET_SIZE(tmp) );  
	count+=GET_SIZE(tmp); 
	count+=GET_SIZE(tmp); 
	//	printf("COUNT4: %d \n ", count);
	while(GET_SIZE(tmp)!=-1 && count < MAXSIZE){	
		//	while(GET_ID(tmp)==1 ||GET_ID(tmp)==2 ||GET_ID(tmp)==3)

		if(GET(tmp)==0){
			//			printf("Printing gAP \n");
			tmp+=8;
			count+=8;	
		} else {

			printf("ID : %d ALLOC : %d SIZE: %d\n", GET_ID(tmp), GET_ALLOC(tmp), GET_SIZE(tmp));
			tmp+=GET_SIZE(tmp); 
			count+=GET_SIZE(tmp);
		}
	}

	printf("---END BUF PRINTING---\n");

}

