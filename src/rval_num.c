#include "rval.h"

void rixx_get  ( rval * num, IXX * out, rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}

void rixx_set  ( rval * num, IXX   i,   rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}

void ruxx_get  ( rval * num, UXX * out, rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}

void ruxx_set  ( rval * num, UXX   u,   rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}

void rfxx_get  ( rval * num, FXX * out, rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}

void rfxx_set  ( rval * num, FXX   f,   rerr * err ) {
    if ( !err ) return;
    if ( !num ) { *err = RERR_ARG_NULL; return; }
    UXX typ;
    rval_type( num, &typ, err );
    if ( !rerr_ok( err ) ) return;
    

}
