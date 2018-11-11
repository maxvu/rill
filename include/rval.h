#ifndef RILL_RVAL
#define RILL_RVAL

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define RILL_VM_RBUF_MINSIZE 3
#define RILL_VM_RBUF_GROWTHCOEFF 2.0

typedef struct RStr RStr;
typedef struct RVec RVec;
typedef struct RMap RMap;

typedef enum RValType {
    RVT_NIL = 0,
    RVT_UXX = 1,
    RVT_IXX = 2,
    RVT_FXX = 3,
    RVT_STR = 4,
    RVT_VEC = 5,
    RVT_MAP = 10
} RValType;

typedef struct RVal {
    enum RValType type;
    union {
        unsigned long uxx;
        long          ixx;
        double        fxx;
        RStr *        str;
        RVec *        vec;
        RMap *        map;
        void *        udo;
    };
} RVal;

void rval_fzero ( RVal * val );
RValType rval_type ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_compact ( RVal * val );
int rval_lease ( RVal * val );
int rval_zero ( RVal * val );

unsigned long ruxx_get ( RVal * val );
void ruxx_set ( RVal * val, unsigned long u );

long rixx_get ( RVal * val );
void rixx_set ( RVal * val, long i );

double rfxx_get ( RVal * val );
void rfxx_set ( RVal * val, double f );

typedef struct RStr {
    char * buffer;
    size_t refcount;
    size_t len;
    size_t cap;
} RStr;

RStr * __rstr_create ( size_t cap );
int __rstr_resize ( RStr * str, size_t new_cap );
int __rstr_reserve ( RStr * str, size_t new_cap );
int __rstr_cat ( RStr * str, const char * src, size_t len );
void __rstr_destroy ( RStr * str );

int rstr_init ( RVal * val, size_t init_cap );
void rstr_lease ( RVal * val );
void rstr_release ( RVal * val );

int rstr_reserve ( RVal * val, size_t new_cap );
int rstr_compact ( RVal * val );

size_t rstr_len ( RVal * val );
const char * rstr_get ( RVal * val );

int rstr_set ( RVal * dst, RVal * src );
int rstr_cat ( RVal * dst, RVal * src );
int rstr_cmp ( RVal * a, RVal * b );
void rstr_clear ( RVal * val );
int rstr_setc ( RVal * dst, const char * src, size_t src_len );
int rstr_catc ( RVal * dst, const char * src, size_t src_len );
int rstr_cmpc ( RVal * dst, const char * src, size_t src_len );

#endif
