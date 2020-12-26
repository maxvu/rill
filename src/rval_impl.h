#include "rval.h"

#ifdef RILL32_BIT
    typedef struct rval_header {
        int typ : 3;
        int ref : 8;
        int tag : 21;
    } rval_header;
    #define IXX int
    #define UXX unsigned int
    #define FXX float
#else
    typedef struct rval_header {
        int typ : 3;
        int ref : 10;
        int tag : 51;
    } rval_header;
    #define IXX long
    #define UXX unsigned long
    #define FXX double
#endif
