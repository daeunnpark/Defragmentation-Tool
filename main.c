#include "helper.h"
#include "helper2.h"



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
	// Traverse	

	printf("-----FROM HERE----\n");
	while(currentSIZE <MAXSIZE){

		if(GET_SIZE(ram)!=0){
			printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
			//PUT_SIZE(ram, 64);
			printf("22SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));

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










		currentSIZE +=GET_SIZE(ram);
		ram = NEXT_BLKP(ram);

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







/*
 * Do not modify code below.
 */
cse320_check();
cse320_free();
return ret;
}
