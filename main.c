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



int size1 = GET_SIZE(ram);
int ID = GET_ID(ram);
int allogc = GET_ALLOC(ram);


printf("-----FROM HERE----\n");
printf("DATA: %d %d %d \n", size1, ID, allogc);

ram = NEXT_BLKP(ram);

size1 = GET_SIZE(ram);
ID = GET_ID(ram);
allogc = GET_ALLOC(ram);


printf("-----FROM HERE222----\n");
printf("DATA: %d %d %d \n", size1, ID, allogc);


//ram = PREV_BLKP(ram);

size1 = GET_SIZE(ram);
ID = GET_ID(ram);
allogc = GET_ALLOC(ram);


printf("-----FROM HERE33----\n");
printf("DATA: %d %d %d \n", size1, ID, allogc);






    /*
     * Do not modify code below.
     */
    cse320_check();
    cse320_free();
    return ret;
}
