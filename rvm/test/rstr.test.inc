RTEST( "rval / STR / init" ) {
    { // Initializes in the normal case.
        rval s = rnil();
        ASSERT( RERR_OK == rstr_init( &s, 20 ) );
        ASSERT( RVT_STR == rval_type( &s ) );
        ASSERT( 0 == rstr_len( &s ) );
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
    rval s = rnil();

    // Reserving and then subsequently compacting a string doesn't cause
    // memory errors.
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( RERR_OK == rstr_qcpy( &s, "test" ) );
    ASSERT( RERR_OK == rstr_reserve( &s, 200 ) );
    ASSERT( RERR_OK == rstr_compact( &s ) );
    ASSERT( 0 == rstr_qcmp( &s, "test" ) );

    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / handles null args" ) {
    rval s = rnil();
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );

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
    rval s = rnil();
    rval t = rnil();
    ASSERT( rstr_init( &s, 20 ) );
    ASSERT( rstr_init( &t, 20 ) );

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
}

RTEST( "rval / STR / self-targeting" ) {
    rval s = rnil();
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello" ) );
    ASSERT( RERR_OK == rstr_cpy( &s, &s ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello" ) );
    rval_release( &s );
}

/*

    can target itself


    clear

    copy
    clone
    cyclesto (between 2 str)
    exclude
    truthy if not empty
    eq (between 2 str)
*/
