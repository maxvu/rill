RTEST( "rval / UXX / reports type" ) {
    rval u = ruxxq( 5 );
    ASSERT( rval_type( &u ) == RVT_UXX );
} RTEST_END;

RTEST( "rval / UXX / get() retrieves" ) {
    rval u = ruxxq( 12 );
    ASSERT( ruxx_get( &u ) == 12 );
} RTEST_END;

RTEST( "rval / UXX / handles null" ) {
    ruxx_get( NULL );
    ASSERT( ( RERR_USE_NULLARG == ruxx_set( NULL, 8 ) ) );
    ruxx_set( NULL, 1.0 );
} RTEST_END;

RTEST( "rval / UXX / refcount ops are no-ops" ) {
    rval u = ruxxq( 12.0 );
    rval_lease( &u );
    rval_release( &u );
    rval_exclude( &u );
} RTEST_END;

RTEST( "rval / UXX / copies" ) {
    rval a = ruxxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_copy( &b, &a ) );
    ASSERT( ruxx_get( &b ) == ruxx_get( &a ) );
} RTEST_END;

RTEST( "rval / UXX / clone-copies" ) {
    rval a = ruxxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_clone( &b, &a ) );
    ASSERT( ruxx_get( &b ) == ruxx_get( &a ) );
} RTEST_END;

RTEST( "rval / UXX / truthy when not { 0 }" ) {
    rval u = ruxxq( 1 );
    ASSERT( rval_truthy( &u ) );
    u = ruxxq( UINT_MAX );
    ASSERT( rval_truthy( &u ) );
    u = ruxxq( 0 );
} RTEST_END;
