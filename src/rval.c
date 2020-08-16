#include "platform.h"
#include "rerr.h"
#include "rval.h"
#include "rval_impl.h"

#include <assert.h>
#include <stddef.h>

rerr rvh_set_typ ( rval * val, UXX typ ) {
    if ( !val )
        return RERR_NULL;
    val->hed &= ~0xFF;
    val->hed |= typ & 0xFF;
    return RERR_OK;
}

char rvh_get_typ ( rval * val, UXX * typ ) {
    if ( !val )
        return RERR_NULL;
    return val->hed & 0xFF;
}

rerr rvh_get_tag ( rval * val, UXX * tag ) {
    if ( !val || !tag )
        return RERR_NULL;
    *tag = ( val->hed >> 4 ) & 0x7F;
    return RERR_OK;
}

rerr rvh_set_tag ( rval * val, UXX tag ) {
    if ( !val )
        return RERR_NULL;
    val->hed &= ~( ~0 >> 11 );
    val->hed |= tag << 11;
    return RERR_OK;
}

rerr rvh_get_ref ( rval * val, UXX * ref ) {
    if ( !val )
        return RERR_NULL;
    *ref = ( val->hed >> 4 ) & 0x7F;
    return RERR_OK;
}

rerr rvh_inc_ref ( rval * val ) {
    if ( !val )
        return RERR_NULL;
    UXX ref = ( val->hed >> 4 ) & 0x7F;
    if ( ++ref > 0x7F )
        return RERR_OVRF;
    val->hed &= ~( 0x7F << 4 );
    val->hed |= ( ref << 4 );
    return RERR_OK;
}

rerr rvh_dec_ref ( rval * val ) {
    if ( !val )
        return RERR_NULL;
    UXX ref = ( val->hed >> 4 ) & 0x7F;
    if ( --ref > 0x7F )
        return RERR_OVRF;
    val->hed &= ~( 0x7F << 4 );
    val->hed |= ( ref << 4 );
    return RERR_OK;
}

rerr rval_type ( rval * val, UXX * typ ) {
    if ( !val || !typ )
        return RERR_NULL;
    rerr err = rvh_get_typ( val, typ );
    return err;
}

rerr rval_copy ( rval ** dst, rval *  src ) {
    if ( !dst || src )
        return RERR_NULL;
    *dst = src;
    rvh_inc_ref( *dst );
    return RERR_OK;
}

rerr rval_clone ( rval ** out, rval * src );

rerr rval_move ( rval ** dst, rval ** src ) {
    if ( !dst || !src )
        return RERR_NULL;
    *dst = *src;
    *src = NULL;
    return RERR_OK;
}

rerr rval_contains ( rval *  ndl, rval *  hay );
rerr rval_ref      ( rval ** val );

rerr rval_deref    ( rval ** val ) {
    if ( !rval )
        return RERR_NULL;
    UXX * ref;
    rvh_get_ref( *val )
    switch ( *val->type ) {
        case
    }
}
