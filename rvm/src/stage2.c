#include <stdio.h>
#include <stdint.h>

#ifdef RILL_32BIT
    typedef int32_t  ixx_t;
    typedef uint32_t uxx_t;
    typedef float    fxx_t;
#endif

#ifdef RILL_64BIT
    typedef int64_t  ixx_t;
    typedef uint64_t uxx_t;
    typedef double   fxx_t;
#endif

typedef struct rnum {
    rvtag tag;
    uxx_t ref;
    union {
        ixx_t ixx;
        uxx_t uxx;
        fxx_t fxx;
    };
} rnum;

typedef struct rstr {
    rvtag  tag;
    uxx_t  ref;
    uxx_t  len;
    uxx_t  cap;
    char * buf;
} rstr;

typedef struct rvec {
    rvtag  tag;
    uxx_t  ref;
    uxx_t  len;
    uxx_t  cap;
    rval * vls;
} rvec;

typedef struct rmap {
    rtag   tag;
    uxx_t  ref;
    uxx_t  len;
    uxx_t  occ;
    rval * kvp;
} rmap;

int main ( int argc, char ** argv ) {
    printf( "ixx_t: %lu\n", sizeof( ixx_t ) );
    printf( "uxx_t: %lu\n", sizeof( uxx_t ) );
    printf( "fxx_t: %lu\n", sizeof( fxx_t ) );
    printf( "rval: %lu\n", sizeof( rval ) );
    printf( "rtag: %lu\n", sizeof( rtag ) );
    printf( "rnum: %lu\n", sizeof( rnum ) );
    printf( "rstr: %lu\n", sizeof( rstr ) );
    printf( "rvec: %lu\n", sizeof( rvec ) );
    printf( "rmap: %lu\n", sizeof( rmap ) );
    printf( "size_t: %lu\n", sizeof( size_t ) );
    printf( "unsigned int: %lu\n", sizeof( unsigned int ) );
    printf( "int_fast32_t: %lu\n", sizeof( int_fast32_t ) );
    printf( "ok\n" );
    return 0;
}
