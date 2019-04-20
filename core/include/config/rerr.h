#ifndef RILL_RERR
#define RILL_RERR

#include "config/arch.h"

// TODO: make thread-local
// TODO: setting that info struct after the code's been set can clobber...

typedef struct RVal RVal;

/* system errors (global) */
#define RILL_ERR_OK      0x00  // absence of an error
#define RILL_ERR_ALLOC   0x01  // generic allocation falure
#define RILL_ERR_NULLARG 0x02  // unexpected null argument
#define RILL_ERR_BADARG  0x03  // generic invalid argument

/* val errors (global) */
#define RILL_ERR_VALALLOC    0x10  // allocation failure during rval operations
#define RILL_ERR_TYPEACCESS  0x12  // access to a val of the wrong type

/* UTF-8 decoding errors */
#define RILL_ERR_UTF8EOFTRUNC   0x20
#define RILL_ERR_UTF8EARLYTRUNC 0x21
#define RILL_ERR_UTF8INVALIDBYT 0x22

/* lexer errors (local) */
#define RILL_ERR_LEXOK           0x30
#define RILL_ERR_LEXSTREAMEND    0x31
#define RILL_ERR_LEXBADNUM       0x32
#define RILL_ERR_LEXOPENCOMMENT  0x33
#define RILL_ERR_LEXOPENSTRING   0x34
#define RILL_ERR_LEXOPENLIST     0x35
#define RILL_ERR_LEXOPENHASH     0x36
#define RILL_ERR_LEXOPENQUOTE    0x37
#define RILL_ERR_LEXOPENWORD     0x38

#define RILL_ASSERT_VALTYPE(val,type) if ( !val ) { rerr_set( RILL_ERR_NULLARG ); return 0; } if ( rval_type( val ) != type ) { rerr_set( RILL_ERR_TYPEACCESS ); return 0; }
#define RILL_ASSERT_ISIXX(val)  RILL_ASSERT_VALTYPE(val, RVT_IXX)
#define RILL_ASSERT_ISUXX(val)  RILL_ASSERT_VALTYPE(val, RVT_UXX)
#define RILL_ASSERT_ISFXX(val)  RILL_ASSERT_VALTYPE(val, RVT_FXX)
#define RILL_ASSERT_ISBUF(val)  RILL_ASSERT_VALTYPE(val, RVT_BUF)
#define RILL_ASSERT_ISVEC(val)  RILL_ASSERT_VALTYPE(val, RVT_VEC)
#define RILL_ASSERT_ISMAP(val)  RILL_ASSERT_VALTYPE(val, RVT_MAP)
#define RILL_ASSERT_ARGNOTNULL(arg)  if ( !arg ) { rerr_set( RILL_ERR_BADARG ); return 0; }

void rerr_init ();

void rerr_set ( RILL_UXX_TYPE errno );
void rerr_clear ();
RILL_UXX_TYPE rerr_get ();

void rerrinfo_set ( RVal * info );
int rerrinfo_get ( RVal * dst );

#endif
