RTEST( "rfxx / normal case" ) {
    rval a = rnil();
    rfxx_set( &a, 12.0 );
    RMUST( "_get()", rfxx_get( &a ) > 11.9 && rfxx_get( &a ) < 12.1 );
    RMUST( "_get() doesn't segfault on null pointer", !rfxx_get( NULL ) );
    RMUST( "_set() doesn't segfault on null pointer", !rfxx_set( NULL, 1.0 ) );
} RTEST_END;

RTEST( "rfxx / truthiness" ) {
    rval a;
    a = rfxxq( 12.0 );  RMUST( "12.0 is truthy", rval_truthy( &a ) );
    a = rfxxq( NAN );   RMUST( "NaN is truthy", rval_truthy( &a ) );
    a = rfxxq( -0 );    RMUST( "-0 is falsy", !rval_truthy( &a ) );
    a = rfxxq( 0 );     RMUST( "0 is falsy", !rval_truthy( &a ) );
} RTEST_END;
