//Qing Yu (sabrina), 01, Zhang Cai (zcai), 01
/* check for coalesce free space */
#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
    assert(Mem_Init(4096) == 0);
    void * ptr[2];

    ptr[0] = Mem_Alloc(600);
    assert(ptr[0] != NULL);

    ptr[1] = Mem_Alloc(600);
    assert(ptr[1] != NULL);
    assert(Mem_Free(ptr[1]) == 0);
   
    ptr[2] = Mem_Alloc(1800);
	assert(ptr[2] != NULL);
	assert(Mem_Free(NULL) == -1); 
	
	assert(Mem_Free((void *)0xadadad) == -1);
	exit(0);
}
