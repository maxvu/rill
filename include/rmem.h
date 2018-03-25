#ifndef RILL_RMEM
#define RILL_RMEM

#include <stddef.h>
#include <stdlib.h>

void * rmem_alloc ( size_t len );
void rmem_free ( void * data );

#endif
