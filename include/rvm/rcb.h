#ifndef RILL_RCB
#define RILL_RCB

rval rcb ();

int rcb_add_word ( rval * rcb, rval * word );
int rcb_recompile ( rval * rcb );

void rcb_release( rval * rcb );

#endif
