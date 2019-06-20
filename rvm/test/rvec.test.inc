RTEST( "rval / VEC / init" ) {

    { // Normal initialization.
        rval v = rnil();
        ASSERT( RERR_OK == rvec_init( &v, 10 ) );
        ASSERT( IS_VEC( &v ) );
        rval_release( &v );
    }

    { // Quick initialization.
        rval v = rvecq( 10 );
        ASSERT( IS_VEC( &v ) );
        ASSERT( 0 == rvec_len( &v ) );
        rval_release( &v );
    }

} RTEST_END;

RTEST( "rval / VEC / push + pop" ) {

    rval v = rvecq( 10 );
    rval i;

    i = ruxxq( 5 );
    ASSERT( RERR_OK == rvec_push( &v, &i ) );
    ASSERT( 1 == rvec_len( &v ) );

    i = ruxxq( 12 );
    ASSERT( RERR_OK == rvec_push( &v, &i ) );
    ASSERT( 2 == rvec_len( &v ) );

    ASSERT( RERR_OK == rvec_pop( &v ) );
    ASSERT( 1 == rvec_len( &v ) );

    ASSERT( RERR_OK == rvec_pop( &v ) );
    ASSERT( 0 == rvec_len( &v ) );

    ASSERT( RERR_OK != rvec_pop( &v ) );

    rval_release( &v );

} RTEST_END;

RTEST( "rval / VEC / get + set" ) {

    rval v = rvecq( 10 );
    rval i;

    for ( int j = 0; j < 6; j++ ) {
        i = ruxxq( j * 2 );
        ASSERT( RERR_OK == rvec_push( &v, &i ) );
    }

    ASSERT( RERR_OK == rvec_get( &i, 0, &v ) );
    ASSERT(  0 == ruxx_get( &i ) );
    ASSERT( RERR_OK == rvec_get( &i, 1, &v ) );
    ASSERT(  2 == ruxx_get( &i ) );
    ASSERT( RERR_OK == rvec_get( &i, 2, &v ) );
    ASSERT(  4 == ruxx_get( &i ) );
    ASSERT( RERR_OK == rvec_get( &i, 3, &v ) );
    ASSERT(  6 == ruxx_get( &i ) );
    ASSERT( RERR_OK == rvec_get( &i, 4, &v ) );
    ASSERT(  8 == ruxx_get( &i ) );
    ASSERT( RERR_OK == rvec_get( &i, 5, &v ) );
    ASSERT( 10 == ruxx_get( &i ) );

    // Out-of-bounds access.
    ASSERT( RERR_USE_OOB == rvec_get( &i, 999, &v ) );
    ASSERT( RERR_USE_OOB == rvec_set( &v, 999, &i ) );

    {
        rval s = rstrq( "test" );
        ASSERT( IS_STR( &s ) );
        ASSERT( RERR_OK == rvec_set( &v, 2, &s ) );
        rval_release( &s );
    }

    {
        rval s = rnil();
        ASSERT( RERR_OK == rvec_get( &s, 2, &v ) );
        ASSERT( 0 == rstr_qcmp( &s, "test" ) );
        rval_release( &s );
    }

    rval_release( &v );

} RTEST_END;

RTEST( "rval / VEC / handles null args" ) {

    rval v = rvecq( 10 );
    rval i = ruxxq( 2 );

    ASSERT( RERR_USE_NULLARG == rvec_init( NULL, 20 ) );
    rvec_len( NULL ); // doesn't segfault
    ASSERT( RERR_USE_NULLARG == rvec_clone( NULL, &v ) );
    ASSERT( RERR_USE_NULLARG == rvec_clone( &v, NULL ) );
    ASSERT( RERR_USE_NULLARG == rvec_reserve( NULL, 20 ) );
    ASSERT( RERR_USE_NULLARG == rvec_compact( NULL ) );
    ASSERT( RERR_USE_NULLARG == rvec_push( &v, NULL ) );
    ASSERT( RERR_USE_NULLARG == rvec_push( NULL, &v ) );
    ASSERT( RERR_USE_NULLARG == rvec_pop( NULL ) );

    rvec_push( &v, &i );
    ASSERT( RERR_USE_NULLARG == rvec_set( &v, 0, NULL ) );
    ASSERT( RERR_USE_NULLARG == rvec_set( NULL, 0, &v ) );
    ASSERT( RERR_USE_NULLARG == rvec_get( NULL, 0, &i ) );
    ASSERT( RERR_USE_NULLARG == rvec_get( &v, 0, NULL ) );

    rval_release( &v );

} RTEST_END;

RTEST( "rval / VEC / fill" ) {

    rval v = rvecq( 10 );
    rval s = rstrq( "hello" );

    ASSERT( RERR_OK == rvec_fill( &v, &s, 20 ) );
    ASSERT( 20 == rvec_len( &v ) );
    ASSERT( RERR_OK == rvec_get( &s, 9, &v ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello" ) );

    rval_release( &s );
    rval_release( &v );

} RTEST_END;

RTEST( "rval / VEC / doesn't cycle" ) {

    rval j = ruxxq( 1 );

    { // self-targeting concat()
        rval v = rvecq( 10 );
        rvec_push( &v, &j );
        rvec_concat( &v, &v );
        ASSERT( v.vec->ref == 1 );
        rval_release( &v );
    }

    { // self-targeting clone()
        rval v = rvecq( 10 );
        rvec_push( &v, &j );
        rvec_clone( &v, &v );
        ASSERT( v.vec->ref == 1 );
        rval_release( &v );
    }

    { // self-targeting push()
        rval v = rvecq( 10 );
        rvec_push( &v, &j );
        rvec_clone( &v, &v );
        ASSERT( v.vec->ref == 1 );
        rval_release( &v );
    }

} RTEST_END;

RTEST( "rval / VEC / reserve + compact" ) {

    rval v = rvecq( 10 );
    rval i = rnil();

    for ( int j = 0; j < 8; j++ ) {
        i = rixxq( j * 3 );
        ASSERT( RERR_OK == rvec_push( &v, &i ) );
    }
    ASSERT( RERR_OK == rvec_reserve( &v, 60 ) );
    ASSERT( RERR_OK == rvec_compact( &v ) );
    ASSERT( 8 == v.vec->cap );
    ASSERT( RERR_OK == rvec_get( &i, 4, &v ) );
    ASSERT( 12 == rixx_get( &i ) );

    rval_release( &v );

} RTEST_END;

RTEST( "rval / VEC / clear" ) {

    rval v = rvecq( 10 );
    rval i = rnil();

    for ( int j = 0; j < 10; j++ ) {
        i = rixxq( j * 4 );
        ASSERT( RERR_OK == rvec_push( &v, &i ) );
    }
    ASSERT( RERR_OK == rvec_reserve( &v, 40 ) );
    ASSERT( RERR_OK == rvec_clear( &v ) );
    ASSERT( 0 == rvec_len( &v ) );

    rval_release( &v );

} RTEST_END;

/*
    TODO

    peek
    clone
    reverse
    mutation + exclusion
    cloning
*/
