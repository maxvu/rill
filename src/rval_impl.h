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

// Exit immediately if err is defect upon function entry.
#define RILL_PROPAGATE_ERR( RETVAL ) if ( err && *err != RERR_OK ) return RETVAL;

// On null arg, set appropriate code and exit.
#define RILL_ASSERT_NOT_NULL( ID, RETVAL ) if ( !ID ) { if ( err ) *err = RERR_NULL; return RETVAL; }

// On wrong type, set appropriate code and exit.
#define RILL_ASSERT_TYPE( ID, TYP, RET ) ;

#endif
