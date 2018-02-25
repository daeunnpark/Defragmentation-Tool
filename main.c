#include "helper.h"
#include "helper2.h"

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

	/*
	   struct block{ 
	 *int footer; // 8 bytes = 64 bits
	 *int header; // 8 bytes
	 int allocFlag // 1 bits
	 int ID; // 2 bits
	 int size; // 61 bits

	 }

	 */

	initbuf(tmp_buf);
	int MAXSIZE = 1024;// bytes
	int currentSIZE = 0;
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
	


void* temp = SWAP(PREV_BLKP(ram), ram);

	printf("AFSWAP SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(temp), GET_ID(temp), GET_ALLOC(temp));
	ram = NEXT_BLKP(ram);
	printf("NEXT SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
	

*/
int index=0;
//	while(ID<4){
		while(currentSIZE <MAXSIZE){

	/*		if(GET_SIZE(ram)!=0){
				printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
				//PUT_SIZE(ram, 64);
				printf("22SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));

*/

if(GET_ID(ram)!=0){
dptr = ram;

blocks[index].addr = dptr;
printf("!!!HH!!!!!\n");
memmove(tmp_buf,&blocks[index], sizeof(blocks[index]));


/*		if(GET_ID(ram)==ID){
					firstflag = 1;
					PUT_SIZE(tmp_buf,GET_SIZE(ram)); 
					PUT_ID(tmp_buf,ID);
					PUT_ALLOC(tmp_buf, GET_ALLOC(ram));
					tmp_buf = NEXT_BLKP(tmp_buf);			
					sort(tmp_buf);

				}

*/



		
		currentSIZE +=GET_SIZE(ram);
 printf("%p\n", ram);   
				ram = NEXT_BLKP(ram);
tmp_buf = tmp_buf +  sizeof(blocks[index-1]);
printf("%p\n", ram);
 printf("THIS at index %d : %p\n",index, blocks[index].addr);
index++;

			}
			else{
				while( GET_SIZE(ram)==0){
					ram = ram + 4; //4 bytes
					currentSIZE+=4;
					//printf("HHH\n");
					//printf("currentSIZE: %d \n",currentSIZE);
				}
			}


		}
		printf("-- END of Ram -- \n");
		currentSIZE=0;
printf("%p\n",blocks[0].addr);
 printf("%p\n",blocks[1].addr); 

//		ID++;
//	}






	/*
	 * Do not modify code below.
	 */
	cse320_check();
	cse320_free();
	return ret;
}
void sort(void* bp){//, int size, int ID, int flag){
	// only 1 element
int ID = GET_ID(bp);

	if(GET_ID(NEXT_BLKP(bp))==0){
		printf("END OF THE BUFF\n");

	} else {
		void* first = FIRST_ID_BLKP(bp, ID);

		//		while(GET_ID(NEXT_BLKP(first)==ID){
		if(GET_ALLOC(PREV_BLKP(bp)) == GET_ALLOC(bp)){
			while(GET_SIZE(PREV_BLKP(bp)) > GET_SIZE(bp)){ // Checking size
				SWAP(PREV_BLKP(bp),bp);
				if(GET_ALLOC(PREV_BLKP(bp)) != GET_ALLOC(bp)){
					break;

				}
			}


		} else { // 0-1 or 1-0
			while( GET_ALLOC(PREV_BLKP(bp))==0 && GET_ALLOC(bp)==1){ // 0-1
				//Sort Alloc
				SWAP(PREV_BLKP(bp),bp);



			}

			while( GET_ALLOC(PREV_BLKP(bp))==1 && GET_ALLOC(bp)==1){ // 0-1
				while(GET_SIZE(PREV_BLKP(bp))> GET_SIZE(bp)){
					SWAP(PREV_BLKP(bp),bp);

				}

			}
		}



	}
}	/*
	   if(GET_ID(ram)<GET_ID(NEXT_BLKP(ram))){

// OK

}
else if (GET_ID(ram)>GET_ID(NEXT_BLKP(ram))) {
// Sort ID

}
else { //ram.ID == NEXT_BLKP(ram).ID
if(GET_ALLOC(ram) == GET_ALLOC(NEXT_BLKP(ram))){
if(GET_SIZE(ram) > GET_SIZE(NEXT_BLKP(ram))){ // Checking size
//Sort Size
}

} else { // 0-1 or 1-0
if(GET_ALLOC(ram)==0){ // 0-1
//Sort Alloc

}



}


}



	 */


