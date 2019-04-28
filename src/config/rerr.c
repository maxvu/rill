#include "config/arch.h"
#include "config/rerr.h"
#include "rval/rval.h"

RILL_UXX_TYPE ___rill_error_code;
rval ___rill_error_info;

void rerr_init () {
    ___rill_error_code = 0;
    ___rill_error_info = rnil();
}

void rerr_set ( RILL_UXX_TYPE errno ) {
    ___rill_error_code = errno;
}

void rerr_clear () {
    ___rill_error_code = RILL_ERR_OK;
}

RILL_UXX_TYPE rerr_get () {
    return ___rill_error_code;
}

void rerrinfo_set ( rval * info ) {
    rval_copy( &___rill_error_info, info );
}

int rerrinfo_get ( rval * dst ) {
    return rval_copy( dst, &___rill_error_info );
}
