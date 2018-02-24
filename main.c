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

int MAXSIZE = 1024;// bytes
int currentSIZE = 0;

int size1 = GET_SIZE(ram);
int ID = GET_ID(ram);
int allogc = GET_ALLOC(ram);




while(currentSIZE <MAXSIZE){

while( GET_SIZE(ram)==0){

ram = ram + 4; //4 bytes
currentSIZE+=4;
printf("HH\n");

}
//ram = NEXT_BLKP(ram);
//ram =ram+4;


printf("-----FROM HERE----\n");
printf("SIZE: %d ID : %d ALLOC : %d \n", GET_SIZE(ram), GET_ID(ram), GET_ALLOC(ram));
currentSIZE +=GET_SIZE(ram);
printf("%d\n", currentSIZE);
ram = NEXT_BLKP(ram);

}
printf("--END printing-- \n");

    /*
     * Do not modify code below.
     */
    cse320_check();
    cse320_free();
    return ret;
}
