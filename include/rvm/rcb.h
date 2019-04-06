#ifndef RILL_RCB
#define RILL_RCB

RVal rcb ();

int rcb_add_word ( RVal * rcb, RVal * word );
int rcb_recompile ( RVal * rcb );

void rcb_release( RVal * rcb );

#endif
