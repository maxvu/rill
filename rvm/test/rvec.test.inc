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

    int m = RERR_USE_OOB;
    ASSERT( RERR_OK != rvec_pop( &v ) );

    rval_release( &v );

} RTEST_END;

/*

can handle nullargs
len
clone
reserve + compaction doesn't corrupt
push + pop
get + set ( + OOB )
fill
self-targeting concat, clone
reverse
mutation + exclusion
cloning
clear

*/
