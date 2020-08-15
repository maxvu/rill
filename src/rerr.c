#include "rerr.h"

char rerr_ok ( rerr err ) {
    return err == RERR_OK;
}

const char * rerr_explain ( rerr err ) {
    switch ( err ) {
        case RERR_OK:
            return "ok";
        break;
        case RERR_MEM:
            return "memory allocation error";
        break;
        case RERR_NULL:
            return "unexpected null argument";
        break;
        case RERR_TYPE:
            return "unexpected wrongly-typed argument";
        break;
        case RERR_OVRF:
            return "unexpected overflow";
        break;
        default:
            return "unknown error";
        break;
    }
}
