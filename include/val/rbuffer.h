#ifndef RILL_VAL_RBUFFER
#define RILL_VAL_RBUFFER

#define RILL_VAL_RBUFFER_GROWTHCOEFF 2.0

#include <stddef.h>
#include <stdint.h>

typedef struct rbuffer {
    RSlab slab;
    size_t len;
    size_t refcount;
} RBuffer;

RBuffer * rbuffer_create ( size_t init_cap );
RBuffer * rbuffer_clone ( RBuffer * buffer );
void rbuffer_destroy ( RBuffer * buffer );

size_t rbuffer_len ( RBuffer * buffer );
void rbuffer_lease ( RBuffer * buffer );
void rbuffer_release ( RBuffer * buffer );
int rbuffer_reserve ( RBuffer * buffer, size_t new_cap );
int rbuffer_compact ( RBuffer * buffer );
uint8_t * rbuffer_get ( RBuffer * buffer );

int rbuffer_cpy ( RBuffer * dst, RBuffer * src );
int rbuffer_cat ( RBuffer * dst, RBuffer * src );
int rbuffer_cmp ( RBuffer * dst, RBuffer * src );

int rbuffer_cpyc ( RBuffer * buffer, char * cstr );
int rbuffer_catc ( RBuffer * buffer, char * cstr );
int rbuffer_cmpc ( RBuffer * buffer, char * cstr );

int rbuffer_cpymem ( RBuffer * buffer, uint8_t bytes, size_t bytes_len );
int rbuffer_catmem ( RBuffer * buffer, uint8_t bytes, size_t bytes_len );
int rbuffer_cmpmem ( RBuffer * buffer, uint8_t bytes, size_t bytes_len );

int rbuffer_clear ( RBuffer * buffer );

#endif
