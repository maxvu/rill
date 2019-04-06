#ifndef RILL_RWRD
#define RILL_RWRD

RVal rwrd (
    RVal * name
);

int rcb_add_word ( RVal * rcb, RVal * word );
int rcb_recompile ( RVal * rcb );

void rcb_destroy( RVal * rcb );

#endif
