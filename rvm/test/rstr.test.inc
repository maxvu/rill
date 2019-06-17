RTEST( "rval / STR / init" ) {
    { // Initializes in the normal case.
        rval s = rnil();
        ASSERT( RERR_OK == rstr_init( &s, 20 ) );
        ASSERT( RVT_STR == rval_type( &s ) );
        ASSERT( 0 == rstr_len( &s ) );
        rval_release( &s );
    }

    { // Initializes using "quick" syntax;
        rval s = rstrq( "test" );
        ASSERT( RVT_STR == rval_type( &s ) );
        ASSERT( 4 == rstr_len( &s ) );
        rval_release( &s );
    }

    { // Re-initializing a string `_reserve()`s to that capacity.
        rval s = rnil();
        ASSERT( RERR_OK == rstr_init( &s, 20 ) );
        ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
        ASSERT( RERR_OK == rstr_init( &s, 20 ) );
        ASSERT( RVT_STR == rval_type( &s ) );
        ASSERT( 5 == rstr_len( &s ) );
        rval_release( &s );
    }
} RTEST_END;

RTEST( "rval / STR / qcpy + qcat + qcmp" ) {
    rval s = rnil();

    // Initialize via `qcpy`.
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello world" ) );

    // Test `qcpy` result.
    ASSERT( 0 != rstr_qcmp( &s, "hi" ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello world" ) );
    ASSERT( 0 != strcmp( rstr_buf( &s ), "hi" ) );
    ASSERT( 0 == strcmp( rstr_buf( &s ), "hello world" ) );

    // Re-initialize using `qcpy` and `qcat`.
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
    ASSERT( RERR_OK == rstr_qcat( &s, " world" ) );

    // Test `qcat` result using `qcmp`.
    ASSERT( 0 != rstr_qcmp( &s, "hi" ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello world" ) );

    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / reserve + compact" ) {
    // Reserving and then subsequently compacting a string doesn't cause
    // memory errors.
    rval s = rstrq( "test test test test " );
    ASSERT( IS_STR( &s ) );
    ASSERT( RERR_OK == rstr_reserve( &s, 200 ) );
    ASSERT( RERR_OK == rstr_compact( &s ) );
    ASSERT( 0 == rstr_qcmp( &s, "test test test test " ) );

    // Compacting a string of length zero doesn't cause memory errors.
    for ( int i = 0; i < 20; i++ )
        ASSERT( RERR_OK == rstr_qcat( &s, "test test test test " ) );
    ASSERT( RERR_OK == rstr_clear( &s ) );
    ASSERT( RERR_OK == rstr_compact( &s ) );
    ASSERT( s.str->cap < 200 );
    ASSERT( 0 == rstr_len( &s ) );

    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / handles null args" ) {
    // Any `rstr_` function that accepts a pointer gracefully rejects NULLs.
    rval s = rstrq( "" );
    ASSERT( IS_STR( &s ) );

    ASSERT( RERR_USE_NULLARG == rstr_init( NULL, 20 ) );
    ASSERT( RERR_USE_NULLARG == rstr_len( NULL ) );
    ASSERT( RERR_USE_NULLARG == rstr_buf( NULL ) );
    ASSERT( RERR_USE_NULLARG == rstr_reserve( NULL, 200 ) );
    ASSERT( RERR_USE_NULLARG == rstr_compact( NULL ) );
    ASSERT( RERR_USE_NULLARG == rstr_cpy( NULL, &s ) );
    ASSERT( RERR_USE_NULLARG == rstr_cpy( &s, NULL ) );
    ASSERT( RERR_USE_NULLARG == rstr_cat( NULL, &s ) );
    ASSERT( RERR_USE_NULLARG == rstr_cat( &s, NULL ) );
    ASSERT( RERR_USE_NULLARG == rstr_cmp( NULL, &s ) );
    ASSERT( RERR_USE_NULLARG == rstr_cmp( &s, NULL ) );

    {
        uint8_t * msg = ( uint8_t * ) "hello";

        ASSERT( RERR_USE_NULLARG == rstr_mcpy( &s, NULL, 20 ) );
        ASSERT( RERR_USE_NULLARG == rstr_mcpy( NULL, msg, 20 ) );
        ASSERT( RERR_USE_NULLARG == rstr_mcat( &s, NULL, 20 ) );
        ASSERT( RERR_USE_NULLARG == rstr_mcat( NULL, msg, 20 ) );
        rstr_mcmp( &s, NULL, 20 ); // does not cause memory error
        rstr_mcmp( NULL, msg, 20 );
    }

    {
        const char * msg = "hello";
        ASSERT( RERR_USE_NULLARG == rstr_qcpy( &s, NULL ) );
        ASSERT( RERR_USE_NULLARG == rstr_qcpy( NULL, msg ) );
        ASSERT( RERR_USE_NULLARG == rstr_qcat( &s, NULL ) );
        ASSERT( RERR_USE_NULLARG == rstr_qcat( NULL, msg ) );
        rstr_qcmp( &s, NULL );
        rstr_qcat( NULL, msg );
    }

    ASSERT( RERR_USE_NULLARG == rstr_clear( NULL ) );

    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / cpy + cat + cmp" ) {
    rval s = rstrq( "" );
    rval t = rstrq( "" );
    ASSERT( IS_STR( &s ) );
    ASSERT( IS_STR( &t ) );

    ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
    ASSERT( 5 == rstr_len( &s ) );
    ASSERT( 0 == rstr_len( &t ) );
    ASSERT( 0 != rstr_cmp( &s, &t ) );
    ASSERT( 0 != rstr_cmp( &t, &s ) );

    ASSERT( RERR_OK == rstr_cat( &t, &s ) );
    ASSERT( 0 == rstr_cmp( &s, &t ) );

    ASSERT( RERR_OK == rstr_cpy( &t, &s ) );
    ASSERT( 0 == rstr_cmp( &s, &t ) );

    rval_release( &s );
    rval_release( &t );
} RTEST_END;

RTEST( "rval / STR / self-targeting" ) {
    rval s = rstrq( "hello" );
    ASSERT( IS_STR( &s ) );

    // Copying a STR onto itself is a no-op.
    ASSERT( RERR_OK == rstr_cpy( &s, &s ) );
    ASSERT( RERR_OK == rstr_cpy( &s, &s ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello" ) );

    // Cat'ing a STR onto itself is repetition.
    ASSERT( RERR_OK == rstr_qcat( &s, " " ) );
    ASSERT( RERR_OK == rstr_cat( &s, &s ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello hello " ) );
    for ( int i = 0; i < 5; i++ ) // doesn't cause memory error
        ASSERT( RERR_OK == rstr_cat( &s, &s ) );

    // Comparing a STR with itself is always true.
    ASSERT( 0 == rstr_cmp( &s, &s ) );
    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / copy + clone" ) {
    rval s = rstrq( "test" );
    rval t = rnil();
    ASSERT( IS_STR( &s ) );

    // Copying a string creates a shared reference.
    ASSERT( RERR_OK == rval_copy( &t, &s ) );
    ASSERT( IS_STR( &t ) );
    ASSERT( t.str == s.str );
    ASSERT( t.str->ref == 2 );

    // Cloning a string create a unique reference.
    ASSERT( RERR_OK == rval_clone( &t, &s ) );
    ASSERT( IS_STR( &t ) );
    ASSERT( t.str != s.str );
    ASSERT( t.str->ref == 1 );
    ASSERT( s.str->ref == 1 );

    // Excluding makes a unique reference from a shared one.
    ASSERT( RERR_OK == rval_copy( &t, &s ) );
    ASSERT( RERR_OK == rval_exclude( &t ) );
    ASSERT( IS_STR( &t ) );
    ASSERT( t.str != s.str );
    ASSERT( t.str->ref == 1 );
    ASSERT( s.str->ref == 1 );

    rval_release( &s );
    rval_release( &t );
} RTEST_END;

RTEST( "rval / STR / mutation + exclusion" ) {
    { // _qcpy doesn't mutate shared references
        rval s = rstrq( "test" );
        rval t = rnil();
        ASSERT( IS_STR( &s ) );

        ASSERT( RERR_OK == rval_copy( &t, &s ) );
        ASSERT( RERR_OK == rstr_qcpy( &s, "testing" ) );

        ASSERT( 0 == rstr_qcmp( &s, "testing" ) );
        ASSERT( 0 == rstr_qcmp( &t, "test" ) );
        ASSERT( 0 != rstr_qcmp( &t, "testing" ) );
        ASSERT( s.str != t.str );
        ASSERT( 1 == s.str->ref );
        ASSERT( 1 == t.str->ref );

        rval_release( &s );
        rval_release( &t );
    }

    { // _qcat doesn't mutate shared references
        rval s = rstrq( "test" );
        rval t = rnil();
        ASSERT( IS_STR( &s ) );
        ASSERT( RERR_OK == rval_copy( &t, &s ) );

        ASSERT( RERR_OK == rstr_qcat( &s, "ing" ) );
        ASSERT( 0 == rstr_qcmp( &s, "testing" ) );
        ASSERT( 0 == rstr_qcmp( &t, "test" ) );
        ASSERT( 0 != rstr_qcmp( &t, "testing" ) );
        ASSERT( s.str != t.str );
        ASSERT( 1 == s.str->ref );
        ASSERT( 1 == t.str->ref );

        rval_release( &s );
        rval_release( &t );
    }

    { // _cpy doesn't mutate shared references
        rval s = rstrq( "red" );
        rval t = rnil();
        rval u = rstrq( "yellow" );
        ASSERT( RERR_OK == rval_copy( &t, &s ) );
        ASSERT( IS_STR( &s ) );
        ASSERT( IS_STR( &t ) );
        ASSERT( IS_STR( &u ) );
        ASSERT( s.str == t.str );
        ASSERT( s.str != u.str );

        rstr_cpy( &s, &u );
        ASSERT( 0 == rstr_qcmp( &s, "yellow" ) );
        ASSERT( s.str != u.str );
        ASSERT( s.str->ref == 1 );
        ASSERT( t.str->ref == 1 );
        ASSERT( u.str->ref == 1 );

        rval_release( &s );
        rval_release( &t );
        rval_release( &u );
    }

    { // _cat doesn't mutate shared references
        rval s = rstrq( "test" );
        rval t = rnil();
        rval u = rstrq( "ing" );
        ASSERT( RERR_OK == rval_copy( &t, &s ) );
        ASSERT( IS_STR( &s ) );
        ASSERT( IS_STR( &t ) );
        ASSERT( IS_STR( &u ) );

        rstr_cat( &s, &u );
        ASSERT( 0 == rstr_qcmp( &s, "testing" ) );
        ASSERT( s.str->ref == 1 );
        ASSERT( t.str->ref == 1 );
        ASSERT( u.str->ref == 1 );

        rval_release( &s );
        rval_release( &t );
        rval_release( &u );
    }

    { // _clear doesn't mutate shared references
        rval s = rstrq( "test" );
        rval t = rnil();
        ASSERT( RERR_OK == rval_copy( &t, &s ) );

        ASSERT( RERR_OK == rstr_clear( &s ) );
        ASSERT( s.str != t.str );
        ASSERT( s.str->ref == 1 );
        ASSERT( t.str->ref == 1 );

        rval_release( &s );
        rval_release( &t );
    }

    { // _reserve and _compact *do* mutate shared references.
        rval s = rstrq( "test" );
        rval t = rnil();
        ASSERT( IS_STR( &s ) );
        ASSERT( RERR_OK == rval_copy( &t, &s ) );

        ASSERT( RERR_OK == rstr_reserve( &s, 100 ) );
        ASSERT( s.str == t.str );

        ASSERT( RERR_OK == rstr_compact( &s ) );
        ASSERT( s.str == t.str );

        rval_release( &s );
        rval_release( &t );
    }
} RTEST_END;

RTEST( "rval / STR / does not cycle" ) {
    rval s = rnil();
    rval t = rnil();

    ASSERT( RERR_OK == rstr_init( &s, 20 ) );

    ASSERT( !rval_cyclesto( &t, &s ) );

    rval_release( &s );
    rval_release( &t );
} RTEST_END;

RTEST( "rval / STR / truthy if not { \"\" }" ) {
    rval s = rnil();

    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( !rval_truthy( &s ) );
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
    ASSERT( rval_truthy( &s ) );

    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / equal if cmp() == 0" ) {
    rval s = rnil();
    rval t = rnil();

    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( RERR_OK == rstr_init( &t, 20 ) );

    ASSERT( 0 == rstr_cmp( &s, &t ) );
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
    ASSERT( 0 != rstr_cmp( &s, &t ) );

    rval_release( &s );
    rval_release( &t );
} RTEST_END;
