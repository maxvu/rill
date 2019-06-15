RTEST( "rval / IXX / reports type" ) {
    rval i = rixxq( 9 );
    ASSERT( rval_type( &i ) == RVT_IXX );
} RTEST_END;

RTEST( "rval / IXX / get() retrieves" ) {
    rval i = rixxq( 12 );
    ASSERT( rixx_get( &i ) == 12 );
} RTEST_END;

RTEST( "rval / IXX / handles null" ) {
    rixx_get( NULL );
    ASSERT( ( RERR_USE_NULLARG == rixx_set( NULL, 8 ) ) );
    rixx_set( NULL, 1.0 );
} RTEST_END;

RTEST( "rval / IXX / refcount ops are no-ops" ) {
    rval i = rixxq( 12.0 );
    rval_lease( &i );
    rval_release( &i );
    rval_exclude( &i );
} RTEST_END;

RTEST( "rval / IXX / copies" ) {
    rval a = rixxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_copy( &b, &a ) );
    ASSERT( rixx_get( &b ) == rixx_get( &a ) );
} RTEST_END;

RTEST( "rval / IXX / clone-copies" ) {
    rval a = rixxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_clone( &b, &a ) );
    ASSERT( rixx_get( &b ) == rixx_get( &a ) );
} RTEST_END;

RTEST( "rval / IXX / truthy when not { 0 }" ) {
    rval a = rixxq( 1 );
    ASSERT( rval_truthy( &a ) );
    a = rixxq( -1 );
    ASSERT( rval_truthy( &a ) );
    a = rixxq( 0 );
} RTEST_END;
