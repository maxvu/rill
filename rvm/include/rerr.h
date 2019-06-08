#ifndef RVM_RERR
#define RVM_RERR

#define RERR_OK  0
#define RERR_USE 1
#define RERR_SYS 2

#define RERR_USE_NULLARG ( RERR_USE & ( 1 << 4 ) )
#define RERR_USE_VALTYPE ( RERR_USE & ( 2 << 4 ) )
#define RERR_USE_OOB     ( RERR_USE & ( 3 << 4 ) )

#define RERR_SYS_ALLOC ( RERR_SYS & ( 1 << 4 ) )

#define ASSERT_NOT_NULL( x ) if ( !x ) return RERR_USE_NULLARG
#define ASSERT_TYPE( x, t ) ASSERT_NOT_NULL( x ); if ( rval_type( x ) != t ) return RERR_USE_VALTYPE
#define ASSERT_OK( expr ) { rerr _err; if ( !( _err = ( expr ) ) ) return _err; }
#define ASSERT_NIL( x ) ASSERT_TYPE( x, RVT_NIL )
#define ASSERT_IXX( x ) ASSERT_TYPE( x, RVT_IXX )
#define ASSERT_UXX( x ) ASSERT_TYPE( x, RVT_UXX )
#define ASSERT_FXX( x ) ASSERT_TYPE( x, RVT_FXX )
#define ASSERT_STR( x ) ASSERT_TYPE( x, RVT_FXX )
#define ASSERT_VEC( x ) ASSERT_TYPE( x, RVT_VEC )
#define ASSERT_MAP( x ) ASSERT_TYPE( x, RVT_MAP )

#define IS_NIL( x ) ( rval_type( x ) == RVT_NIL )
#define IS_IXX( x ) ( rval_type( x ) == RVT_IXX )
#define IS_UXX( x ) ( rval_type( x ) == RVT_UXX )
#define IS_FXX( x ) ( rval_type( x ) == RVT_FXX )
#define IS_STR( x ) ( rval_type( x ) == RVT_FXX )
#define IS_VEC( x ) ( rval_type( x ) == RVT_VEC )
#define IS_MAP( x ) ( rval_type( x ) == RVT_MAP )

#endif
