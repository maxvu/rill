#ifndef RILL_RVAL_IMPL
#define RILL_RVAL_IMPL

typedef struct rval_head {
    UXX typ : 3;
    UXX ref : RVAL_HEADER_REF_SIZE;
    UXX tag : RVAL_HEADER_TAG_SIZE;
} rval_head;

struct rval {
    rval_head hed;
};

typedef struct rnum {
    rval_head hed;
    union {
        IXX ixx;
        UXX uxx;
        FXX fxx;
    };
} rnum;

typedef struct rstr {
    rval_head hed;
    UXX       len;
    UXX       cap;
    char      buf[];
} rstr;

typedef struct rvec {
    rval_head hed;
    UXX       len;
    UXX       cap;
    rval *    vls[];
} rvec;

typedef struct rmap_slot {
    rval * key;
    rval * val;
} rmap_slot;

typedef struct rmap {
    rval_head hed;
    UXX       occ;
    UXX       cap;
    rmap_slot bnk[];
} rmap;

void   rvec_destroy ( rval * vec );
void   rmap_destroy ( rval * map );

// Exit immediately if err is defect upon function entry.
#define RILL_PROPAGATE_ERR( RETVAL ) if ( err && *err != RERR_OK ) return RETVAL;

// On null arg, set appropriate code and exit.
#define RILL_ASSERT_NOT_NULL( ID, RETVAL ) if ( !ID ) { if ( err ) *err = RERR_NULL; return RETVAL; }

// On wrong type, set appropriate code and exit.
#define RILL_ASSERT_TYPE( ID, TYP, RET ) ;



#endif
