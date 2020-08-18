#include "rerr.h"

char rerr_ok ( rerr * err ) {
    if ( !err )
        return 0;
    return *err == RERR_OK;
}

void rerr_reset           ( rerr * err ) {
    if ( err ) *err = RERR_OK;
}

const char * rerr_explain ( rerr * err ) {
    const char * unknown = "unknown error";
    if ( !err )
        return unknown;
    switch ( *err ) {
        case RERR_OK:
            return "ok";
        break;
        case RERR_MEM:
            return "memory allocation error";
        break;
        case RERR_NULL:
            return "null argument";
        break;
        case RERR_TYPE:
            return "wrong-type argument";
        break;
        case RERR_OVRF:
            return "overflow";
        break;
        default:
            return unknown;
        break;
    }
}
