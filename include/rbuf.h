#ifndef RILL_RBUF
#define RILL_RBUF

void * rbuf_create ( size_t siz );
void * rbuf_resize ( void * buf, size_t siz, size_t save );
void * rbuf_destroy ( void * buf );

#endif
