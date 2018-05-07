

## Introduction
This application implements defragmentation of emulated memory, using buffer and linkedlist.
Application named `"defrag_tool"` can be compiled by typing make.

# Frameworks
- Application starts by calling the function "`cse320_init(char* filename)"`, in the framework provided, which loads test file into the emulated memory and returns a pointer to the start of it. Then, `"cse320_tmp_buffer_init()"` will return a pointer to a temporary buffer that is used as a temporary storage. Size of the emulated memory is 1024 Bytes and maximum size of the temporary buffer is also 1024 bytes. 

However, initially the temporary buffer is limited to 128 Bytes. The size of the temporary buffer can be increased by calling `"cse320 sbrk(ssize_t size)"` that will increase its size by moving the break point. If the function is called with size equals zero, then it returns current break point.

`"cse320_check(char* filename)"` the emulated memory and `"cse320 free()"` frees temporary buffer and emulated memory.

test_builder allows to construct test files.

# Functions  
`"void* createLL(void *ram)"` creates a linked list and returns its head
`"void bubbleSort(void *start)"` sorts linked list by decreasing ID, Allod-non Alloc, increasing size 
`"void swap(struct block *a, struct block *b)"` swaps data of two nodes a and b
`"void toBUF(void *bp, void *head)"` copies linkedlist to buffer
`"void* coalesce(void *bp, void *head)"` merges two consecutive unallocated blocks having the same ID
`"void* coalesce2(void *bp, void *head)"`  merges two consecutive unallocated blocks having the same ID=0
`"int countSize(void* head)"` size getter function of linkedlist of given head
`"void printLL(struct block* head)"` is a helper function to print linked list of given head
`"void print_BUF(void* tmp_buf)"` is a helper function to print buffer of given head


# Specifications
Each memory block consists of header, footer, payload, and possibly padding. Size of the header and footer is one word (8 Bytes). Each block should be double word aligned. You can find structure of header/footer below:
• Lowest bit represents allocation flag that is 0 when block is free and 1 when block is allocated
• Next two lowest bits represent application ID to distinguish between dif- ferent applications (more details further)
• Rest of the bits represent size of the block in a similar way as was discussed in lecture (recall, that 8 Bytes always have three lowest bits equal to zero)



