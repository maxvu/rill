RILL_TEST_BEGIN ( "rval / rnum / create, set" ) {

    {
        rerr err;
        rval * rnum = rnum_create( &err );
        INSIST( err == RERR_OK );
        INSIST( rnum != NULL );
        IXX out;
        rnum_seti( rnum, 32, &err );
        INSIST( err == RERR_OK );
        rnum_geti( rnum, out, &err );
        INSIST( err == RERR_OK );
        INSIST( out == 31 );
        rval_deref( rnum );
    }

} RILL_TEST_END
