#include "platform.h"
#include "rerr.h"
#include "rval.h"
#include "rval_impl.h"

#include <assert.h>

void rvhed_set_typ ( rval * val, UXX typ, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    val->hed &= ~0xFF;
    val->hed |= typ & 0xFF;
}

void rvhed_get_typ ( rval * val, UXX * typ, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    *typ = val->hed & 0xFF;
}

void rvhed_set_tag ( rval * val, UXX tag, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    val->hed &= 0x7F0 << 4;
    val->hed |= ( tag << 4 ) & 0x7F0;
}

void rvhed_get_tag ( rval * val, UXX * tag, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    *tag = val->hed >> 4 & 0x7F0;
}

void rvhed_inc_ref ( rval * val, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    UXX ref = val->hed >> 4 & 0x7F0;
    if ( ++ref > 0x7F ) { *err = RERR_ARG_OVRF; return; }
    val->hed &= ~( 0x7F << 4 );
    val->hed |= ref << 4;
}

void rvhed_dec_ref ( rval * val, rerr * err ) {
    assert( err );
    if ( !err || !rerr_ok( *err ) ) return;
    if ( !val ) { *err = RERR_ARG_NULL; return; }
    UXX ref = val->hed >> 4 & 0x7F0;
    if ( --ref > 0x7F ) { *err = RERR_ARG_OVRF; return; }
    val->hed &= ~( 0x7F << 4 );
    val->hed |= ref << 4;
}

void rval_type     ( rval *  val, char *  typ, rerr * err );
void rval_copy     ( rval ** dst, rval *  src, rerr * err );
void rval_clone    ( rval ** out, rval *  src, rerr * err );
void rval_move     ( rval ** dst, rval ** src, rerr * err );
void rval_contains ( rval *  ndl, rval *  hay, rerr * err );
void rval_ref      ( rval ** val, rerr *  err );
void rval_deref    ( rval ** val, rerr *  err );
