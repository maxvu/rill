#include "rmem.h"

void * rmem_alloc ( size_t len ) {
    return malloc( len );
}

void rmem_free ( void * data ) {
    free( data );
}
