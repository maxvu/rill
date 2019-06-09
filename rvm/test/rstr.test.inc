RTEST( "rval / STR / init" ) {
    rval s = rnil();
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( RVT_STR == rval_type( &s ) );
    
    ASSERT( 0 == rstr_len( &s ) );
    ASSERT( 20 >= s.str->cap );
    rval_release( &s );
} RTEST_END;

RTEST( "rval / STR / get + qcpy + qcat + qcmp" ) {
    rval s = rnil();
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    ASSERT( RERR_OK == rstr_qcpy( &s, "hello world" ) );
    ASSERT( 0 != rstr_qcmp( &s, "howdy doody" ) );
    ASSERT( 0 == rstr_qcmp( &s, "hello world" ) );
    ASSERT( 0 != strcmp( rstr_buf( &s ), "howdy doody" ) );
    ASSERT( 0 == strcmp( rstr_buf( &s ), "hello world" ) );
    rval_release( &s );
} RTEST_END;



RTEST( "rval / STR / reserve + compact" ) {
    rval s = rnil();
    ASSERT( RERR_OK == rstr_init( &s, 20 ) );
    /*
        TODO
    */
    rval_release( &s );
} RTEST_END;

/*
    handles null args
    init
    len
    buf
    reserve
    compact
    cpy
    cat
    cmp
    
    mcpy
    mcat
    mcmp
    
    qcpy
    qcat
    qcmp
    
    clear
    
    copy
    clone
    cyclesto (between 2 str)
    exclude
    truthy if not empty
    eq (between 2 str)
*/