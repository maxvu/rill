#ifndef RILL_RWRD
#define RILL_RWRD

rval rwrd (
    rval * name
);

int rcb_add_word ( rval * rcb, rval * word );
int rcb_recompile ( rval * rcb );

void rcb_destroy( rval * rcb );

#endif
