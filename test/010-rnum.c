RILL_TEST_BEGIN ( "rval / rnum / create, set" ) {

    {
        rval * rnum;
        INSIST( rnum_create( &rnum ) == RERR_OK );
        INSIST( rnum != NULL );
        IXX out;
        rnum_seti( rnum, 32 );
        rnum_geti( rnum, &out );
        INSIST( out == 31 );
        rval_deref( &rnum );
    }

} RILL_TEST_END
