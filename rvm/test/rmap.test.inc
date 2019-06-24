RTEST( "rval / MAP / init" ) {
    { // Normal initialization.
        rval m = rnil();
        ASSERT( RERR_OK == rmap_init( &m, 10 ) );
        ASSERT( 0 == rmap_size( &m ) );
        ASSERT( IS_MAP( &m ) );
        rval_release( &m );
    }

    { // Quick initialization.
        rval m = rmapq( 10 );
        ASSERT( IS_MAP( &m ) );
        rval_release( &m );
    }
} RTEST_END;

RTEST( "rval / MAP / handles nullargs" ) {
    rval m = rnil();
    rval i = ruxxq( 2 );
    ASSERT( RERR_OK == rmap_init( &m, 20 ) );

    ASSERT( RERR_USE_NULLARG == rmap_init( NULL, 20 ) );
    rmap_size( NULL ); // doesn't segfault
    rmap_load( NULL ); // doesn't segfault
    ASSERT( RERR_USE_NULLARG == rmap_reserve( NULL, 20 ) );
    ASSERT( RERR_USE_NULLARG == rmap_compact( NULL ) );
    rmap_has( NULL, &i ); // doesn't segfault
    rmap_has( &m, NULL ); // doesn't segfault
    ASSERT( NULL == rmap_peek( NULL, &i ) );
    ASSERT( NULL == rmap_peek( &m, NULL ) );
    ASSERT( RERR_USE_NULLARG == rmap_get( NULL, &i, &m ) );
    ASSERT( RERR_USE_NULLARG == rmap_get( &i, NULL, &m ) );
    ASSERT( RERR_OK != rmap_get( &i, &i, NULL ) );
    ASSERT( RERR_USE_NULLARG == rmap_set( NULL, &i, &m ) );
    ASSERT( RERR_OK != rmap_set( &i, NULL, &m ) );
    ASSERT( RERR_OK != rmap_set( &i, &i, NULL ) );
    ASSERT( RERR_OK != rmap_unset( &m, NULL ) );
    ASSERT( RERR_OK != rmap_unset( NULL, &i ) );

    /*
        TODO: the rest of rval / MAP / handles nullargs
    */


    rval_release( &m );
} RTEST_END;

RTEST( "rval / MAP / normal use" ) {
    rval m = rnil();
    rval i = rnil();
    ASSERT( RERR_OK == rmap_init( &m, 10 ) );

    i = ruxxq( 1 );
    ASSERT( RERR_OK == rmap_qset( &m, "one", &i ) );
    i = ruxxq( 2 );
    ASSERT( RERR_OK == rmap_qset( &m, "two", &i ) );
    i = ruxxq( 3 );
    ASSERT( RERR_OK == rmap_qset( &m, "three", &i ) );
    ASSERT( 3 == rmap_size( &m ) );
    ASSERT( 0.33 > rmap_load( &m ) );


    rval_release( &m );
} RTEST_END;




/*
    handles nullargs
    size
    load
    has + get + set
    qhas + qget + qset
    keys + vals
    merge
    qget/qset/qunset
    clear
    iteration

    reservation + compaction
    set self
    try to merge self
    merge something that contains self

    iterator:
    on empty
    normal case
    null args
    past-the-post
*/
