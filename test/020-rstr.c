RILL_TEST_BEGIN ( "rval / rstr / access without resize" ) {

    {
        rerr err = RERR_OK;

        rval * str = rstr_create( 16, &err );
        INSIST( rerr_ok( &err ) );
        INSIST( str != NULL );
        INSIST( rstr_len( str, NULL ) == 0 );

        const char * msg_a = "this is longer than sixteen chars";
        const char * msg_b = "this is not";

        str = rstr_cpyc( str, msg_a, &err );
        INSIST( rstr_len( str, &err ) == strlen( msg_a ) );

        rval * otr = rstr_create( 16, &err );
        INSIST( rerr_ok( &err ) );
        otr = rstr_cpyc( otr, msg_b, &err );
        INSIST( rerr_ok( &err ) );

        INSIST( rstr_cmp( str, otr, NULL ) > 0 );

        rval_deref( str );
        rval_deref( otr );
    }

} RILL_TEST_END
