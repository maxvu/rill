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

    ASSERT( RERR_USE_NULLARG == rmap_init( NULL, 20 ) );
    rmap_size( NULL ); // doesn't segfault
    rmap_load( NULL ); // doesn't segfault
    ASSERT( RERR_USE_NULLARG == rmap_reserve( NULL, 20 ) );
    ASSERT( RERR_USE_NULLARG == rmap_compact( NULL ) );
    rmap_has( NULL, &i ); // doesn't segfault
    rmap_has( &m, NULL ); // doesn't segfault


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
