#ifndef RILL_RVAL
#define RILL_RVAL

#include "config.h"

#include <stddef.h>
#include <stdint.h>

// TODO: RVal inputs null-checked
// TODO: wrongly-tped functions fail
// TODO: modifiers exclude()

typedef enum RValType RValType;
typedef struct RVal RVal;
typedef struct RBuf RBuf;
typedef struct RVec RVec;
typedef struct RMap RMap;
typedef struct RMapSlot RMapSlot;

enum RValType {
    RVT_NIL = 0,
    RVT_IXX = 1,
    RVT_UXX = 2,
    RVT_FXX = 3,
    RVT_BUF = 4,
    RVT_VEC = 5,
    RVT_MAP = 6
};

struct RVal {
    RValType typ;
    union {
        RILL_IXX_TYPE ixx;
        RILL_UXX_TYPE uxx;
        RILL_FXX_TYPE fxx;
        RBuf *        buf;
        RVec *        vec;
        RMap *        map;
    };
};

int rval_type ( RVal * val );
int rval_lease ( RVal * val );
int rval_release ( RVal * val );
int rval_exclude ( RVal * val );
int rval_copy ( RVal * dst, RVal * src );
int rval_clone ( RVal * dst, RVal * src );
int rval_move ( RVal * dst, RVal * src );
int rval_swap ( RVal * a, RVal * b );
int rval_eq ( RVal * a, RVal * b );

RVal rnil ();

RVal rixx ( RILL_IXX_TYPE i );
void rixx_set ( RVal * val, RILL_IXX_TYPE i );
RILL_IXX_TYPE rixx_get ( RVal * val );

RVal ruxx ( RILL_UXX_TYPE u );
void ruxx_set ( RVal * val, RILL_UXX_TYPE u );
RILL_UXX_TYPE ruxx_get ( RVal * val );

RVal rfxx ( RILL_FXX_TYPE f );
void rfxx_set ( RVal * val, RILL_FXX_TYPE f );
RILL_FXX_TYPE rfxx_get ( RVal * val );

#define RILL_RBUF_MINSIZ 8
#define RILL_RBUF_DEFSIZ 16
#define RILL_RBUF_GROWTH 2.0

typedef struct RBuf {
    size_t    len;
    size_t    cap;
    size_t    ref;
    uint8_t   bts[];
} RBuf;

RVal rbuf ();
int rbuf_init ( RVal * val, size_t cap );
size_t rbuf_len ( RVal * val );
int rbuf_reserve ( RVal * buf, size_t cap );
int rbuf_compact ( RVal * buf );
int rbuf_memcpy ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcat ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_memcmp ( RVal * buf, uint8_t * mem, size_t mem_len );
int rbuf_cpy ( RVal * dst, RVal * src );
int rbuf_cat ( RVal * dst, RVal * src );
int rbuf_cmp ( RVal * a, RVal * b );
int rbuf_strcpy ( RVal * buf, const char * cstr );
int rbuf_strcat ( RVal * buf, const char * cstr );
int rbuf_strcmp ( RVal * buf, const char * cstr );
int rbuf_clear ( RVal * buf );

#define RILL_RVEC_MINSIZ 4
#define RILL_RVEC_DEFSIZ 12
#define RILL_RVEC_GROWTH 2.0

typedef struct RVec {
    size_t len;
    size_t cap;
    size_t ref;
    RVal   vls[];
} RVec;

RVal rvec ();
int rvec_init ( RVal * vec, size_t cap );
int rvec_reserve ( RVal * vec, size_t cap );
int rvec_compact ( RVal * vec );
int rvec_push ( RVal * vec, RVal * item );
int rvec_pop ( RVal * vec );
int rvec_get ( RVal * vec, size_t idx );
int rvec_set ( RVal * vec, size_t idx, RVal * item );
int rvec_fill ( RVal * vec, RVal * fill, size_t n );
int rvec_reverse ( RVal * vec );
int rvec_concat ( RVal * dst, RVal * src );
int rvec_clear ( RVal * vec );

#define RILL_RMAP_MINSIZ 4
#define RILL_RMAP_DEFSIZ 12
#define RILL_RMAP_GROWTH 2.0
#define RILL_RMAP_MAXLOD 0.95

struct RMapSlot {
    RVal key;
    RVal val;
};

struct RMap {
    size_t     occ;
    size_t     cap;
    size_t     ref;
    RMapSlot   slt[];
};

RVal rmap ();
int rmap_init ( RVal * map, size_t cap );
int rmap_reserve ( RVal * map, size_t cap );
int rmap_compact ( RVal * map );
int rmap_set ( RVal * map, RVal * key, RVal * val );
int rmap_get ( RVal * map, RVal * key );
int rmap_unset ( RVal * map, RVal * key );
int rmap_keys ( RVal * dst_lst, RVal * src_map );
int rmap_vals ( RVal * dst_lst, RVal * src_map );
int rmap_merge ( RVal * dst, RVal * src );
int rmap_clear ( RVal * map );

#endif
