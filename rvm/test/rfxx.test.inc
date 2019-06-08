RTEST( "rval / FXX / reports type" ) {
    rval f = rfxxq( 12.0 );
    ASSERT( rval_type( &f ) == RVT_FXX );
} RTEST_END;

RTEST( "rval / FXX / get() retrieves" ) {
    rval f = rfxxq( 12.0 );
    ASSERT( fabs( rfxx_get( &f ) - 12.0 ) < 0.001 );
    f = rfxxq( NAN );
    ASSERT( isnan( rfxx_get( &f ) ) );
} RTEST_END;

RTEST( "rval / FXX / handles null" ) {
    rfxx_get( NULL );
    ASSERT( ( RERR_USE_NULLARG == rfxx_set( NULL, 1.0 ) ) );
    rfxx_set( NULL, 1.0 );
} RTEST_END;

RTEST( "rval / FXX / refcount ops are no-ops" ) {
    rval f = rfxxq( 12.0 );
    rval_lease( &f );
    rval_release( &f );
    rval_exclude( &f );
} RTEST_END;

RTEST( "rval / FXX / copies" ) {
    rval a = rfxxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_copy( &b, &a ) );
    ASSERT( fabs( rfxx_get( &b ) - rfxx_get( &a ) ) <= 0.000 );
} RTEST_END;

RTEST( "rval / FXX / clone-copies" ) {
    rval a = rfxxq( 12.0 );
    rval b = rnil();
    ASSERT( RERR_OK == rval_clone( &b, &a ) );
    ASSERT( fabs( rfxx_get( &b ) - rfxx_get( &a ) ) <= 0.000 );
} RTEST_END;

RTEST( "rval / FXX / truthy when not { +0, -0 }" ) {
    rval a = rfxxq( 1.0 );
    ASSERT( rval_truthy( &a ) );
    a = rfxxq( -1.0 );
    ASSERT( rval_truthy( &a ) );
    a = rfxxq( NAN );
    ASSERT( rval_truthy( &a ) );
    a = rfxxq( INFINITY );
    ASSERT( rval_truthy( &a ) );
    a = rfxxq( -INFINITY );
    ASSERT( rval_truthy( &a ) );
    a = rfxxq( 0 );
    ASSERT( !rval_truthy( &a ) );
    a = rfxxq( -0 );
    ASSERT( !rval_truthy( &a ) );
} RTEST_END;
