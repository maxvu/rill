#ifndef RILL_RVM
#define RILL_RVM

#include "rval.h"

typedef struct rvm {
    UXX    pc; // program counter
    rval * it; // instruction table
    rval * ct; // constant table
    rval * ps; // primary stack
    rval * ss; // secondary stack
    rval * et; // extension type list
    char   sf; // suspend flag;
} rvm;

rerr rvm_init ( rvm * vm );
rerr rvm_load_it ( rvm * vm, unsigned char * bc, UXX bc_len );
rerr rvm_load_ct ( rvm * vm, rval * ct );
rerr rvm_reset ( rvm * vm );
rerr rvm_step ( rvm * vm );
rerr rvm_run ( rvm * vm );
rerr rvm_retire ( rvm * vm );

#endif
