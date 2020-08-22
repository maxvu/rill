RILL_TEST_BEGIN ( "rval / rnum / IXX get+set" ) {

    {
        rerr err = RERR_OK;

        // create a num
        rval * num = rnum_create( &err );
        INSIST( err == RERR_OK );
        INSIST( num != NULL );

        // set the num as IXX
        IXX out;
        rnum_seti( num, -7, &err );
        INSIST( err == RERR_OK );

        // read the num as IXX
        out = rnum_geti( num, &err );
        INSIST( err == RERR_OK );
        INSIST( out == -7 );

        rval_deref( num );
        INSIST( err == RERR_OK );
    }



} RILL_TEST_END

RILL_TEST_BEGIN ( "rval / rnum / UXX get+set" ) {

    {
        rerr err = RERR_OK;

        // create a num
        rval * num = rnum_create( &err );
        INSIST( err == RERR_OK );
        INSIST( num != NULL );

        // set the num as UXX
        UXX out;
        rnum_setu( num, 32, &err );
        INSIST( err == RERR_OK );

        // read the num as UXX
        out = rnum_getu( num, &err );
        INSIST( err == RERR_OK );
        INSIST( out == 32 );

        rval_deref( num );
        INSIST( err == RERR_OK );
    }

} RILL_TEST_END

RILL_TEST_BEGIN ( "rval / rnum / FXX get+set" ) {

    {
        rerr err = RERR_OK;

        // create a num
        rval * num = rnum_create( &err );
        INSIST( err == RERR_OK );
        INSIST( num != NULL );

        // set the num as FXX
        FXX out;
        rnum_setf( num, 8.0, &err );
        INSIST( err == RERR_OK );

        // read the num as FXX
        out = rnum_getf( num, &err );
        INSIST( err == RERR_OK );
        INSIST( out == 8.0 );

        rval_deref( num );
        INSIST( err == RERR_OK );
    }

} RILL_TEST_END
